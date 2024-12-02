#pragma once
#include "common/interface/inc/drivers.hpp"
#include "platform/stm32mp1/generated/CM4/Core/Inc/i2c.h"

#define MPU6050_DataRate_8KHz 0
#define MPU6050_DataRate_4KHz 1
#define MPU6050_DataRate_2KHz 3
#define MPU6050_DataRate_1KHz 7
#define MPU6050_DataRate_500Hz 15
#define MPU6050_DataRate_250Hz 31
#define MPU6050_DataRate_125Hz 63
#define MPU6050_DataRate_100Hz 79

namespace Driver {

class Mpu6050 : public Common::Interface::Imu {
   public:
    Mpu6050(Common::Interface::Functionality functionality);
    ~Mpu6050() override = default;

    Eigen::Vector3f getAcceleration_mpss() final;
    Eigen::Vector3f getRotationalVelocity_radps() final;
    
    typedef enum {
        MPU6050_Result_Ok = 0x00,
        MPU6050_Result_Error,
        MPU6050_Result_DeviceNotConnected, /*!< There is no device with valid
                                              slave address */
        MPU6050_Result_DeviceInvalid /*!< Connected device with address is not
                                        MPU6050 */
    } MPU6050_Result;

   private:
    static constexpr float DEG_TO_RAD = 0.0174533f;

    /**
     * @brief  MPU6050 can have 2 different slave addresses, depends on it's
     * input AD0 pin This feature allows you to use 2 different sensors with
     * this library at the same time. If you set AD0 pin to low, then this
     * parameter should be MPU6050_Device_0, but if AD0 pin is high, then you
     * should use MPU6050_Device_1
     */
    typedef enum {
        DeviceAddress_0 = 0x00, /*!< AD0 pin is set to low */
        DeviceAddress_1 = 0x02  /*!< AD0 pin is set to high */
    } Mpu6050_DeviceAddress;

    typedef enum {
        Sensitivity_2g = 0x00, /*!< Range is +- 2G */
        Sensitivity_4g = 0x01, /*!< Range is +- 4G */
        Sensitivity_8g = 0x02, /*!< Range is +- 8G */
        Sensitivity_16g = 0x03 /*!< Range is +- 16G */
    } Mpu6050_AccelSensitivity;

    typedef enum {
        Sensitivity_250degps = 0x00,  /*!< Range is +- 250 degrees/s */
        Sensitivity_500degps = 0x01,  /*!< Range is +- 500 degrees/s */
        Sensitivity_1000degps = 0x02, /*!< Range is +- 1000 degrees/s */
        Sensitivity_2000degps = 0x03  /*!< Range is +- 2000 degrees/s */
    } Mpu6050_GyroSensitivity;

    typedef union {
        struct {
            uint8_t DataReady : 1; /*!< Data ready interrupt */
            uint8_t reserved2 : 2; /*!< Reserved bits */
            uint8_t
                Master : 1; /*!< Master interrupt. Not enabled with library */
            uint8_t FifoOverflow : 1; /*!< FIFO overflow interrupt. Not enabled
                                         with library */
            uint8_t reserved1 : 1;    /*!< Reserved bit */
            uint8_t MotionDetection : 1; /*!< Motion detected interrupt */
            uint8_t reserved0 : 1;       /*!< Reserved bit */
        } F;
        uint8_t Status;
    } Mpu6050_Interrupt;

    I2C_HandleTypeDef* m_I2CHandle;
    Mpu6050_DeviceAddress m_DeviceNumber;
    Mpu6050_AccelSensitivity m_AccelerometerSensitivity;
    Mpu6050_GyroSensitivity m_GyroscopeSensitivity;

    uint8_t m_Address;
    float m_GyroScaleFactor;
    float m_AccelScaleFactor;

    int16_t m_Accelerometer_X; /*!< Accelerometer value X axis */
    int16_t m_Accelerometer_Y; /*!< Accelerometer value Y axis */
    int16_t m_Accelerometer_Z; /*!< Accelerometer value Z axis */
    int16_t m_Gyroscope_X;     /*!< Gyroscope value X axis */
    int16_t m_Gyroscope_Y;     /*!< Gyroscope value Y axis */
    int16_t m_Gyroscope_Z;     /*!< Gyroscope value Z axis */
    float m_Temperature;       /*!< Temperature in degrees */

    MPU6050_Result init();
    MPU6050_Result setGyroSensitivity();
    MPU6050_Result setAccelSensitivity();
    MPU6050_Result setDataRate(uint8_t rate);
    MPU6050_Result enableInterrupts();
    MPU6050_Result disableInterrupts();
    MPU6050_Result getInterrupts(Mpu6050_Interrupt* InterruptsStruct);
    MPU6050_Result readAccel();
    MPU6050_Result readGyro();
    MPU6050_Result readTemperature();
    MPU6050_Result readAll();
};

}  // namespace Driver
