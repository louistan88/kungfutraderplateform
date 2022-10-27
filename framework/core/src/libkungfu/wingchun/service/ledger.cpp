//
// Created by Keren Dong on 2019-06-28.
//

#include <kungfu/common.h>
#include <kungfu/longfist/longfist.h>
#include <kungfu/wingchun/service/ledger.h>
#include <kungfu/yijinjing/time.h>

using namespace kungfu::rx;
using namespace kungfu::yijinjing::practice;
using namespace kungfu::longfist;
using namespace kungfu::longfist::enums;
using namespace kungfu::longfist::types;
using namespace kungfu::yijinjing;
using namespace kungfu::yijinjing::data;
using namespace kungfu::yijinjing::cache;

namespace kungfu::wingchun::service {
Ledger::Ledger(locator_ptr locator, mode m, bool low_latency)
    : apprentice(location::make_shared(m, category::SYSTEM, "service", "ledger", std::move(locator)), low_latency),
      broker_client_(*this), bookkeeper_(*this, broker_client_) {}

void Ledger::on_exit() {}

void Ledger::on_trading_day(const event_ptr &event, int64_t daytime) { bookkeeper_.on_trading_day(daytime); }

book::Bookkeeper &Ledger::get_bookkeeper() { return bookkeeper_; }

void Ledger::on_start() {
  broker_client_.on_start(events_);
  bookkeeper_.on_start(events_);
  bookkeeper_.guard_positions();

  events_ | is(BrokerStateUpdate::tag) | $$(update_broker_state_map(event->source(), event->data<BrokerStateUpdate>()));
  events_ | is(Deregister::tag) | $$(update_broker_state_map(event->source(), event->data<Deregister>()));
  events_ | is(OrderInput::tag) | $$(update_order_stat(event, event->data<OrderInput>()));
  events_ | is(Order::tag) | $$(update_order_stat(event, event->data<Order>()));
  events_ | is(Trade::tag) | $$(update_order_stat(event, event->data<Trade>()));
  events_ | is(Channel::tag) | $$(inspect_channel(event->gen_time(), event->data<Channel>()));
  events_ | is(KeepPositionsRequest::tag) | $$(keep_positions(event->gen_time(), event->source()));
  events_ | is(RebuildPositionsRequest::tag) | $$(rebuild_positions(event->gen_time(), event->source()));
  events_ | is(MirrorPositionsRequest::tag) | $$(bookkeeper_.mirror_positions(event->gen_time(), event->source()));
  events_ | is(BrokerStateRequest::tag) | $$(write_broker_state(event->gen_time(), event->source()));
  events_ | is(AssetRequest::tag) | $$(write_book_reset(event->gen_time(), event->source()));
  events_ | is(PositionRequest::tag) | $$(write_strategy_data(event->gen_time(), event->source()));
  events_ | is(PositionEnd::tag) | skip_while(while_to(location::SYNC)) |
      $$(update_account_book(event->gen_time(), event->data<PositionEnd>().holder_uid););

  add_time_interval(time_unit::NANOSECONDS_PER_MINUTE, [&](auto e) { request_asset_sync(e->gen_time()); });
  add_time_interval(time_unit::NANOSECONDS_PER_MINUTE, [&](auto e) { request_position_sync(e->gen_time()); });
  refresh_books();
}

void Ledger::update_broker_state_map(uint32_t location_uid, const BrokerStateUpdate &state) {
  broker_states_.insert_or_assign(location_uid, state);
}

void Ledger::update_broker_state_map(uint32_t location_uid, const Deregister &deregister) {
  if (broker_states_.find(location_uid) != broker_states_.end()) {
    broker_states_.erase(location_uid);
  }
}

void Ledger::refresh_books() {
  for (const auto &pair : bookkeeper_.get_books()) {
    if (pair.second->asset.ledger_category == LedgerCategory::Account) {
      refresh_account_book(now(), pair.first);
    }
    request_write_to(now(), pair.first);
  }
}

void Ledger::refresh_account_book(int64_t trigger_time, uint32_t account_uid) {
  auto account_location = get_location(account_uid);
  auto group = account_location->group;
  auto md_location = location::make_shared(account_location->mode, category::MD, group, group, get_locator());
  auto book = bookkeeper_.get_book(account_uid);
  auto subscribe_positions = [&](auto positions) {
    for (const auto &pair : positions) {
      auto &position = pair.second;
      broker_client_.subscribe(md_location, position.exchange_id, position.instrument_id);
    }
  };
  subscribe_positions(book->long_positions);
  subscribe_positions(book->short_positions);
  broker_client_.try_renew(trigger_time, md_location);
  book->update(trigger_time);
}

OrderStat &Ledger::get_order_stat(uint64_t order_id, const event_ptr &event) {
  if (order_stats_.find(order_id) == order_stats_.end()) {
    order_stats_.try_emplace(order_id, get_home_uid(), event->source(), event->gen_time(), OrderStat());
  }
  return order_stats_.at(order_id).data;
}

void Ledger::update_order_stat(const event_ptr &event, const OrderInput &data) {
  write_book(event->gen_time(), event->dest(), event->source(), data);
  auto &stat = get_order_stat(data.order_id, event);
  stat.order_id = data.order_id;
  stat.md_time = event->trigger_time();
  stat.input_time = event->gen_time();
}

void Ledger::update_order_stat(const event_ptr &event, const Order &data) {
  if (data.error_id == 0) {
    write_book(event->gen_time(), event->source(), event->dest(), data);
  }
  auto &stat = get_order_stat(data.order_id, event);
  auto inserted = stat.insert_time != 0;
  auto acked = stat.ack_time != 0;
  if (not inserted) {
    stat.insert_time = event->gen_time();
    write_to(event->gen_time(), stat, event->source());
  }
  if (inserted and not acked) {
    stat.ack_time = event->gen_time();
    write_to(event->gen_time(), stat, event->source());
  }
}

void Ledger::update_order_stat(const event_ptr &event, const Trade &data) {
  write_book(event->gen_time(), event->source(), event->dest(), data);
  auto &stat = get_order_stat(data.order_id, event);
  if (stat.trade_time == 0) {
    stat.trade_time = event->gen_time();
    stat.total_price += data.price * data.volume;
    stat.total_volume += data.volume;
    if (stat.total_volume > 0) {
      stat.avg_price = stat.total_price / stat.total_volume;
    }
    write_to(event->gen_time(), stat, event->source());
  }
}

void Ledger::update_account_book(int64_t trigger_time, uint32_t account_uid) {
  refresh_account_book(trigger_time, account_uid);
  auto writer = get_writer(account_uid);
  auto book = bookkeeper_.get_book(account_uid);
  auto &asset = book->asset;
  write_positions(trigger_time, account_uid, book->long_positions);
  write_positions(trigger_time, account_uid, book->short_positions);
  writer->write(trigger_time, asset);
}

void Ledger::inspect_channel(int64_t trigger_time, const Channel &channel) {
  auto source_location = get_location(channel.source_id);
  auto is_from_account = source_location->category == category::TD;

  if (channel.source_id == cached_home_location_->uid or channel.dest_id == cached_home_location_->uid) {
    return;
  }
  if (channel.source_id != get_live_home_uid() and channel.dest_id != get_live_home_uid()) {
    reader_->join(source_location, channel.dest_id, trigger_time);
  }
  if (channel.dest_id == get_live_home_uid() and has_writer(channel.source_id) and is_from_account) {
    write_book_reset(trigger_time, channel.source_id);
  }
}

void Ledger::keep_positions(int64_t trigger_time, uint32_t strategy_uid) {
  if (bookkeeper_.has_book(strategy_uid)) {
    auto strategy_book = bookkeeper_.get_book(strategy_uid);
    tmp_books_.insert_or_assign(strategy_uid, strategy_book);
    bookkeeper_.drop_book(strategy_uid);
  }
}

void Ledger::rebuild_positions(int64_t trigger_time, uint32_t strategy_uid) {
  auto strategy_book = bookkeeper_.get_book(strategy_uid);
  auto rebuild_book = [&](auto &positions) {
    for (const auto &pair : positions) {
      auto &position = pair.second;
      if (strategy_book->has_position_for(position)) {
        auto &strategy_position = strategy_book->get_position_for(position.direction, position);
        longfist::copy(strategy_position, position);
        strategy_position.update_time = trigger_time;
      }
    }
  };

  if (tmp_books_.find(strategy_uid) != tmp_books_.end()) {
    auto tmp_book = tmp_books_.at(strategy_uid);
    rebuild_book(tmp_book->long_positions);
    rebuild_book(tmp_book->short_positions);
  }
  strategy_book->update(trigger_time);
}

void Ledger::write_broker_state(int64_t trigger_time, uint32_t source_id) {
  auto writer = get_writer(source_id);
  for (const auto &pair : broker_states_) {
    auto &broker_state = pair.second;
    writer->write(trigger_time, broker_state);
  }
}

void Ledger::write_book_reset(int64_t trigger_time, uint32_t book_uid) {
  auto writer = get_writer(book_uid);
  writer->open_data<CacheReset>(trigger_time).msg_type = Position::tag;
  writer->close_data();
  writer->open_data<CacheReset>(trigger_time).msg_type = Asset::tag;
  writer->close_data();
  writer->open_data<CacheReset>(trigger_time).msg_type = AssetMargin::tag;
  writer->close_data();
  writer->mark(trigger_time, ResetBookRequest::tag);
}

void Ledger::write_strategy_data(int64_t trigger_time, uint32_t strategy_uid) {
  auto writer = get_writer(strategy_uid);
  for (const auto &pair : bookkeeper_.get_books()) {
    auto &book = pair.second;
    auto &asset = book->asset;
    auto &asset_margin = book->asset_margin;
    auto book_uid = asset.holder_uid;
    bool has_account = asset.ledger_category == LedgerCategory::Account and has_channel(book_uid, strategy_uid);
    bool is_strategy = asset.ledger_category == LedgerCategory::Strategy and book_uid == strategy_uid;
    if (has_account or is_strategy) {
      write_positions(trigger_time, strategy_uid, book->long_positions);
      write_positions(trigger_time, strategy_uid, book->short_positions);
      writer->write(trigger_time, asset);
      writer->write(trigger_time, asset_margin);
    }
  }
  writer->open_data<PositionEnd>(trigger_time).holder_uid = strategy_uid;
  writer->close_data();
}

void Ledger::write_positions(int64_t trigger_time, uint32_t dest, book::PositionMap &positions) {
  auto writer = get_writer(dest);
  for (const auto &pair : positions) {
    if (pair.second.volume > 0) {
      writer->write_as(trigger_time, pair.second, get_home_uid(), pair.second.holder_uid);
    }
  }
}

void Ledger::request_asset_sync(int64_t trigger_time) {
  for (const auto &pair : bookkeeper_.get_books()) {
    auto &book = pair.second;
    auto &asset = book->asset;
    if (asset.ledger_category == LedgerCategory::Account and has_writer(asset.holder_uid)) {
      get_writer(asset.holder_uid)->mark(trigger_time, AssetSync::tag);
    }
  }
}

void Ledger::request_position_sync(int64_t trigger_time) {
  for (const auto &pair : bookkeeper_.get_books()) {
    auto &book = pair.second;
    auto &asset = book->asset;
    if (asset.ledger_category == LedgerCategory::Account and has_writer(asset.holder_uid)) {
      get_writer(asset.holder_uid)->mark(trigger_time, PositionSync::tag);
    }
  }
}

} // namespace kungfu::wingchun::service