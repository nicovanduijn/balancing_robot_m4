#include "common/app/inc/init.hpp"
#include "common/interface/inc/drivers.hpp"
#include "common/rtos/inc/freertos_hooks.hpp"

namespace Driver {
extern Common::Interface::Drivers init_low_level(void);
}

int main(int argc, char** argv) {
    auto drivers = Driver::init_low_level();
    Common::App::init_application(drivers);

    vTaskStartScheduler();
    for (;;) {
    }

    (void)argc;
    (void)argv;
    return 0;
}