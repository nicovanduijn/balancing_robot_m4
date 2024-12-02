#include "platform/stm32mp1/driver/inc/mpu6050_driver.hpp"

#include "platform/stm32mp1/driver/inc/bsp.hpp"

/* Default I2C address */
#define MPU6050_I2C_ADDR 0xD0

/* Who I am register value */
#define MPU6050_I_AM 0x68

/* MPU6050 registers */
#define MPU6050_AUX_VDDIO 0x01
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1A
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_MOTION_THRESH 0x1F
#define MPU6050_INT_PIN_CFG 0x37
#define MPU6050_INT_ENABLE 0x38
#define MPU6050_INT_STATUS 0x3A
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x47
#define MPU6050_GYRO_ZOUT_L 0x48
#define MPU6050_MOT_DETECT_STATUS 0x61
#define MPU6050_SIGNAL_PATH_RESET 0x68
#define MPU6050_MOT_DETECT_CTRL 0x69
#define MPU6050_USER_CTRL 0x6A
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_PWR_MGMT_2 0x6C
#define MPU6050_FIFO_COUNTH 0x72
#define MPU6050_FIFO_COUNTL 0x73
#define MPU6050_FIFO_R_W 0x74
#define MPU6050_WHO_AM_I 0x75

/* Gyro sensitivities in degrees/s */
#define MPU6050_GYRO_SENS_250 ((float)131)
#define MPU6050_GYRO_SENS_500 ((float)65.5)
#define MPU6050_GYRO_SENS_1000 ((float)32.8)
#define MPU6050_GYRO_SENS_2000 ((float)16.4)

/* Acce sensitivities in g/s */
#define MPU6050_ACCE_SENS_2 ((float)16384)
#define MPU6050_ACCE_SENS_4 ((float)8192)
#define MPU6050_ACCE_SENS_8 ((float)4096)
#define MPU6050_ACCE_SENS_16 ((float)2048)

namespace Driver {

Mpu6050::Mpu6050(Common::Interface::Functionality functionality)
    : m_I2CHandle{Bsp::getI2CHandle(functionality)},
      m_DeviceNumber{Mpu6050_DeviceAddress::DeviceAddress_0},
      m_AccelerometerSensitivity{Mpu6050_AccelSensitivity::Sensitivity_16g},
      m_GyroscopeSensitivity{Mpu6050_GyroSensitivity::Sensitivity_2000degps} {
    init();
}

Eigen::Vector3f Mpu6050::getAcceleration_mpss() {
    readAccel();
    Eigen::Vector3f acceleration{m_AccelScaleFactor * m_Accelerometer_X,
                                 m_AccelScaleFactor * m_Accelerometer_Y,
                                 m_AccelScaleFactor * m_Accelerometer_Z};
    return acceleration;
}

Eigen::Vector3f Mpu6050::getRotationalVelocity_radps() {
    readGyro();
    Eigen::Vector3f rotational_velocity_radps{
        m_GyroScaleFactor * m_Gyroscope_X * DEG_TO_RAD,
        m_GyroScaleFactor * m_Gyroscope_Y * DEG_TO_RAD,
        m_GyroScaleFactor * m_Gyroscope_Z * DEG_TO_RAD};

    return rotational_velocity_radps;
}

Mpu6050::MPU6050_Result Mpu6050::init() {
    uint8_t WHO_AM_I = (uint8_t)MPU6050_WHO_AM_I;
    uint8_t temp;
    uint8_t d[2];

    /* Format I2C address */
    m_Address = MPU6050_I2C_ADDR | (uint8_t)m_DeviceNumber;

    /* Check if device is connected */
    if (HAL_I2C_IsDeviceReady(m_I2CHandle, m_Address, 2, 5) != HAL_OK) {
        return MPU6050_Result_Error;
    }
    /* Check who am I */
    //------------------
    /* Send address */
    if (HAL_I2C_Master_Transmit(m_I2CHandle, m_Address, &WHO_AM_I, 1, 1000) !=
        HAL_OK) {
        return MPU6050_Result_Error;
    }

    /* Receive multiple byte */
    if (HAL_I2C_Master_Receive(m_I2CHandle, m_Address, &temp, 1, 1000) !=
        HAL_OK) {
        return MPU6050_Result_Error;
    }

    /* Checking */
    while (temp != MPU6050_I_AM) {
        /* Return error */
        return MPU6050_Result_DeviceInvalid;
    }
    //------------------

    /* Wakeup MPU6050 */
    //------------------
    /* Format array to send */
    d[0] = MPU6050_PWR_MGMT_1;
    d[1] = 0x00;

    /* Try to transmit via I2C */
    if (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, (uint8_t*)d,
                                2, 1000) != HAL_OK) {
        return MPU6050_Result_Error;
    }
    //------------------

