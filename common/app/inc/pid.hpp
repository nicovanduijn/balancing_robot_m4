#pragma once

#include "common/app/inc/a7_communicator.hpp"
#include "common/interface/inc/controller.hpp"

namespace Common {
namespace App {

class Pid : public Interface::Controller {
   public:
    Pid(A7Communicator& a7_communicator);
    ~Pid();

    virtual void setCurrentState(const Eigen::Vector4f& state) final;
    virtual void setDesiredState(const Eigen::Vector4f& state) final;
    virtual float getControl() final;

   private:
    static constexpr float TIMESTEP_MS = 500.0f;  // todo: get from rtos
    Eigen::Vector4f m_current_state{0.0f, 0.0f, 0.0f, 0.0f};
    Eigen::Vector4f m_desired_state{0.0f, 0.0f, 0.0f, 0.0f};
    float m_kp{0.0f};
    float m_ki{0.0f};
    float m_kd{0.0f};
    float m_integral{0.0f};
    A7Communicator& m_a7_communicator;
};

}  // namespace App
}  // namespace Common