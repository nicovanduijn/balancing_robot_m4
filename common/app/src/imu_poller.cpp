#include "common/app/inc/imu_poller.hpp"

namespace Common {
namespace App {

ImuPoller::ImuPoller(Interface::Imu& imu, A7Communicator& a7Communicator)
    : Task{"imuPoller", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},
      m_imu{imu},
      m_a7Communicator{a7Communicator} {}

void ImuPoller::threadFunction() {
    for (;;) {
        auto value = m_imu.getXAcceleration_mpss();
        m_a7Communicator.sendAngle(0, static_cast<int16_t>(100 * value));
        vTaskDelay(pdMS_TO_TICKS(IMU_PERIOD_ms));
    }
}

}  // namespace App
}  // namespace Common