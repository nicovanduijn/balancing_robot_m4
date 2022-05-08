#include "platform/stm32mp1/driver/inc/init.hpp"

#include "platform/stm32mp1/driver/inc/gpio_driver.hpp"

namespace Driver {

Common::Interface::Drivers init_low_level(void) {
    init_hal();

    static Driver::Gpio runled{Common::Interface::Gpio::Function::RUN_LED};

    static Common::Interface::Drivers drivers{runled};
    return drivers;
}

}  // namespace Driver