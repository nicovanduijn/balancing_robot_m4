#include "platform/posix/driver/inc/imu_driver.hpp"

namespace Driver {

Eigen::Vector3f Imu::getAcceleration_mpss() { return Eigen::Vector3f::Zero(); }
Eigen::Vector3f Imu::getRotationalVelocity_radps() {
    return Eigen::Vector3f::Zero();
}

}  // namespace Driver