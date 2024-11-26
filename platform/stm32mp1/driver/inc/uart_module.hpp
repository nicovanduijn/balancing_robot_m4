/*
 * UARTModule.h
 *
 *  Created on: Nov 18, 2024
 *      Author: dluk
 */
#pragma once

#include "common/interface/inc/drivers.hpp"
#include "openamp.h"  //includes the extern C defines itself
#include "extern/serialcomlib/serial_com_lib.h"
// #include "MotorModule.h"
// #include "PIDModule.h"
#include "common/rtos/inc/task.hpp"

extern "C" {
	#include "openamp_log.h"
	#include "virt_uart.h"
	#include "openamp_log.h"

	extern void Error_Handler(void);
}


class UARTModule : public Common::Rtos::Task{
public:
    // // Public method to access the singleton instance
    // static UARTModule& getInstance(//PIDModule& pid, MotorModule& motor, 
	// 	Common::Interface::Imu& imu) {
    //     if (!instance) {
    //     	instance = new UARTModule(//pid, motor, 
	// 		imu);
    //     }
    //     return *instance;
    // }
	    UARTModule(//PIDModule& pid, MotorModule& motor, 
	Common::Interface::Imu& imu);

    // Deleted methods to prevent copying or assigning the singleton
    UARTModule(const UARTModule&) = delete;
    UARTModule& operator=(const UARTModule&) = delete;




    virtual ~UARTModule();

	void threadFunction() override;

private:

	
	void processRx();
    void processTx();

    static UARTModule* instance;

	// PIDModule& pidModule;
	// MotorModule& motorModule;
	Common::Interface::Imu& m_imu;// IMUModule& imuModule;
	

	static const uint16_t MAX_BUFFER_SIZE = RPMSG_BUFFER_SIZE;
	VIRT_UART_HandleTypeDef huart0;
	static __IO FlagStatus VirtUart0RxMsg;
	static uint8_t VirtUart0ChannelBuffRx[MAX_BUFFER_SIZE];
	static uint16_t VirtUart0ChannelRxSize;
	bool uart_init_done = false;

	static void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);
	void processData(uint8_t *rxBuffer, size_t rxBufferSize);
};

