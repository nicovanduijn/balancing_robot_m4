/*
 * UARTModule.h
 *
 *  Created on: Nov 18, 2024
 *      Author: dluk
 */
#pragma once

#include "common/interface/inc/drivers.hpp"
#include "extern/serialcomlib/serial_com_lib.h"
#include "openamp.h"

extern "C" {
#include "openamp_log.h"
#include "virt_uart.h"

extern void Error_Handler(void);
}

namespace Driver {
class VirtualUart : public Common::Interface::Uart {
   public:
    VirtualUart();
    VirtualUart(const VirtualUart&) = delete;
    VirtualUart& operator=(const VirtualUart&) = delete;
    virtual ~VirtualUart();

    bool transmit(const uint8_t* const transmitBuffer,
                  std::size_t numberOfBytesToTransmit) final;
    void registerRxCompleteCallback(
        const RxCompleteCallback& callbackToRegister) final;
    bool getReceivedBytes(uint8_t* const receiveBuffer,
                          std::size_t numberOfBytesToReceive) final;

   private:
    static VIRT_UART_HandleTypeDef m_huart0;
    static __IO FlagStatus m_virtUart0RxMsg;
    static RxCompleteCallback m_rxCompleteCallback;

    static void virtualUartRxCompleteCallback(VIRT_UART_HandleTypeDef* huart);
};
}  // namespace Driver