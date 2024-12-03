#pragma once

#include "common/app/inc/a7_communicator.hpp"
#include "common/interface/inc/estimator.hpp"

namespace Common {
namespace App {

class SimpleLowPass : public Interface::Estimator {
   public:
    SimpleLowPass(A7Communicator& a7_communicator);
    ~SimpleLowPass();

    virtual void addAccelerometerMeasurement(
        const Eigen::Vector3f& measurement) final;
    virtual void addGyroscopeMeasurement(
        const Eigen::Vector3f& measurement) final;
    virtual void addOdometryTick(Wheel wheel) final;
    virtual void setAccelerometerOffsets(const Eigen::Vector3f& offsets) final;
    virtual void setGyroscopeOffsets(const Eigen::Vector3f& offsets) final;
    virtual Eigen::Vector4f getCurrentState() final;

    void setEstimatorParameters(float alpha);

   private:
    Eigen::Vector4f m_current_state{0.0f, 0.0f, 0.0f, 0.0f};
    Eigen::Vector3f m_accelerometer_offsets{0.0f, 0.0f, 0.0f};
    Eigen::Vector3f m_gyroscope_offsets{0.0f, 0.0f, 0.0f};
    float m_alpha{0.98f};
    A7Communicator& m_a7_communicator;
};

}  // namespace App
}  // namespace Common