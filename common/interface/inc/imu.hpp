#pragma once
#include <extern/eigen/Eigen/Dense>
namespace Common {
namespace Interface {

class Imu {
   public:
    virtual ~Imu() = default;

    virtual Eigen::Vector3f getAcceleration_mpss() = 0;
    virtual Eigen::Vector3f getRotationalVelocity_radps() = 0;

};

}  // namespace Interface
}  // namespace Common