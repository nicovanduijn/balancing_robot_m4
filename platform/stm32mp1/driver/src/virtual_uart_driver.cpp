/*
 * VirtualUart.cpp
 *
 *  Created on: Nov 18, 2024
 *      Author: dluk
 */

#include "platform/stm32mp1/driver/inc/virtual_uart_driver.hpp"

namespace Driver {

VIRT_UART_HandleTypeDef VirtualUart::m_huart0{};
__IO FlagStatus VirtualUart::m_virtUart0RxMsg{RESET};
Common::Interface::Uart::RxCompleteCallback VirtualUart::m_rxCompleteCallback{
    nullptr};

VirtualUart::VirtualUart() {
    if (VIRT_UART_Init(&m_huart0) != VIRT_UART_OK) {
        log_err("VIRT_UART_Init UART0 failed.\r\n");
        Error_Handler();
    }
    log_info("Virtual UART0 OpenAMP-rpmsg channel creation\r\n");

    if (VIRT_UART_RegisterCallback(&m_huart0, VIRT_UART_RXCPLT_CB_ID,
                                   virtualUartRxCompleteCallback) !=
        VIRT_UART_OK) {
        Error_Handler();
    }
}

VirtualUart::~VirtualUart() {}

bool VirtualUart::transmit(const uint8_t *const transmitBuffer,
                           std::size_t numberOfBytesToTransmit) {
    OPENAMP_check_for_message(); // Needs to be called periodically for Rx to work, so until we have an independent polling task, this is required
    VIRT_UART_Transmit(&m_huart0, transmitBuffer, numberOfBytesToTransmit);
    return true;
}

void VirtualUart::registerRxCompleteCallback(
    const RxCompleteCallback &callbackToRegister) {
    m_rxCompleteCallback = callbackToRegister;
}

bool VirtualUart::getReceivedBytes(uint8_t *const receiveBuffer,
                                   std::size_t numberOfBytesToReceive) {
    if (m_virtUart0RxMsg && numberOfBytesToReceive <= m_huart0.RxXferSize) {
        memcpy(receiveBuffer, m_huart0.pRxBuffPtr, numberOfBytesToReceive);
        m_virtUart0RxMsg = RESET;
        return true;
    }
    return false;
}

void VirtualUart::virtualUartRxCompleteCallback(
    VIRT_UART_HandleTypeDef *huart) {
    m_virtUart0RxMsg = SET;
    if (m_rxCompleteCallback) {
        m_rxCompleteCallback(huart->RxXferSize);
    }
    log_info("Virtual UART received %d bytes\n\r", huart->RxXferSize);
}

}  // namespace Driver