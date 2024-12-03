#include "platform/stm32mp1/driver/inc/motor_driver.hpp"

#include "platform/stm32mp1/driver/inc/bsp.hpp"

namespace Driver {

Motor::Motor(Driver::Pwm& high_side, Driver::Pwm& low_side)
    : m_high_side{high_side}, m_low_side{low_side} {}

void Motor::setMotorSpeed(float duty_cycle_normalized) {
    if (duty_cycle_normalized > 0.0f) {
        m_high_side.setDutyCycle(duty_cycle_normalized);
        m_low_side.setDutyCycle(0.0f);
    } else {
        m_high_side.setDutyCycle(0.0f);
        m_low_side.setDutyCycle(-duty_cycle_normalized);
    }
}

}  // namespace Driver