#pragma once

#include "common/interface/inc/imu.hpp"
#include "common/rtos/inc/task.hpp"

namespace Common {
namespace App {

class ImuPoller : public Rtos::Task {
   public:
    ImuPoller(Interface::Imu& imu);

   private:
    static constexpr uint32_t IMU_PERIOD_ms = 500u;
    void threadFunction() override;
    Interface::Imu& m_imu;
};

}  // namespace App
}  // namespace Common