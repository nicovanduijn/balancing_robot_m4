#include "common/app/inc/run_led.hpp"

namespace Common {
namespace App {

RunLed::RunLed(Interface::Gpio& gpio)
    : Task{"runLed", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},
      m_led{gpio} {
    m_led.toggle();
}

void RunLed::threadFunction() {
    for (;;) {
        m_led.toggle();
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_ms));
    }
}
}  // namespace App
}  // namespace Common