#pragma once

#include "common/interface/inc/gpio.hpp"
#include "common/interface/inc/imu.hpp"

namespace Common {
namespace Interface {

struct Drivers {
    Drivers(Gpio& inRunLed, Imu& inImu) : runLed{inRunLed}, imu{inImu} {};
    Gpio& runLed;
    Imu& imu;
};

enum class Functionality {
    RUN_LED = 0,
    IMU,
};

}  // namespace Interface
}  // namespace Common