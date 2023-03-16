
// SPDX-License-Identifier: Apache-2.0

//
// Created by Keren Dong on 2020/5/22.
//

#include <kungfu/yijinjing/journal/assemble.h>
#include <kungfu/yijinjing/time.h>

namespace kungfu::yijinjing::journal {
using namespace kungfu::longfist::enums;
using namespace kungfu::longfist::types;

struct noop_publisher : public publisher {
  noop_publisher() = default;
  bool is_usable() override { return true; }
  void setup() override {}
  int notify() override { return 0; }
  int publish(const std::string &json_message) override { return 0; }
};

struct assemble_exception : std::runtime_error {
  explicit assemble_exception(const std::string &msg) : std::runtime_error(msg){};
};

sink::sink() : publisher_(std::make_shared<noop_publisher>()) {}

publisher_ptr sink::get_publisher() { return publisher_; }

copy_sink::copy_sink(data::locator_ptr locator) : sink(), locator_(std::move(locator)) {}

void copy_sink::put(const data::location_ptr &location, uint32_t dest_id, const frame_ptr &frame) {
  auto pair = writers_.try_emplace(location->uid);
  auto &writers = pair.first->second;
  if (writers.find(dest_id) == writers.end()) {
    auto target_location = data::location::make_shared(*location, locator_);
    writers.try_emplace(dest_id, std::make_shared<writer>(target_location, dest_id, true, get_publisher()));
  }
  writers.at(dest_id)->copy_frame(frame);
}

assemble::assemble(const std::string &mode, const std::string &category, const std::string &group,
                   const std::string &name)
    : mode_(mode), category_(category), group_(group), name_(name), publisher_(std::make_shared<noop_publisher>()) {}

assemble::assemble(const std::vector<data::locator_ptr> &locators, const std::string &mode, const std::string &category,
                   const std::string &group, const std::string &name)
    : mode_(mode), category_(category), group_(group), name_(name), publisher_(std::make_shared<noop_publisher>()) {
  for (auto &locator : locators) {
    locators_.push_back(locator);
    readers_.push_back(std::make_shared<reader>(true));
    auto reader = readers_.back();
    for (auto &location : locator->list_locations(category, group, name, mode)) {
      for (auto dest_id : locator->list_location_dest(location)) {
        reader->join(location, dest_id, 0);
      }
    }
  }
  sort();
}

assemble assemble::operator+(assemble &other) {
  if (mode_ != other.mode_ or category_ != other.category_ or group_ != other.group_ or name_ != other.name_) {
    auto msg = fmt::format("assemble incompatible: {}/{}/{}/{}, {}/{}/{}/{}", category_, group_, name_, mode_,
                           other.category_, other.group_, other.name_, other.mode_);
    throw assemble_exception(msg);
  }
  std::vector<data::locator_ptr> merged_locators = {};
  merged_locators.insert(merged_locators.end(), locators_.begin(), locators_.end());
  merged_locators.insert(merged_locators.end(), other.locators_.begin(), other.locators_.end());
  return assemble(merged_locators, mode_, category_, group_, name_);
}

void assemble::operator>>(const sink_ptr &sink) {
  while (data_available()) {
    auto page = current_reader_->current_page();
    sink->put(page->get_location(), page->get_dest_id(), current_frame());
    next();
  }
}

bool assemble::data_available() {
  sort();
  for (auto &reader : readers_) {
    if (reader->data_available()) {
      return true;
    }
  }
  return false;
}

void assemble::next() {
  if (current_reader_ and current_reader_->data_available()) {
    current_reader_->next();
  }
  sort();
}

frame_ptr assemble::current_frame() { return current_reader_->current_frame(); }

void assemble::sort() {
  int64_t min_time = INT64_MAX;
  for (auto &reader : readers_) {
    if (reader->data_available() and reader->current_frame()->gen_time() < min_time) {
      min_time = reader->current_frame()->gen_time();
      current_reader_ = reader;
    }
  }
}

assemble::assemble(const data::location_ptr &source_location, uint32_t dest_id, uint32_t assemble_mode,
                   int64_t from_time)
    : assemble() {
  readers_.clear();
  data::locator l{};
  readers_.push_back(std::make_shared<reader>(true));
  auto reader = readers_.front();

  // join channel
  if (assemble_mode & AssembleMode::Channel) {
    reader->join(source_location, dest_id, from_time);
  }

  // join all journal dest of location
  if (assemble_mode & AssembleMode::Write) {
    for (auto dest : l.list_location_dest(source_location)) {
      reader->join(source_location, dest, from_time);
    }
  }

  // scan all locations, join dest_id or PUBLIC
  bool b_read = assemble_mode & AssembleMode::Read;
  bool b_public = assemble_mode & AssembleMode::Public;
  bool b_all = assemble_mode & AssembleMode::All;
  if (b_read or b_public or b_all) {
    for (auto &location : l.list_locations("*", "*", "*", "*")) {
      for (auto dest : l.list_location_dest(location)) {
        if (b_all) {
          reader->join(location, dest, from_time);
        } else if (b_read and dest == dest_id) {
          reader->join(location, dest_id, from_time);
        } else if (b_public and dest == data::location::PUBLIC) {
          reader->join(location, data::location::PUBLIC, from_time);
        }
      }
    }
  }
  sort();
}

[[maybe_unused]] void assemble::seek_to_time(int64_t nano_time) {
  for (auto &reader : readers_) {
    reader->seek_to_time(nano_time);
  }
  sort();
}

} // namespace kungfu::yijinjing::journal