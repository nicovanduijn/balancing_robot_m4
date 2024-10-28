#pragma once

#include "common/interface/inc/drivers.hpp"
#include "platform/stm32mp1/generated/CM4/Core/Inc/gpio.h"
#include "platform/stm32mp1/generated/CM4/Core/Inc/i2c.h"

namespace Driver {
namespace Bsp {

GPIO_TypeDef* getPort(Common::Interface::Functionality functionality);

uint16_t getPin(Common::Interface::Functionality functionality);

I2C_HandleTypeDef* getI2CHandle(Common::Interface::Functionality functionality);

}  // namespace Bsp
}  // namespace Driver