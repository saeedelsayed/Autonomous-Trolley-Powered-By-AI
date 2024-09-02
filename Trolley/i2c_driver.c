/*******************************************************************************
 *
 * Module: I2C module
 *
 * File Name: i2c_driver.c
 *
 * Description: Source file for the I2C module
 *
 * Author: Saeed Elsayed & Ahmed Radwan
 *
 *******************************************************************************/

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "i2c_driver.h"
#include "i2c_registers.h"
#include "common_macros.h"


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
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else {
    /* enable the clock for the I2C (warning...it is static)*/
    RCC_APB1ENR |= (1 << 21);  /* I2C1 */
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
* @brief This function is responsible for sending the start bit
* 
* @return uint8 
*/
standard_return_t I2C_Master_start(const I2C_config_t *i2c)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* set the start bit in the control register 1 to tell the I2C to send the start bit */
    (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (1 << I2C_CR1_START);
    /* wait until the start bit in the status register is set to make 
       sure that the I2C sent the start bit successfully */
    while(BIT_IS_CLEAR((*(uint32 *)(i2c->type + I2Cx_SR1_OFFSET)),I2C_SR1_SB));
  }
  
  return ret_val;
}

/**
* @brief This function is responsible for sending the stop bit
* 
* @return uint8 
*/
standard_return_t I2C_Master_stop(const I2C_config_t *i2c)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* Set the stop bit in the control register 1 to tell the I2C to send the stop bit */
    (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (1 << I2C_CR1_STOP);
  }
  
  return ret_val;
}

/**
* @brief This function is responsible for writing address on the bus
* 
* @return uint8 
*/
standard_return_t I2C_writeAddress(const I2C_config_t *i2c, uint8 address)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* write the address in the data register*/
    (*(uint32 *)(i2c->type + I2Cx_DR_OFFSET)) = address;
    
    /* wait until the address bit that insures the address was sent successfully is set */
    while(BIT_IS_CLEAR((*(uint32 *)(i2c->type + I2Cx_SR1_OFFSET)),I2C_SR1_ADDR))
    {
      //if(BIT_IS_SET((*(uint32 *)(i2c->type + I2Cx_SR1_OFFSET)),I2C_SR1_AF))
      //{
        //ret_val = E_NOT_OK;
        //break;
      //}
    };
  }
  
  return ret_val;
}

standard_return_t I2C_clearAddressFlag(const I2C_config_t *i2c)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
  /* read the status registers 1 & 2 to clear the address flag */
  volatile uint32 dummyVariable = (*(uint32 *)(i2c->type + I2Cx_SR1_OFFSET));
  dummyVariable = (*(uint32 *)(i2c->type + I2Cx_SR2_OFFSET));
  }
  
  return ret_val;
} 

/**
 * @brief This function is responsible for ebabling the acknowledge bit to be sent
 * 
 * @return uint8 
 */
standard_return_t I2C_enableACK(const I2C_config_t *i2c)
{
  /* set the ACK bit in the control register 1 */
  (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) |= (1 << I2C_CR1_ACK);
}

/**
 * @brief This function is responsible for disabling the acknowledge bit
 * 
 * @return uint8 
 */
standard_return_t I2C_disableACK(const I2C_config_t *i2c)
{ 
  /* clear the ACK bit in the control register 1 */
  (*(uint32 *)(i2c->type + I2Cx_CR1_OFFSET)) &= ~(1 << I2C_CR1_ACK);
}

/**
* @brief This function is responsible for writing data on the bus
*
* @return uint8
*/
standard_return_t I2C_writeData(const I2C_config_t *i2c, uint8 data)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* write the required data to be sent in the data register */
    (*(uint32 *)(i2c->type + I2Cx_DR_OFFSET)) = data;
    /* wait until the transfer of the data is finished */
    while(BIT_IS_CLEAR((*(uint32 *)( i2c->type  + I2Cx_SR1_OFFSET)), I2C_SR1_BTF));
  }
  
  return ret_val;
}

/**
* @brief This function is responsible for reading data from the bus
*
* @return uint8
*/
standard_return_t I2C_read(const I2C_config_t *i2c, uint8* data)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* wait until the data register has data */
    while(BIT_IS_CLEAR((*(uint32 *)(i2c->type + I2Cx_SR1_OFFSET)),I2C_SR1_RXNE));
    /* receive the data from the data register */
    *data = (*(uint32 *)(i2c->type + I2Cx_DR_OFFSET));
  }
  
  return ret_val;
}

/*
 * @brief This function is responsible for sending only one byte
 * 
 * @return uint8 
 */
standard_return_t I2C_Master_transmitByte(const I2C_config_t *i2c, uint8 address, uint8 data)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
    /* send the start bit */
    I2C_Master_start(i2c);
    /* write the address */
    I2C_writeAddress(i2c, address);
    /* clear the address flag */
    I2C_clearAddressFlag(i2c);
    /* write the data in the data register */
    I2C_writeData(i2c, data);
    /* send the stop bit */
    I2C_Master_stop(i2c);
  }
  
  return ret_val;
}

standard_return_t I2C_Master_transmitString(const I2C_config_t *i2c, uint8 address, uint8 * str)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
  /* counter to access the array of the sent string */ 
  uint8 i = 0;
  /* send the start bit */
  I2C_Master_start(i2c);
  /* write the address */
  ret_val = I2C_writeAddress(i2c, address);
  if(ret_val == E_NOT_OK)
  {
      return FAIL;
  }
  
  /* clear the address flag */
  I2C_clearAddressFlag(i2c);
  
  while(str[i] != '\0')
  {   
    /* send the content of the array */
    I2C_writeData(i2c, str[i]);
    i++;   
  }
  /* send the stop bit */
  I2C_Master_stop(i2c);
  
  }
  
  return ret_val;
}

standard_return_t I2C_Master_receiveString(const I2C_config_t *i2c, uint8 n, uint8* str)
{
  /* variable to check if the pointer of the I2C is pointing to nothing */
  standard_return_t ret_val = E_OK;
  if(NULL_PTR == i2c){
    /* return not ok if the pointer is pointing to null */
    ret_val = E_NOT_OK;
  }
  else
  {
  /* counter to access the array of the received string */
  uint8 i = 0;
  /* enable the acknowledge bit to be sent after receiving data */
  I2C_enableACK(i2c);
  /* if we will send only one byte, we need to disable the acknowlegde bit 
     and send the stop bit  */
  if(n == 1)
  {
    /* disable the Acknowledge bit */
    I2C_disableACK(i2c);
    /* clear the address flag */
    I2C_clearAddressFlag(i2c);
    /* send the stop bit */
    I2C_Master_stop(i2c);
    /* receive the data from the data register */
    I2C_read(i2c, &str[i]);
  }
  else
  {
    /* clear the address flag */
    I2C_clearAddressFlag(i2c);
    
    while(n > 0)
    {
      /* receive the data from the data register */
      I2C_read(i2c, &str[i]);
      /* if only one byte stay, we need the disable the acknowledge 
         and send the stop bit */
      if(n == 2)
      {
        /* disable the Acknowledge bit */
        I2C_disableACK(i2c);
        /* send the stop bit */
        I2C_Master_stop(i2c);
      }
      i++;
      n--;
    }
  }
  }
}