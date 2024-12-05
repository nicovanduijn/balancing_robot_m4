#pragma once

#include "common/interface/inc/drivers.hpp"
#include "platform/stm32mp1/generated/CM4/Core/Inc/tim.h"

namespace Driver {

class Pwm {
   public:
    Pwm(Common::Interface::Functionality functionality);

    void setDutyCycle(uint16_t duty_cycle_percent);

   private:
    static constexpr uint32_t PERIOD_PWM_US = 100;
    TIM_HandleTypeDef* m_timer;
    uint32_t m_channel;
};

}  // namespace Driver
