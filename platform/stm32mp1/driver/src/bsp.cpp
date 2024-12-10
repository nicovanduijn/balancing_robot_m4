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

/*
        pwmM1A(&htim5, TIM_CHANNEL_2, GPIOH, GPIO_PIN_11), //PH11
        pwmM1B(&htim4, TIM_CHANNEL_3, GPIOD, GPIO_PIN_14), //PD14
        pwmM2A(&htim3, TIM_CHANNEL_2, GPIOC, GPIO_PIN_7), //PC7
        pwmM2B(&htim12, TIM_CHANNEL_1, GPIOH, GPIO_PIN_6),  //PH6
*/

TIM_HandleTypeDef* getTimHandle(
    Common::Interface::Functionality functionality) {
    switch (functionality) {
        case Common::Interface::Functionality::MOTOR_LEFT_HIGH_SIDE:
            return &htim4;
        case Common::Interface::Functionality::MOTOR_LEFT_LOW_SIDE:
            return &htim5;
        case Common::Interface::Functionality::MOTOR_RIGHT_HIGH_SIDE:
            return &htim3;
        case Common::Interface::Functionality::MOTOR_RIGHT_LOW_SIDE:
            return &htim12;
        default:
            return nullptr;
    }
}

uint32_t getTimChannel(Common::Interface::Functionality functionality) {
    switch (functionality) {
        case Common::Interface::Functionality::MOTOR_LEFT_HIGH_SIDE:
            return TIM_CHANNEL_3;
        case Common::Interface::Functionality::MOTOR_LEFT_LOW_SIDE:
            return TIM_CHANNEL_2;
        case Common::Interface::Functionality::MOTOR_RIGHT_HIGH_SIDE:
            return TIM_CHANNEL_2;
        case Common::Interface::Functionality::MOTOR_RIGHT_LOW_SIDE:
            return TIM_CHANNEL_1;
        default:
            return 0;
    }
}

}  // namespace Bsp
}  // namespace Driver