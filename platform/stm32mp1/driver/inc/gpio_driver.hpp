#pragma once

#include "common/interface/inc/gpio.hpp"
#include "platform/stm32mp1/generated/CM4/Inc/gpio.h"

namespace Driver {

class Gpio : public Common::Interface::Gpio {
   public:
    Gpio(Common::Interface::Gpio::Function function);

    virtual void toggle() final;
    virtual void on() final;
    virtual void off() final;

   private:
    GPIO_TypeDef* m_port;
    uint16_t m_pin;
};

}  // namespace Driver
