#pragma once

#include "common/interface/inc/gpio.hpp"
#include "common/interface/inc/imu.hpp"
#include "common/interface/inc/motor.hpp"
#include "common/interface/inc/uart.hpp"

namespace Common {
namespace Interface {

struct Drivers {
    Drivers(Gpio& inRunLed, Imu& inImu, Uart& inCommunicationUart,
            Motor& inLeftMotor, Motor& inRightMotor)
        : runLed{inRunLed},
          imu{inImu},
          communicationUart{inCommunicationUart},
          leftMotor{inLeftMotor},
          rightMotor{inRightMotor} {};
    Gpio& runLed;
    Imu& imu;
    Uart& communicationUart;
    Motor& leftMotor;
    Motor& rightMotor;
};

enum class Functionality {
    RUN_LED = 0,
    IMU,
    MOTOR_LEFT_HIGH_SIDE,
    MOTOR_LEFT_LOW_SIDE,
    MOTOR_RIGHT_HIGH_SIDE,
    MOTOR_RIGHT_LOW_SIDE,
};

}  // namespace Interface
}  // namespace Common