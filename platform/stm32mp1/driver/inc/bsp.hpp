#pragma once

#include "common/interface/inc/gpio.hpp"
#include "platform/stm32mp1/generated/CM4/Core/Inc/gpio.h"

namespace Driver {
namespace Bsp {

GPIO_TypeDef* getPort(Common::Interface::Gpio::Function function) {
    (void)function;  // todo: add lookup table!
    return GPIOA;
}

uint16_t getPin(Common::Interface::Gpio::Function function) {
    (void)function;  // todo: add lookup table!
    return GPIO_PIN_14;
}

}  // namespace Bsp
}  // namespace Driver