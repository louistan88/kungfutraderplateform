//
// Created by Keren Dong on 2020/3/12.
//

#ifndef WINGCHUN_BROKER_CLIENT_H
#define WINGCHUN_BROKER_CLIENT_H

#include <kungfu/longfist/longfist.h>
#include <kungfu/wingchun/broker/broker.h>
#include <kungfu/yijinjing/io.h>
#include <kungfu/yijinjing/log.h>
#include <kungfu/yijinjing/practice/apprentice.h>

namespace kungfu::wingchun::broker {
struct ResumePolicy {
  [[nodiscard]] int64_t get_connect_time(const yijinjing::practice::apprentice &app,
                                         const longfist::types::Register &broker) const;

  [[nodiscard]] virtual int64_t get_resmue_time(const yijinjing::practice::apprentice &app,
                                                const longfist::types::Register &broker) const = 0;
};

struct ContinuousResumePolicy : public ResumePolicy {
  [[nodiscard]] int64_t get_resmue_time(const yijinjing::practice::apprentice &app,
                                        const longfist::types::Register &broker) const override;
};

struct IntradayResumePolicy : public ResumePolicy {
  [[nodiscard]] int64_t get_resmue_time(const yijinjing::practice::apprentice &app,
                                        const longfist::types::Register &broker) const override;
};

class Client {
  typedef std::unordered_map<uint32_t, longfist::types::InstrumentKey> InstrumentKeyMap;
  typedef std::unordered_map<uint32_t, longfist::enums::BrokerState> BrokerStateMap;

public:
  explicit Client(yijinjing::practice::apprentice &app);

  virtual ~Client() = default;

  [[nodiscard]] const InstrumentKeyMap &get_instrument_keys() const;

  [[nodiscard]] virtual bool is_ready(uint32_t broker_location_uid) const;

  [[nodiscard]] virtual const ResumePolicy &get_resume_policy() const = 0;

  [[nodiscard]] virtual bool is_subscribed(uint32_t md_location_uid, const std::string &exchange_id,
                                           const std::string &instrument_id) const;

  virtual void subscribe(const yijinjing::data::location_ptr &md_location, const std::string &exchange_id,
                         const std::string &instrument_id);

  virtual void on_start(const rx::connectable_observable<event_ptr> &events);

protected:
  yijinjing::practice::apprentice &app_;

  [[nodiscard]] virtual bool should_connect_md(const yijinjing::data::location_ptr &md_location) const = 0;

  [[nodiscard]] virtual bool should_connect_td(const yijinjing::data::location_ptr &md_location) const = 0;

  [[nodiscard]] virtual bool should_connect_strategy(const yijinjing::data::location_ptr &md_location) const = 0;

  virtual void subscribe_instruments(int64_t trigger_time, const yijinjing::data::location_ptr &md_location);

private:
  BrokerStateMap broker_states_ = {};
  InstrumentKeyMap instrument_keys_ = {};
  yijinjing::data::location_map ready_md_locations_ = {};
  yijinjing::data::location_map ready_td_locations_ = {};
  yijinjing::data::location_map instrument_md_locations_ = {};

  void connect(const event_ptr &event, const longfist::types::Register &register_data);

  void update_broker_state(const event_ptr &event, const longfist::types::BrokerStateUpdate &state);

  void update_broker_state(const event_ptr &event, const longfist::types::Deregister &deregister_data);
};

class AutoClient : public Client {
public:
  explicit AutoClient(yijinjing::practice::apprentice &app);

  [[nodiscard]] const ResumePolicy &get_resume_policy() const override;

protected:
  [[nodiscard]] bool should_connect_md(const yijinjing::data::location_ptr &md_location) const override;

  [[nodiscard]] bool should_connect_td(const yijinjing::data::location_ptr &md_location) const override;

  [[nodiscard]] bool should_connect_strategy(const yijinjing::data::location_ptr &md_location) const override;

private:
  ContinuousResumePolicy resume_policy_ = {};
};

class ManualClient : public Client {
  typedef std::unordered_map<uint32_t, bool> EnrollmentMap;

public:
  explicit ManualClient(yijinjing::practice::apprentice &app);

  [[nodiscard]] const ResumePolicy &get_resume_policy() const override;

  [[nodiscard]] bool is_subscribed(uint32_t md_location_uid, const std::string &exchange_id,
                                   const std::string &instrument_id) const override;

  void subscribe(const yijinjing::data::location_ptr &md_location, const std::string &exchange_id,
                 const std::string &instrument_id) override;

  [[nodiscard]] bool is_all_subscribed(uint32_t md_location_uid) const;

  void subscribe_all(const yijinjing::data::location_ptr &md_location);

  void enroll_account(const yijinjing::data::location_ptr &td_location);

protected:
  [[nodiscard]] bool should_connect_md(const yijinjing::data::location_ptr &md_location) const override;

  [[nodiscard]] bool should_connect_td(const yijinjing::data::location_ptr &md_location) const override;

  [[nodiscard]] bool should_connect_strategy(const yijinjing::data::location_ptr &md_location) const override;

  void subscribe_instruments(int64_t trigger_time, const yijinjing::data::location_ptr &md_location) override;

private:
  IntradayResumePolicy resume_policy_ = {};
  EnrollmentMap enrolled_md_locations_ = {};
  EnrollmentMap enrolled_td_locations_ = {};
};

template <typename DataType>
static constexpr auto is_own = [](const Client &broker_client) {
  return rx::filter([&](const event_ptr &event) {
    const DataType &data = event->data<DataType>();
    return event->msg_type() == DataType::tag and
           broker_client.is_subscribed(event->source(), data.exchange_id, data.instrument_id);
  });
};
} // namespace kungfu::wingchun::broker

#endif // WINGCHUN_BROKER_CLIENT_H
