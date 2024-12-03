#pragma once

#include "common/interface/inc/drivers.hpp"

namespace Driver {

class Motor : public Common::Interface::Motor {
   public:
    Motor(){};

    virtual void setMotorSpeed(float speed_normalized) final;

   private:
    float m_speed_normalized{0.0};
};

}  // namespace Driver