    setDataRate(MPU6050_DataRate_500Hz);

    /* Config accelerometer */
    setAccelSensitivity();

    /* Config Gyroscope */
    setGyroSensitivity();

    /* Return OK */
    return MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::setDataRate(uint8_t rate) {
    uint8_t d[2];

    /* Format array to send */
    d[0] = MPU6050_SMPLRT_DIV;
    d[1] = rate;

    /* Set data sample rate */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address,
                                   (uint8_t*)d, 2, 1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/

    /* Return OK */
    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::setAccelSensitivity() {
    uint8_t temp;
    uint8_t regAdd = (uint8_t)MPU6050_ACCEL_CONFIG;

    /* Config accelerometer */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &regAdd, 1,
                                   1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/
    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, &temp, 1,
                                  1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/
    temp = (temp & 0xE7) | (uint8_t)m_AccelerometerSensitivity << 3;
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &temp, 1,
                                   1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/

    /* Set sensitivities for multiplying gyro and accelerometer data */
    switch (m_AccelerometerSensitivity) {
        case Mpu6050::Sensitivity_2g:
            m_AccelScaleFactor = (float)1 / MPU6050_ACCE_SENS_2;
            break;
        case Mpu6050::Sensitivity_4g:
            m_AccelScaleFactor = (float)1 / MPU6050_ACCE_SENS_4;
            break;
        case Mpu6050::Sensitivity_8g:
            m_AccelScaleFactor = (float)1 / MPU6050_ACCE_SENS_8;
            break;
        case Mpu6050::Sensitivity_16g:
            m_AccelScaleFactor = (float)1 / MPU6050_ACCE_SENS_16;
            break;
        default:
            break;
    }

    /* Return OK */
    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::setGyroSensitivity() {
    uint8_t temp;
    uint8_t regAdd = (uint8_t)MPU6050_GYRO_CONFIG;

    /* Config gyroscope */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &regAdd, 1,
                                   1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/
    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, &temp, 1,
                                  1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/
    temp = (temp & 0xE7) | (uint8_t)m_GyroscopeSensitivity << 3;
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &temp, 1,
                                   1000) != HAL_OK)
        ;
    /*{
                            return MPU6050_Result_Error;
    }*/

    switch (m_GyroscopeSensitivity) {
        case Mpu6050::Sensitivity_250degps:
            m_GyroScaleFactor = (float)1 / MPU6050_GYRO_SENS_250;
            break;
        case Mpu6050::Sensitivity_500degps:
            m_GyroScaleFactor = (float)1 / MPU6050_GYRO_SENS_500;
            break;
        case Mpu6050::Sensitivity_1000degps:
            m_GyroScaleFactor = (float)1 / MPU6050_GYRO_SENS_1000;
            break;
        case Mpu6050::Sensitivity_2000degps:
            m_GyroScaleFactor = (float)1 / MPU6050_GYRO_SENS_2000;
            break;
        default:
            break;
    }
    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::readAccel() {
    uint8_t data[6];
    uint8_t reg = MPU6050_ACCEL_XOUT_H;

    /* Read accelerometer data */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &reg, 1,
                                   1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, data, 6,
                                  1000) != HAL_OK)
        ;

