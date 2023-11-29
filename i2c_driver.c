/**
 * @file i2c_driver.c
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief This file is the implementation for the i2c driver
 * @date 2023-11-15
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "i2c_driver.h"
#include "i2c_registers.h"
//#include "port.h"


#define RCC_APB1ENR   (*(unsigned long*) (0x40023800+0x40))

/*******************************************************************************************/
/*********************************** Function Definitions **********************************/
/*******************************************************************************************/
/**
 * @brief This function is responsible for initializing the I2C module
 * 
 * @return uint8 
 */
standard_return_t I2C_init(const I2C_config_t *i2c){
    standard_return_t ret_val = E_OK;
    if(NULL_PTR == i2c){
        ret_val = E_NOT_OK;
    }
    else {
        /* enable the clock for the I2C (warning...it is static)*/
         RCC_APB1ENR |= (1 << 21);  /* I2C1 */
        // RCC_APB1ENR |= (1 << 22);  /* I2C2 */
        // RCC_APB1ENR |= (1 << 23);  /* I2C3 */
        
        /* clear all bits of the CR1 register */
        (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) = CLEAR_ALL_BITS;
        /* disable I2C */
        (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (I2C_DISABLE << I2C_CR1_PE);
        /* choose the mode of the I2C */
        (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (i2c->mode << I2C_MODE_SMBUS);

        /* clear all bits of the CR2 register */
        (*(uint32 *)(i2c->type + I2Cx_CR2_OFFSET)) = CLEAR_ALL_BITS;
        /* choose the clock of the I2C (warning...it is static)*/
        (*(uint32 *)(i2c->type + I2Cx_CR2_OFFSET)) |= (I2C_CLOCK_16MHZ << I2C_CR2_FREQ);

        /* clear all bits of the CCR register */
        (*(uint32 *)(i2c->type + I2Cx_CCR_OFFSET)) = CLEAR_ALL_BITS;
        /* choose the speed of the I2C */
        (*(uint32 *)(i2c->type + I2Cx_CCR_OFFSET)) |= (I2C_SPEED_STANDARD << I2C_CCR_FS);
        /* Controls the SCL clock in master mode(100 KHZ) (warning...it is static)*/ 
        (*(uint32 *)(i2c->type + I2Cx_CCR_OFFSET)) |= (80 << I2C_CCR_CCR);
        
        /* clear all bits of the TRISE register */
        (*(uint32 *)(i2c->type + I2Cx_TRISE_OFFSET)) = CLEAR_ALL_BITS;
        /* control the TRISE register (warning...it is static) */
        (*(uint32 *)(i2c->type + I2Cx_TRISE_OFFSET)) |= (17 << I2C_TRISE_TRISE);
        
        /* enable I2C */
        (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (I2C_ENABLE << I2C_CR1_PE);
        
    }

    return ret_val;

}

/**
 * @brief This function is responsible for de-initializing the I2C module
 * 
 * @return uint8 
 */
standard_return_t I2C_Deinit(const I2C_config_t *i2c)
{
    standard_return_t ret_val = E_OK;
    if (NULL_PTR == i2c)
    {
        ret_val = E_NOT_OK;
    }
    else
    {

        
    }

    return ret_val;
}
/**
 * @brief This function is responsible for sending the start bit
 * 
 * @return uint8 
 */
standard_return_t I2C_start(const I2C_config_t *i2c)
{
    standard_return_t ret_val = E_OK;
    if (NULL_PTR == i2c)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
    }

    return ret_val;
}

/**
 * @brief This function is responsible for sending the stop bit
 * 
 * @return uint8 
 */
standard_return_t I2C_stop(const I2C_config_t *i2c)
{
    standard_return_t ret_val = E_OK;
    if (NULL_PTR == i2c)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
    }

    return ret_val;
}

/**
 * @brief This function is responsible for writing data on the bus
 *
 * @return uint8
 */
standard_return_t I2C_write(const I2C_config_t *i2c, uint8 data)
{
    standard_return_t ret_val = E_OK;
    if (NULL_PTR == i2c)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
    }

    return ret_val;
}

/**
 * @brief This function is responsible for reading data from the bus
 *
 * @return uint8
 */
standard_return_t I2C_read(const I2C_config_t *i2c, uint8 ack, uint8 *data)
{
    standard_return_t ret_val = E_OK;
    if (NULL_PTR == i2c || NULL_PTR == data)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
    }

    return ret_val;
}
