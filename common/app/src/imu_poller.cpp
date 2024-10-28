#include "common/app/inc/imu_poller.hpp"

namespace Common {
namespace App {

ImuPoller::ImuPoller(Interface::Imu& imu)
    : Task{"imuPoller", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},
      m_imu{imu} {}

void ImuPoller::threadFunction() {
    for (;;) {
        m_imu.getXAcceleration_mpss();
        vTaskDelay(IMU_PERIOD_ms);
    }
}

}  // namespace App
}  // namespace Common