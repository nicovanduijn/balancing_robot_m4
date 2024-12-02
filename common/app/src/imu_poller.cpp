#include "common/app/inc/imu_poller.hpp"

namespace Common {
namespace App {

ImuPoller::ImuPoller(Interface::Imu& imu, Interface::Estimator& estimator,
                     A7Communicator& a7Communicator)
    : Task{"imuPoller", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},
      m_imu{imu},
      m_estimator{estimator},
      m_a7Communicator{a7Communicator} {}

void ImuPoller::threadFunction() {
    for (;;) {
        auto acceleration_mpss = m_imu.getAcceleration_mpss();
        m_estimator.addAccelerometerMeasurement(acceleration_mpss);
        Eigen::Vector4f current_state = m_estimator.getCurrentState();
        float current_pitch_degrees = 57.295f * current_state(2);
        m_a7Communicator.sendAngle(0, current_pitch_degrees);
        vTaskDelay(pdMS_TO_TICKS(IMU_PERIOD_ms));
    }
}

}  // namespace App
}  // namespace Common