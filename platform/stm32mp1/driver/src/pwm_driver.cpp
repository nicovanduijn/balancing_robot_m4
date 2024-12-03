#include "platform/stm32mp1/driver/inc/pwm_driver.hpp"

#include "platform/stm32mp1/driver/inc/bsp.hpp"

namespace Driver {

Pwm::Pwm(Common::Interface::Functionality functionality)
    : m_timer{Bsp::getTimHandle(functionality)},
      m_channel{Bsp::getTimChannel(functionality)} {}

void Pwm::setDutyCycle(uint16_t duty_cycle_percent) {
    m_timer->Instance->CNT = 0;

    uint32_t pulse = static_cast<uint32_t>(
        (duty_cycle_percent * (m_timer->Instance->ARR + 1)) / PERIOD_PWM_US +
        0.5f);

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(m_timer, &sConfigOC, m_channel);
    HAL_TIM_PWM_Start(m_timer, m_channel);
}

}  // namespace Driver