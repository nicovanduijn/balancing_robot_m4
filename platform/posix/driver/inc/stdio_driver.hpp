
#pragma once

#include "common/interface/inc/drivers.hpp"

namespace Driver {
class StdIo : public Common::Interface::Uart {
   public:
    StdIo();
    StdIo(const StdIo&) = delete;
    StdIo& operator=(const StdIo&) = delete;
    virtual ~StdIo();

    bool transmit(const uint8_t* const transmitBuffer,
                  std::size_t numberOfBytesToTransmit) final;
    void registerRxCompleteCallback(
        const RxCompleteCallback& callbackToRegister) final;
    bool getReceivedBytes(uint8_t* const receiveBuffer,
                          std::size_t numberOfBytesToReceive) final;

   private:
    static RxCompleteCallback m_rxCompleteCallback;
};
}  // namespace Driver