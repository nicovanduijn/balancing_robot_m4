#include "common/app/inc/init.hpp"

#include "common/app/inc/balancing_robot.hpp"
#include "common/app/inc/pid.hpp"
#include "common/app/inc/run_led.hpp"
#include "common/app/inc/simple_low_pass.hpp"
namespace Common {
namespace App {

void init_application(Common::Interface::Drivers& drivers) {
    static Common::App::RunLed led{drivers.runLed};
    static Common::App::A7Communicator communicator{drivers.communicationUart};
    static Common::App::SimpleLowPass simple_low_pass_filter{communicator};
    static Common::App::Pid simple_pid_controller{communicator};
    static Common::App::BalancingRobot main_logic{
        drivers.imu,       simple_low_pass_filter, simple_pid_controller,
        drivers.leftMotor, drivers.rightMotor,     communicator};
    return;
}

}  // namespace App
}  // namespace Common