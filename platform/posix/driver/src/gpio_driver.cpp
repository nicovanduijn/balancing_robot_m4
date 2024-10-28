#include "platform/posix/driver/inc/gpio_driver.hpp"

namespace Driver {

void Gpio::toggle() { m_state = !m_state; }
void Gpio::on() { m_state = true; }
void Gpio::off() { m_state = false; }

}  // namespace Driver