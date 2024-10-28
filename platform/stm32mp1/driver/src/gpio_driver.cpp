#include "platform/stm32mp1/driver/inc/gpio_driver.hpp"

#include "platform/stm32mp1/driver/inc/bsp.hpp"

namespace Driver {

Gpio::Gpio(Common::Interface::Functionality functionality)
    : m_port{Bsp::getPort(functionality)}, m_pin{Bsp::getPin(functionality)} {}

void Gpio::toggle() { HAL_GPIO_TogglePin(m_port, m_pin); }
void Gpio::on() { HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_SET); }
void Gpio::off() { HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_RESET); }

}  // namespace Driver