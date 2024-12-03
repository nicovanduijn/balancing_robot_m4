#pragma once

#include "common/interface/inc/drivers.hpp"
#include "platform/stm32mp1/driver/inc/pwm_driver.hpp"

namespace Driver {

class Motor : public Common::Interface::Motor {
   public:
    Motor(Driver::Pwm& high_side, Driver::Pwm& low_side);

    virtual void setMotorSpeed(float speed_normalized) final;

   private:
    Driver::Pwm& m_high_side;
    Driver::Pwm& m_low_side;
};

}  // namespace Driver
