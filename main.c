#include "port.h"
#include "uart_driver.h"
#include "uart_registers.h"
#include "i2c_driver.h"
#include "i2c_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "bluetooth.h"

uint8 ControlRegister = 0;
uint8 statusRegister = 0;
uint8 xLow = 0;
uint8 xHigh = 0;
uint8 yLow = 0;
uint8 yHigh = 0;
uint8 zLow = 0;
uint8 zHigh = 0;

int main()
{
  /* enable clock for STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /*enable clock for PORT B */
  *((uint32*)0x40023830) |= (1 << 1);
  
  /*enable clock for PORT A */
  *((uint32*)0x40023830) |= (1 << 0);
  
  ConfigurationPin pin6PortB = {PORTB_ID, PIN6_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
  ConfigurationPin pin7PortB = {PORTB_ID, PIN7_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
  
  PORT_configurePin(&pin6PortB);
  PORT_configurePin(&pin7PortB);
  
  
  I2C_config_t I2C_1 = {I2C1, I2C_MODE_I2C};
  
  I2C_init(&I2C_1);
  
  /**************** Define set/reset period ***********/
  
  /* start condition */
  I2C_Master_start(&I2C_1);
  
  /* Compass address with write operation */
  I2C_writeAddress(&I2C_1, 0x0D << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(&I2C_1);
  
  /* register address */
  I2C_writeData(&I2C_1, 0x0B);
  
  /* data written to the register */
  I2C_writeData(&I2C_1, 0x01);
  
  /* stop condition */
  I2C_Master_stop(&I2C_1);
  
  /****************** init compass using control register ****************/
  
  /* start condition */
  I2C_Master_start(&I2C_1);
  
  /* Compass address with write operation */
  I2C_writeAddress(&I2C_1, 0x0D << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(&I2C_1);
  
  /* register address */
  I2C_writeData(&I2C_1, 0x09);
  
  /* data written to the register */
  I2C_writeData(&I2C_1, 0x1D);
  
  /* stop condition */
  I2C_Master_stop(&I2C_1);
  
  /***************** read data from control register *******************/
  
  /* start condition */
  I2C_Master_start(&I2C_1);
  
  /* Compass address with write operation */
  I2C_writeAddress(&I2C_1, 0x0D << 1);
  
  /* clear address flag */
  I2C_clearAddressFlag(&I2C_1);
  
  /* location to be read from */
  I2C_writeData(&I2C_1, 0x09);
  
  /* repeated start condition */
  I2C_Master_start(&I2C_1);
  
  /* Compass address with read operation */
  I2C_writeAddress(&I2C_1, (0x0D << 1) | 0x01);
  
  /* disable ack bit */
  I2C_disableACK(&I2C_1);
  
  /* clear address flag */
  I2C_clearAddressFlag(&I2C_1);
  
  /* stop condition */
  I2C_Master_stop(&I2C_1);
  
  /* read data from the register */
  I2C_read(&I2C_1, &ControlRegister);
  
  while(1){
    
    /***************** read status register ***************/
    
    /* start condition */
    I2C_Master_start(&I2C_1);
    
    /* Compass address with write operation */
    I2C_writeAddress(&I2C_1, 0x0D << 1);
    
    /* clear address flag */
    I2C_clearAddressFlag(&I2C_1);
    
    /* location to be read from */
    I2C_writeData(&I2C_1, 0x06);
    
    /* repeated start condition */
    I2C_Master_start(&I2C_1);
    
    /* Compass address with read operation */
    I2C_writeAddress(&I2C_1, (0x0D << 1) | 0x01);
    
    /* disable ack bit */
    I2C_disableACK(&I2C_1);
    
    /* clear address flag */
    I2C_clearAddressFlag(&I2C_1);
    
    /* stop condition */
    I2C_Master_stop(&I2C_1);
    
    /* read data from the register */
    I2C_read(&I2C_1, &statusRegister);
    
    /******************* read data registers *************/
    
    if(statusRegister & (1 << 0)){
      
      /* enable ack bit */
      I2C_enableACK(&I2C_1);
      
      /* start condition */
      I2C_Master_start(&I2C_1);
      
      /* Compass address with write operation */
      I2C_writeAddress(&I2C_1, 0x0D << 1);
      
      /* clear address flag */
      I2C_clearAddressFlag(&I2C_1);
      
      /* location to be read from */
      I2C_writeData(&I2C_1, 0x00);
      
      /* repeated start condition */
      I2C_Master_start(&I2C_1);
      
      /* Compass address with read operation */
      I2C_writeAddress(&I2C_1, (0x0D << 1) | 0x01);
      
      /* clear address flag */
      I2C_clearAddressFlag(&I2C_1);
      
      /* read data from the data registers */
      I2C_read(&I2C_1, &xLow);
      I2C_read(&I2C_1, &xHigh);
      I2C_read(&I2C_1, &yLow);
      I2C_read(&I2C_1, &yHigh);
      I2C_read(&I2C_1, &zLow);
      
      /* disable ack bit */
      I2C_disableACK(&I2C_1);
      
      /* stop condition */
      I2C_Master_stop(&I2C_1);
      
      /* read last data register */
      I2C_read(&I2C_1, &zHigh); 
    }
    
  }
  
  return 0;
  
}
