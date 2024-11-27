#include "common/app/inc/a7_communicator.hpp"

namespace Common {
namespace App {

A7Communicator::A7Communicator(Interface::Uart& uart) : m_uart{uart} {
    m_uart.registerRxCompleteCallback([this](uint16_t numBytesReceived) {
        if (numBytesReceived > m_receiveBuffer.size()) {
            return;
        }
        m_uart.getReceivedBytes(m_receiveBuffer.data(), numBytesReceived);
        SCOM_DataIdsEnum dataId =
            SCOM_deserialize_data_id(m_receiveBuffer.data(), numBytesReceived);
        for (auto& callback : m_callbacks) {
            if (callback.first == dataId) {
                callback.second();
            }
        }
    });
}

A7Communicator::~A7Communicator() { m_callbacks.clear(); }

A7Communicator::CallbackRegistrationId A7Communicator::subscribeToDataId(
    SCOM_DataIdsEnum dataId, NotificationCallback callback) {
    m_callbacks.push_back(std::make_pair(dataId, callback));
    return m_callbacks.size() - 1;
}

void A7Communicator::unsubscribefromDataId(CallbackRegistrationId id) {
    for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it) {
        if (it->first == id) {
            m_callbacks.erase(it);
            break;
        }
    }
}

void A7Communicator::sendAngle(int16_t targetAngle, int16_t actualAngle) {
    uint8_t buffer[SCOM_INFO_ANGLES_SIZE];
    SCOM_serialize_info_angle(buffer, SCOM_INFO_ANGLES_SIZE, targetAngle,
                              actualAngle);
    m_uart.transmit(buffer, SCOM_INFO_ANGLES_SIZE);
}

void A7Communicator::sendBatteryLevel(uint8_t batteryLevel) {
    uint8_t buffer[SCOM_INFO_BATTERYLEVEL_SIZE];
    SCOM_serialize_info_bat_level(buffer, SCOM_INFO_BATTERYLEVEL_SIZE,
                                  batteryLevel);
    m_uart.transmit(buffer, SCOM_INFO_BATTERYLEVEL_SIZE);
}

void A7Communicator::sendCpu2Temp(uint16_t cpu2Temp) {
    uint8_t buffer[SCOM_INFO_CPU2TEMP_SIZE];
    SCOM_serialize_info_cpu2_temp(buffer, SCOM_INFO_CPU2TEMP_SIZE, cpu2Temp);
    m_uart.transmit(buffer, SCOM_INFO_CPU2TEMP_SIZE);
}

void A7Communicator::sendDebug(float floatDebugVal1, float floatDebugVal2,
                               float floatDebugVal3, float floatDebugVal4) {
    uint8_t buffer[SCOM_INFO_DEBUG_SIZE];
    SCOM_serialize_info_debug(buffer, SCOM_INFO_DEBUG_SIZE, floatDebugVal1,
                              floatDebugVal2, floatDebugVal3, floatDebugVal4);
    m_uart.transmit(buffer, SCOM_INFO_DEBUG_SIZE);
}

SCOM_ControlPIDValues A7Communicator::getControlPIDValues() {
    SCOM_ControlPIDValues controlPIDValues;
    SCOM_deserialize_control_pid_values(
        m_receiveBuffer.data(), SCOM_CONTROL_PIDVALUES_SIZE, &controlPIDValues);
    return controlPIDValues;
}

SCOM_ControlOnOff A7Communicator::getControlOnOff() {
    SCOM_ControlOnOff controlOnOff;
    SCOM_deserialize_control_on_off(m_receiveBuffer.data(),
                                    SCOM_CONTROL_ONOFF_SIZE, &controlOnOff);
    return controlOnOff;
}

SCOM_ControlCalibration A7Communicator::getControlCalibration() {
    SCOM_ControlCalibration controlCalibration;
    SCOM_deserialize_control_calibration(m_receiveBuffer.data(),
                                         SCOM_CONTROL_CALIBRATION_SIZE,
                                         &controlCalibration);
    return controlCalibration;
}

}  // namespace App
}  // namespace Common