#pragma once
#include <extern/eigen/Eigen/Dense>

namespace Common {
namespace Interface {

class Estimator {
   public:
    virtual ~Estimator() = default;

    enum class Wheel { LEFT, RIGHT };

    enum ControlState : uint8_t { X = 0, X_DOT, THETA, THETA_DOT };

    virtual void addAccelerometerMeasurement(
        const Eigen::Vector3f& measurement) = 0;
    virtual void addGyroscopeMeasurement(
        const Eigen::Vector3f& measurement) = 0;
    virtual void addOdometryTick(Wheel wheel) = 0;
    virtual void setAccelerometerOffsets(const Eigen::Vector3f& offsets) = 0;
    virtual void setGyroscopeOffsets(const Eigen::Vector3f& offsets) = 0;

    // System state is defined as [x, x_dot, theta, theta_dot]
    virtual Eigen::Vector4f getCurrentState() = 0;
    virtual void setEstimatorParameters(float filter_coefficient) = 0;
};

}  // namespace Interface
}  // namespace Common