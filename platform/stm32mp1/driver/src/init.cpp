#include "platform/stm32mp1/driver/inc/init.hpp"

#include "platform/stm32mp1/driver/inc/gpio_driver.hpp"
#include "platform/stm32mp1/driver/inc/mpu6050_driver.hpp"
#include "platform/stm32mp1/driver/inc/uart_module.hpp"

namespace Driver {

Common::Interface::Drivers init_low_level(void) {
    init_hal();

    static Driver::Gpio runled{Common::Interface::Functionality::RUN_LED};
    static Driver::Mpu6050 imu{Common::Interface::Functionality::IMU};
    static UARTModule uart{imu};

    static Common::Interface::Drivers drivers{runled, imu};
    return drivers;
}

}  // namespace Driver