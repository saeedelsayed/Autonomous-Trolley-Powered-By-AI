/*******************************************************************************
 *
 * Module: I2C module
 *
 * File Name: i2c_driver.h
 *
 * Description: Header file for the I2C module
 *
 * Author: Saeed Elsayed & Ahmed Radwan
 *
 *******************************************************************************/

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

/* I2C acknowledge */
#define I2C_ACK_ENABLE 0x01
#define I2C_ACK_DISABLE 0x00


/************************************************************************/
/***************************Definitions**********************************/
/************************************************************************/
typedef struct 
{
    uint32 type; /* holds the start address of the I2C */
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
 * @brief This function is responsible for sending the start bit
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_start(const I2C_config_t *i2c);

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
 * @brief This function is responsible for clearing the address flag
 * 
 * @return uint8 
 */
standard_return_t I2C_clearAddressFlag(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for ebabling the acknowledge bit to be sent
 * 
 * @return uint8 
 */
standard_return_t I2C_enableACK(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for disabling the acknowledge bit
 * 
 * @return uint8 
 */
standard_return_t I2C_disableACK(const I2C_config_t *i2c);

/**
 * @brief This function is responsible for writing data on the bus
 * 
 * @return uint8 
 */
standard_return_t I2C_writeData(const I2C_config_t *i2c, uint8 data);

/**
 * @brief This function is responsible for reading data from the bus
 * 
 * @return uint8 
 */
standard_return_t I2C_read(const I2C_config_t *i2c, uint8* data);

/**
 * @brief This function is responsible for sending only one byte
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_transmitByte(const I2C_config_t *i2c, uint8 address, uint8 data);

/**
 * @brief This function is responsible for sending a string
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_transmitString(const I2C_config_t *i2c, uint8 address, uint8* str);

/**
 * @brief This function is responsible for receiving a string
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_receiveString(const I2C_config_t *i2c, uint8 n, uint8* str);

#endif /* I2C_DRIVER_H_ */