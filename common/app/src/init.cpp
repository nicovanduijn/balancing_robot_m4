#include "common/app/inc/init.hpp"

#include "common/app/inc/imu_poller.hpp"
#include "common/app/inc/run_led.hpp"

namespace Common {
namespace App {

void init_application(Common::Interface::Drivers& drivers) {
    static Common::App::RunLed led{drivers.runLed};
    static Common::App::ImuPoller imuPoller{drivers.imu};
    return;
}

}  // namespace App
}  // namespace Common