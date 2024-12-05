#include "platform/stm32mp1/driver/inc/init.hpp"

#include "platform/stm32mp1/driver/inc/gpio_driver.hpp"
#include "platform/stm32mp1/driver/inc/motor_driver.hpp"
#include "platform/stm32mp1/driver/inc/mpu6050_driver.hpp"
#include "platform/stm32mp1/driver/inc/pwm_driver.hpp"
#include "platform/stm32mp1/driver/inc/virtual_uart_driver.hpp"

namespace Driver {

Common::Interface::Drivers init_low_level(void) {
    init_hal();

    static Driver::Gpio runled{Common::Interface::Functionality::RUN_LED};
    static Driver::Mpu6050 imu{Common::Interface::Functionality::IMU};
    static Driver::VirtualUart uart{};
    static Driver::Pwm pwm_left_high{
        Common::Interface::Functionality::MOTOR_LEFT_HIGH_SIDE};
    static Driver::Pwm pwm_left_low{
        Common::Interface::Functionality::MOTOR_LEFT_LOW_SIDE};
    static Driver::Pwm pwm_right_high{
        Common::Interface::Functionality::MOTOR_RIGHT_HIGH_SIDE};
    static Driver::Pwm pwm_right_low{
        Common::Interface::Functionality::MOTOR_RIGHT_LOW_SIDE};
    static Driver::Motor motorLeft{pwm_left_high, pwm_left_low};
    static Driver::Motor motorRight{pwm_right_high, pwm_right_low};

    static Common::Interface::Drivers drivers{runled, imu, uart, motorLeft,
                                              motorRight};
    return drivers;
}

}  // namespace Driver