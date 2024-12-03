#include "common/app/inc/balancing_robot.hpp"

namespace Common {
namespace App {

BalancingRobot::BalancingRobot(Interface::Imu& imu,
                               Interface::Estimator& estimator,
                               Interface::Controller& controller,
                               A7Communicator& a7_communicator)
    : Task{"BalancingRobot", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},
      m_imu{imu},
      m_estimator{estimator},
      m_controller{controller},
      m_a7_communicator{a7_communicator} {
    const Eigen::Vector4f desired_state{0.0f, 0.0f, 0.0f, 0.0f};
    m_controller.setDesiredState(desired_state);
}

void BalancingRobot::threadFunction() {
    for (;;) {
        auto acceleration_mpss = m_imu.getAcceleration_mpss();
        auto rotational_velocity_radps = m_imu.getRotationalVelocity_radps();

        m_estimator.addAccelerometerMeasurement(acceleration_mpss);
        m_estimator.addGyroscopeMeasurement(rotational_velocity_radps);

        Eigen::Vector4f current_state = m_estimator.getCurrentState();
        float current_pitch_degrees = 57.295f * current_state(2);
        m_a7_communicator.sendAngle(0, current_pitch_degrees);

        m_controller.setCurrentState(current_state);
        auto control = m_controller.getControl();
        m_a7_communicator.sendDebug(control, 0.0f, 0.0f, 0.0f);

        vTaskDelay(pdMS_TO_TICKS(IMU_PERIOD_ms));
    }
}

}  // namespace App
}  // namespace Common