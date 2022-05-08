#pragma once

#include "common/interface/inc/gpio.hpp"

namespace Common {
namespace Interface {

struct Drivers {
    Drivers(Gpio& inRunLed) : runLed{inRunLed} {};
    Gpio& runLed;
};

}  // namespace Interface
}  // namespace Common