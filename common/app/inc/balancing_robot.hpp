#pragma once

#include "common/app/inc/a7_communicator.hpp"
#include "common/interface/inc/controller.hpp"
#include "common/interface/inc/estimator.hpp"
#include "common/interface/inc/imu.hpp"
#include "common/rtos/inc/task.hpp"

namespace Common {
namespace App {

class BalancingRobot : public Rtos::Task {
   public:
    BalancingRobot(Interface::Imu& imu, Interface::Estimator& estimator,
                   Interface::Controller& controller,
                   A7Communicator& a7_communicator);

   private:
    static constexpr uint32_t CONTROL_LOOP_PERIOD_ms = 500u;
    void threadFunction() override;
    Interface::Imu& m_imu;
    Interface::Estimator& m_estimator;
    Interface::Controller& m_controller;
    A7Communicator& m_a7_communicator;
};

}  // namespace App
}  // namespace Common