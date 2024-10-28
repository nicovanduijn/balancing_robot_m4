#pragma once

namespace Common {
namespace Interface {

class Imu {
   public:
    virtual ~Imu() = default;

    virtual float getXAcceleration_mpss() = 0;
    virtual float getYAcceleration_mpss() = 0;
    virtual float getZAcceleration_mpss() = 0;
    virtual float getXRotationalVelocity_radps() = 0;
    virtual float getYRotationalVelocity_radps() = 0;
    virtual float getZRotationalVelocity_radps() = 0;
};

}  // namespace Interface
}  // namespace Common