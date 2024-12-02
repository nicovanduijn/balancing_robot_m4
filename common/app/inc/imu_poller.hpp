#pragma once

#include "common/app/inc/a7_communicator.hpp"
#include "common/interface/inc/estimator.hpp"
#include "common/interface/inc/imu.hpp"
#include "common/rtos/inc/task.hpp"

namespace Common {
namespace App {

class ImuPoller : public Rtos::Task {
   public:
    ImuPoller(Interface::Imu& imu, Interface::Estimator& estimator, A7Communicator& a7Communicator);

   private:
    static constexpr uint32_t IMU_PERIOD_ms = 500u;
    void threadFunction() override;
    Interface::Imu& m_imu;
    Interface::Estimator& m_estimator;
    A7Communicator& m_a7Communicator;
};

}  // namespace App
}  // namespace Common