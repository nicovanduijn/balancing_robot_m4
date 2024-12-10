#pragma once

#include "common/app/inc/a7_communicator.hpp"
#include "common/interface/inc/controller.hpp"
#include "common/interface/inc/estimator.hpp"
#include "common/interface/inc/imu.hpp"
#include "common/interface/inc/motor.hpp"
#include "common/rtos/inc/task.hpp"

namespace Common {
namespace App {

class BalancingRobot : public Rtos::Task {
   public:
    BalancingRobot(Interface::Imu& imu, Interface::Estimator& estimator,
                   Interface::Controller& controller,
                   Interface::Motor& left_motor, Interface::Motor& right_motor,
                   A7Communicator& a7_communicator);

   private:
    static constexpr uint32_t CONTROL_LOOP_PERIOD_ms = 50u;
    uint32_t m_comm_loop_counter = 0U;
    void threadFunction() override;
    Interface::Imu& m_imu;
    Interface::Estimator& m_estimator;
    Interface::Controller& m_controller;
    Interface::Motor& m_left_motor;
    Interface::Motor& m_right_motor;
    A7Communicator& m_a7_communicator;
};

}  // namespace App
}  // namespace Common