    m_Accelerometer_X = (int16_t)(data[0] << 8 | data[1]);
    m_Accelerometer_Y = (int16_t)(data[2] << 8 | data[3]);
    m_Accelerometer_Z = (int16_t)(data[4] << 8 | data[5]);

    return Mpu6050::MPU6050_Result_Ok;
}
Mpu6050::MPU6050_Result Mpu6050::readGyro() {
    uint8_t data[6];
    uint8_t reg = MPU6050_GYRO_XOUT_H;

    /* Read gyroscope data */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &reg, 1,
                                   1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, data, 6,
                                  1000) != HAL_OK)
        ;

    m_Gyroscope_X = (int16_t)(data[0] << 8 | data[1]);
    m_Gyroscope_Y = (int16_t)(data[2] << 8 | data[3]);
    m_Gyroscope_Z = (int16_t)(data[4] << 8 | data[5]);

    return Mpu6050::MPU6050_Result_Ok;
}
Mpu6050::MPU6050_Result Mpu6050::readTemperature() {
    uint8_t data[2];
    int16_t temp;
    uint8_t reg = MPU6050_TEMP_OUT_H;

    /* Read temperature */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &reg, 1,
                                   1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, data, 2,
                                  1000) != HAL_OK)
        ;

    temp = (data[0] << 8 | data[1]);
    m_Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);

    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::enableInterrupts() {
    uint8_t temp;
    uint8_t reg[2] = {MPU6050_INT_ENABLE, 0x21};

    /* Enable interrupts for data ready and motion detect */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, reg, 2,
                                   1000) != HAL_OK)
        ;

    uint8_t mpu_reg = MPU6050_INT_PIN_CFG;
    /* Clear IRQ flag on any read operation */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &mpu_reg,
                                   1, 1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, &temp, 14,
                                  1000) != HAL_OK)
        ;
    temp |= 0x10;
    reg[0] = MPU6050_INT_PIN_CFG;
    reg[1] = temp;
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, reg, 2,
                                   1000) != HAL_OK)
        ;

    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::readAll() {
    uint8_t data[14];
    int16_t temp;
    uint8_t reg = MPU6050_ACCEL_XOUT_H;

    /* Read full raw data, 14bytes */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &reg, 1,
                                   1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, data, 14,
                                  1000) != HAL_OK)
        ;

    /* Format accelerometer data */
    m_Accelerometer_X = (int16_t)(data[0] << 8 | data[1]);
    m_Accelerometer_Y = (int16_t)(data[2] << 8 | data[3]);
    m_Accelerometer_Z = (int16_t)(data[4] << 8 | data[5]);

    /* Format temperature */
    temp = (data[6] << 8 | data[7]);
    m_Temperature =
        (float)((float)((int16_t)temp) / (float)340.0 + (float)36.53);

    /* Format gyroscope data */
    m_Gyroscope_X = (int16_t)(data[8] << 8 | data[9]);
    m_Gyroscope_Y = (int16_t)(data[10] << 8 | data[11]);
    m_Gyroscope_Z = (int16_t)(data[12] << 8 | data[13]);

    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::disableInterrupts() {
    uint8_t reg[2] = {MPU6050_INT_ENABLE, 0x00};

    /* Disable interrupts */
    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, reg, 2,
                                   1000) != HAL_OK)
        ;

    return Mpu6050::MPU6050_Result_Ok;
}

Mpu6050::MPU6050_Result Mpu6050::getInterrupts(
    Mpu6050_Interrupt* InterruptsStruct) {
    uint8_t read;

    /* Reset structure */
    InterruptsStruct->Status = 0;
    uint8_t reg = MPU6050_INT_STATUS;

    while (HAL_I2C_Master_Transmit(m_I2CHandle, (uint16_t)m_Address, &reg, 1,
                                   1000) != HAL_OK)
        ;

    while (HAL_I2C_Master_Receive(m_I2CHandle, (uint16_t)m_Address, &read, 14,
                                  1000) != HAL_OK)
        ;

    /* Fill value */
    InterruptsStruct->Status = read;

    return Mpu6050::MPU6050_Result_Ok;
}

}  // namespace Driver