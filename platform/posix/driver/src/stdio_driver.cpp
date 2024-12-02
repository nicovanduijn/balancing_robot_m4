#include "platform/posix/driver/inc/stdio_driver.hpp"

#include <iostream>

namespace Driver {

Common::Interface::Uart::RxCompleteCallback StdIo::m_rxCompleteCallback{
    nullptr};

StdIo::StdIo() {}

StdIo::~StdIo() {}

bool StdIo::transmit(const uint8_t *const transmitBuffer,
                     std::size_t numberOfBytesToTransmit) {
    for (std::size_t i = 0; i < numberOfBytesToTransmit; i++) {
        std::cout << transmitBuffer[i];
    }
    return true;
}

void StdIo::registerRxCompleteCallback(
    const RxCompleteCallback &callbackToRegister) {
    m_rxCompleteCallback = callbackToRegister;
}

bool StdIo::getReceivedBytes(uint8_t *const receiveBuffer,
                             std::size_t numberOfBytesToReceive) {
    return true;
}

}  // namespace Driver