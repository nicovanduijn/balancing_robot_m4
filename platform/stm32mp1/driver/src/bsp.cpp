#include "platform/stm32mp1/driver/inc/bsp.hpp"

namespace Driver {
namespace Bsp {

GPIO_TypeDef* getPort(Common::Interface::Functionality functionality) {
    (void)functionality;  // todo: add lookup table!
    return GPIOA;
}

uint16_t getPin(Common::Interface::Functionality functionality) {
    (void)functionality;  // todo: add lookup table!
    return GPIO_PIN_13;
}

I2C_HandleTypeDef* getI2CHandle(
    Common::Interface::Functionality functionality) {
    (void)functionality;  // todo:: add lookup table
    return &hi2c5;
}

}  // namespace Bsp
}  // namespace Driver