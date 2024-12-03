#include "common/app/inc/pid.hpp"

namespace Common {
namespace App {

Pid::Pid(A7Communicator& a7_communicator)
    : m_a7_communicator{a7_communicator} {}
Pid::~Pid() {}

void Pid::setCurrentState(const Eigen::Vector4f& state) {
    m_current_state = state;
}

void Pid::setDesiredState(const Eigen::Vector4f& state) {
    m_desired_state = state;
}

float Pid::getControl() {
    auto p_control = m_kp * (m_desired_state(2) - m_current_state(2));
    m_integral +=
        m_ki * (m_desired_state(2) - m_current_state(2)) * TIMESTEP_MS;
    auto d_control = m_kd * (m_desired_state(3) - m_current_state(3));

    return p_control + m_integral + d_control;
}

}  // namespace App
}  // namespace Common