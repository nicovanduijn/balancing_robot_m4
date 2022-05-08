#include "platform/posix/driver/inc/init.hpp"

#include "platform/posix/driver/inc/gpio_driver.hpp"

namespace Driver {
Common::Interface::Drivers init_low_level(void) {
    static Driver::Gpio runled{Common::Interface::Gpio::Function::RUN_LED};
    static Common::Interface::Drivers drivers{runled};
    return drivers;
}

}  // namespace Driver