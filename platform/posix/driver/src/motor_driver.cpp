#include "platform/posix/driver/inc/motor_driver.hpp"

namespace Driver {

void Motor::setMotorSpeed(float speed_normalized) {
    m_speed_normalized = speed_normalized;
}

}  // namespace Driver