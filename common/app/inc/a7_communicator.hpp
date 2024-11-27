#pragma once
#include <stdint.h>

#include <vector>

#include "common/interface/inc/uart.hpp"
#include "extern/serialcomlib/serial_com_lib.h"

namespace Common {
namespace App {

class A7Communicator {
   public:
    using NotificationCallback = std::function<void()>;
    using CallbackRegistrationId = uint8_t;

    A7Communicator(Interface::Uart& uart);
    ~A7Communicator();

    CallbackRegistrationId subscribeToDataId(SCOM_DataIdsEnum dataId,
                                             NotificationCallback callback);
    void unsubscribefromDataId(CallbackRegistrationId id);

    void sendAngle(int16_t targetAngle, int16_t actualAngle);
    void sendBatteryLevel(uint8_t batteryLevel);
    void sendCpu2Temp(uint16_t cpu2Temp);
    void sendDebug(float floatDebugVal1, float floatDebugVal2,
                   float floatDebugVal3, float floatDebugVal4);

    SCOM_ControlPIDValues getControlPIDValues();
    SCOM_ControlOnOff getControlOnOff();
    SCOM_ControlCalibration getControlCalibration();

   private:
    Interface::Uart& m_uart;
    std::vector<std::pair<SCOM_DataIdsEnum, NotificationCallback>> m_callbacks;
    std::array<uint8_t, SCOM_MAX_MESSAGE_SIZE> m_receiveBuffer;
};

}  // namespace App
}  // namespace Common