#include "platform/posix/driver/inc/init.hpp"

#include "platform/posix/driver/inc/gpio_driver.hpp"
#include "platform/posix/driver/inc/imu_driver.hpp"
#include "platform/posix/driver/inc/motor_driver.hpp"
#include "platform/posix/driver/inc/stdio_driver.hpp"

namespace Driver {
Common::Interface::Drivers init_low_level(void) {
    static Driver::Gpio runled{Common::Interface::Functionality::RUN_LED};
    static Driver::Imu imu;
    static Driver::StdIo stdio;
    static Driver::Motor motorLeft;
    static Driver::Motor motorRight;
    static Common::Interface::Drivers drivers{runled, imu, stdio, motorLeft,
                                              motorRight};
    return drivers;
}

}  // namespace Driver