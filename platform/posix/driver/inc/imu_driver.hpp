#pragma once

#include "common/interface/inc/drivers.hpp"

namespace Driver {

class Imu : public Common::Interface::Imu {
   public:
    Imu() = default;
    ~Imu() = default;

    Eigen::Vector3f getAcceleration_mpss() final;
    Eigen::Vector3f getRotationalVelocity_radps() final;
};

}  // namespace Driver