/**
 * @file i2c_driver.h
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief This is the header file for the I2C driver
 * @date 2023-11-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

/************************************************************************/
/***************************Includes*************************************/
/************************************************************************/
#include "std_types.h"

/************************************************************************/
/***************************Macros***************************************/
/************************************************************************/

/* I2C configuration */
#define I2C_ENABLE 0x01
#define I2C_DISABLE 0x00

/* I2C mode */
#define I2C_MODE_I2C 0x00
#define I2C_MODE_SMBUS 0x01

/* I2C clock */
#define I2C_CLOCK_16MHZ 0x10
#define I2C_CLOCK_8MHZ 0x08

/* I2C speed */
#define I2C_SPEED_STANDARD 0x00
#define I2C_SPEED_FAST 0x01

/* I2C duty cycle */
#define I2C_DUTY_2 0x00
#define I2C_DUTY_16_9 0x01

/* I2C address mode */
#define I2C_ADDRESS_7_BITS 0x00
#define I2C_ADDRESS_10_BITS 0x01

/* I2C acknowledge */
#define I2C_ACK_ENABLE 0x01
#define I2C_ACK_DISABLE 0x00

/* I2C acknowledge position */
#define I2C_ACK_POS_NEXT 0x00
#define I2C_ACK_POS_CURRENT 0x01

/* I2C software reset */
#define I2C_RESET 0x01
#define I2C_NO_RESET 0x00

/* I2C error */
#define I2C_ERROR 0x01
#define I2C_NO_ERROR 0x00

/* I2C state */
#define I2C_STATE_BUSY 0x01
#define I2C_STATE_READY 0x00

/* I2C rise time */
#define I2C_RISE_TIME_1000 0x00
#define I2C_RISE_TIME_400 0x01

/* I2C filter */
typedef enum
{
    I2C_FILTER_DISABLED = 0x00,
    I2C_FILTER_1 ,
    I2C_FILTER_2 ,
    I2C_FILTER_3 ,
    I2C_FILTER_4 ,
    I2C_FILTER_5 ,
    I2C_FILTER_6 ,
    I2C_FILTER_7 ,
    I2C_FILTER_8 ,
    I2C_FILTER_9 ,
    I2C_FILTER_10 ,
    I2C_FILTER_11 ,
    I2C_FILTER_12 ,
    I2C_FILTER_13 ,
    I2C_FILTER_14 ,
    I2C_FILTER_15 
}I2C_filter;

/* I2C return status */
typedef enum
{
    I2C_STATUS_OK = 0x00,
    I2C_STATUS_ERROR,
    I2C_STATUS_BUSY,
    I2C_STATUS_TIMEOUT
}I2C_status;

/* I2C return status */
typedef enum I2C_direction
{
    I2C_DIRECTION_TRANSMITTER = 0x00,
    I2C_DIRECTION_RECEIVER
}I2C_direction;





/************************************************************************/
/***************************Definitions**********************************/
/************************************************************************/
typedef struct 
{
    uint32 type; /* holds the start address of the I2C */
    // uint8 state; /* holds the initial state of the I2C */
     uint8 mode; /* holds the mode of the I2C */
     
}I2C_config_t;

/************************************************************************/
/***************************Function Declarations*************************/
/************************************************************************/

/**
 * @brief This function is responsible for initializing the I2C module
 *
 * @return uint8
 */
standard_return_t I2C_init(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for de-initializing the I2C module
 * 
 * @return uint8 
 */
standard_return_t I2C_Deinit(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for sending the start bit
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_start(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for sending the repeated start bit 
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_restart(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for sending the stop bit
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_stop(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for writing address on the bus
 * 
 * @return uint8 
 */
standard_return_t I2C_writeAddress(const I2C_config_t *i2c, uint8 address);

/**
 * @brief This function is responsible for writing data on the bus
 * 
 * @return uint8 
 */
standard_return_t I2C_writeData(const I2C_config_t *i2c, uint8 data);

standard_return_t I2C_enableACK(const I2C_config_t *i2c);

standard_return_t I2C_disableACK(const I2C_config_t *i2c);

standard_return_t I2C_clearAddressFlag(const I2C_config_t *i2c);


/**
 * @brief This function is responsible for reading data from the bus
 * 
 * @return uint8 
 */
standard_return_t I2C_read(const I2C_config_t *i2c, uint8* data);


standard_return_t I2C_Master_transmitByte(const I2C_config_t *i2c, uint8 address, uint8 data);

standard_return_t I2C_Master_transmitString(const I2C_config_t *i2c, uint8 address, uint8* str);

standard_return_t I2C_Master_receiveString(const I2C_config_t *i2c, uint8 n, uint8* str);

#endif /* I2C_DRIVER_H_ */