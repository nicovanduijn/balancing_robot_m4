/*
 * UARTModule.cpp
 *
 *  Created on: Nov 18, 2024
 *      Author: dluk
 */

#include "platform/stm32mp1/driver/inc/uart_module.hpp"

UARTModule* UARTModule::instance = nullptr;
__IO FlagStatus UARTModule::VirtUart0RxMsg = RESET;
uint8_t UARTModule::VirtUart0ChannelBuffRx[MAX_BUFFER_SIZE] = {0};
uint16_t UARTModule::VirtUart0ChannelRxSize = 0;

UARTModule::UARTModule(Common::Interface::Imu& imu):
	// pidModule(pid),
	// motorModule(motor),
	Task{"UARTModule", configMINIMAL_STACK_SIZE, configDEFAULT_TASK_PRIO},m_imu(imu)
{

	if (VIRT_UART_Init(&huart0) != VIRT_UART_OK) {
		log_err("VIRT_UART_Init UART0 failed.\r\n");
		Error_Handler();
	}
	log_info("Virtual UART0 OpenAMP-rpmsg channel creation\r\n");


	if(VIRT_UART_RegisterCallback(&huart0, VIRT_UART_RXCPLT_CB_ID, VIRT_UART0_RxCpltCallback) != VIRT_UART_OK)
	{
		Error_Handler();
	}
}

UARTModule::~UARTModule() {
}

void UARTModule::threadFunction() {
    while(1){
        processRx();
        processTx();
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void UARTModule::processRx(){
	OPENAMP_check_for_message();

	if (VirtUart0RxMsg) {
	  if(uart_init_done==false){
		uart_init_done = true;
		uint8_t tmp_buffer_angles[SCOM_INFO_ANGLES_SIZE];
		SCOM_serialize_info_angle(tmp_buffer_angles, sizeof(tmp_buffer_angles), 0, 0);  //require initial response
		VIRT_UART_Transmit(&huart0, (uint8_t*)tmp_buffer_angles, sizeof(tmp_buffer_angles));
	  }

	  VirtUart0RxMsg = RESET;
	  processData(VirtUart0ChannelBuffRx, sizeof(VirtUart0ChannelBuffRx));
	}
}

void UARTModule::processTx(){
	if(uart_init_done){
		const int16_t target_angle = 0;
       const int16_t current_angle = static_cast<int16_t>(100*m_imu.getXAcceleration_mpss());
		uint8_t tmp_buffer_angles[SCOM_INFO_ANGLES_SIZE];
		SCOM_StatusType status_angles = SCOM_serialize_info_angle(tmp_buffer_angles, sizeof(tmp_buffer_angles), target_angle, current_angle);
		if(SCOM_OK != status_angles){
		  log_info("SCOM_serialize_info_angle failed with code: %d \n", status_angles);
		  Error_Handler();
		}
		VIRT_UART_Transmit(&huart0, (uint8_t*)tmp_buffer_angles, sizeof(tmp_buffer_angles));
	}
}


void UARTModule::processData(uint8_t *rxBuffer, size_t rxBufferSize){
    uint8_t packet_id = rxBuffer[0];
    SCOM_StatusType status = SCOM_OK;
    SCOM_ControlPIDValues control_pid_values;
    SCOM_ControlOnOff control_on_off;
    SCOM_ControlCalibration control_calibration;

    switch (packet_id) {
    case SCOM_ID_PID_VALUES:
        status = SCOM_deserialize_control_pid_values(rxBuffer, rxBufferSize, &control_pid_values);
        if (SCOM_OK != status) {
            log_info("SCOM_deserialize_control_pid_values failed with code: %d\n", status);
        } else {
            log_info("PID Values - P: %f, I: %f, D: %f, K: %f\n", control_pid_values.P_value, control_pid_values.I_value, control_pid_values.D_value, control_pid_values.K_comp_filter);
        }
        // pidModule.setKP(control_pid_values.P_value);
        // pidModule.setKI(control_pid_values.I_value);
        // pidModule.setKD(control_pid_values.D_value);
        // imuModule.setK_compl_filer(control_pid_values.K_comp_filter);
        break;

    case SCOM_ID_ON_OFF:
        status = SCOM_deserialize_control_on_off(rxBuffer, rxBufferSize, &control_on_off);
        if (SCOM_OK != status) {
            log_info("SCOM_deserialize_control_on_off failed with code: %d\n", status);
        } else {
            log_info("On/Off State: %d\n", control_on_off.on_off_state);
        }
        // pidModule.set_control_on_off(control_on_off.on_off_state);
        break;

    case SCOM_ID_CALIBRATION:
        status = SCOM_deserialize_control_calibration(rxBuffer, rxBufferSize, &control_calibration);
        if (SCOM_OK != status) {
            log_info("SCOM_deserialize_control_calibration failed with code: %d\n", status);
        } else {
            log_info("Calibration Command: %d\n", control_calibration.calibration_command);
        }
        // imuModule.set_calibration_cmd(control_calibration.calibration_command);
        break;

    default:
        log_info("Invalid ID in received control data: %d\n", packet_id);
        break;
    }
}

void UARTModule::VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart) {
    /* copy received msg in a variable to sent it back to master processor in main infinite loop*/
    VirtUart0ChannelRxSize = huart->RxXferSize < MAX_BUFFER_SIZE? huart->RxXferSize : MAX_BUFFER_SIZE-1;
    memcpy(VirtUart0ChannelBuffRx, huart->pRxBuffPtr, VirtUart0ChannelRxSize);
    VirtUart0RxMsg = SET;
    log_info("Msg received on VIRTUAL UART0 channel:  %s \n\r", (char *) huart->pRxBuffPtr);
}
