#pragma once

#include "common/interface/inc/gpio.hpp"
#include "common/rtos/inc/task.hpp"

namespace Common {
namespace App {

class RunLed : public Rtos::Task {
   public:
    RunLed(Interface::Gpio& gpio);

   private:
    static constexpr uint32_t BLINK_PERIOD_ms = 500u;
    void threadFunction() override;
    Interface::Gpio& m_led;
};

}  // namespace App
}  // namespace Common