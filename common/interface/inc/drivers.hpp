#pragma once

#include "common/interface/inc/gpio.hpp"
#include "common/interface/inc/imu.hpp"
#include "common/interface/inc/uart.hpp"

namespace Common {
namespace Interface {

struct Drivers {
    Drivers(Gpio& inRunLed, Imu& inImu, Uart& inCommunicationUart)
        : runLed{inRunLed},
          imu{inImu},
          communicationUart{inCommunicationUart} {};
    Gpio& runLed;
    Imu& imu;
    Uart& communicationUart;
};

enum class Functionality {
    RUN_LED = 0,
    IMU,
};

}  // namespace Interface
}  // namespace Common