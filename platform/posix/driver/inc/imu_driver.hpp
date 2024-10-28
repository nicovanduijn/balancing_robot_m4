#pragma once

#include "common/interface/inc/drivers.hpp"

namespace Driver {

class Imu : public Common::Interface::Imu {
   public:
    Imu() = default;
    ~Imu() = default;

    float getXAcceleration_mpss() final;
    float getYAcceleration_mpss() final;
    float getZAcceleration_mpss() final;
    float getXRotationalVelocity_radps() final;
    float getYRotationalVelocity_radps() final;
    float getZRotationalVelocity_radps() final;
};

}  // namespace Driver