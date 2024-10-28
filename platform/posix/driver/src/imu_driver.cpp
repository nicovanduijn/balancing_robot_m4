#include "platform/posix/driver/inc/imu_driver.hpp"

namespace Driver {

float Imu::getXAcceleration_mpss() { return 0.f; }
float Imu::getYAcceleration_mpss() { return 0.f; }
float Imu::getZAcceleration_mpss() { return 0.f; }
float Imu::getXRotationalVelocity_radps() { return 0.f; }
float Imu::getYRotationalVelocity_radps() { return 0.f; }
float Imu::getZRotationalVelocity_radps() { return 0.f; }

}  // namespace Driver