#include "common/app/inc/simple_low_pass.hpp"

#include <math.h>

namespace Common {
namespace App {

SimpleLowPass::SimpleLowPass(A7Communicator& a7_communicator)
    : m_a7_communicator{a7_communicator} {
    m_a7_communicator.subscribeToDataId(SCOM_ID_PID_VALUES, [this](void) {
        auto controlPIDValues = m_a7_communicator.getControlPIDValues();
        setEstimatorParameters(controlPIDValues.K_comp_filter);
    });
}

SimpleLowPass::~SimpleLowPass() {}

void SimpleLowPass::addAccelerometerMeasurement(
    const Eigen::Vector3f& measurement) {
    const Eigen::Vector3f corrected_measurement =
        measurement - m_accelerometer_offsets;
    const float measured_pitch = 1.5708f -
        atan2(corrected_measurement.z(), corrected_measurement.x());
    m_current_state(Interface::Estimator::ControlState::THETA) =
        m_alpha * measured_pitch +
        (1.0f - m_alpha) *
            m_current_state(Interface::Estimator::ControlState::THETA);
}

void SimpleLowPass::addGyroscopeMeasurement(
    const Eigen::Vector3f& measurement) {
    m_current_state(Interface::Estimator::ControlState::THETA_DOT) =
        measurement[1] - m_gyroscope_offsets[1];
}

void SimpleLowPass::addOdometryTick(Wheel wheel) {
    // unimplemented
}

void SimpleLowPass::setAccelerometerOffsets(const Eigen::Vector3f& offsets) {
    m_accelerometer_offsets = offsets;
}

void SimpleLowPass::setGyroscopeOffsets(const Eigen::Vector3f& offsets) {
    m_gyroscope_offsets = offsets;
}

Eigen::Vector4f SimpleLowPass::getCurrentState() { return m_current_state; }

void SimpleLowPass::setEstimatorParameters(float alpha) { m_alpha = alpha; }

}  // namespace App
}  // namespace Common