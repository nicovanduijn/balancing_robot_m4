#pragma once

#include "common/interface/inc/estimator.hpp"


namespace Common {
namespace App {

class SimpleLowPass : public Interface::Estimator {
   public:
    SimpleLowPass();
    ~SimpleLowPass();

    virtual void addAccelerometerMeasurement(const Eigen::Vector3f& measurement) final;
    virtual void addGyroscopeMeasurement(const Eigen::Vector3f& measurement) final;
    virtual void addOdometryTick(Wheel wheel) final;
    virtual void setAccelerometerOffsets(const Eigen::Vector3f& offsets) final;
    virtual void setGyroscopeOffsets(const Eigen::Vector3f& offsets) final;
    virtual Eigen::Vector4f getCurrentState() final;

    void setEstimatorParameters(float alpha);


   private:
    Eigen::Vector4f m_current_state{0.0f, 0.0f, 0.0f, 0.0f}; // currently, only updating x[2] (theta) and x[3] (theta_dot)
    Eigen::Vector3f m_accelerometer_offsets{0.0f, 0.0f, 0.0f};
    Eigen::Vector3f m_gyroscope_offsets{0.0f, 0.0f, 0.0f};
    float m_alpha{0.1f};

};

}  // namespace App
}  // namespace Common