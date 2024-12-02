#include "common/app/inc/init.hpp"

#include "common/app/inc/imu_poller.hpp"
#include "common/app/inc/run_led.hpp"
#include "common/app/inc/simple_low_pass.hpp"
namespace Common {
namespace App {

void init_application(Common::Interface::Drivers& drivers) {
    static Common::App::RunLed led{drivers.runLed};
    static Common::App::A7Communicator communicator{drivers.communicationUart};
    static Common::App::SimpleLowPass estimator{communicator};
    static Common::App::ImuPoller imuPoller{drivers.imu, estimator,
                                            communicator};
    return;
}

}  // namespace App
}  // namespace Common