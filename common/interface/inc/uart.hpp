#pragma once
#include <stdint.h>

#include <functional>

namespace Common {
namespace Interface {

class Uart {
   public:
    using RxCompleteCallback = std::function<void(uint16_t numBytesReceived)>;

    virtual ~Uart() = default;

    // Buffer gets copied so is safe to be destroyed when this function returns
    virtual bool transmit(const uint8_t* const transmitBuffer,
                          std::size_t numberOfBytesToTransmit) = 0;

    virtual void registerRxCompleteCallback(
        const RxCompleteCallback& callbackToRegister) = 0;

    virtual bool getReceivedBytes(
        uint8_t* const receiveBuffer,
        std::size_t maximumNumberOfBytesToReceive) = 0;
};

}  // namespace Interface
}  // namespace Common