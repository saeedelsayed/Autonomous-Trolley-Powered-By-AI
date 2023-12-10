#include "port.h"
#include "uart_driver.h"
#include "uart_registers.h"
#include "i2c_driver.h"
#include "i2c_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "bluetooth.h"

char bluetooth_message[20];

int main()
{
  /* enable clock for portA */
  *((uint32*)0x40023800) |= (1 << 0);
  *((uint32*)0x40023830) |= (1 << 1);
  *((uint32*)0x40023830) |= (1 << 0);
  
  uint8* data1;
  
  ConfigurationPin pin6PortB = {PORTB_ID, PIN6_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
  ConfigurationPin pin7PortB = {PORTB_ID, PIN7_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
 
  PORT_configurePin(&pin6PortB);
  PORT_configurePin(&pin7PortB);
  
  
  I2C_config_t I2C_1 = {I2C1, I2C_MODE_I2C};
  
  I2C_init(&I2C_1);
  
  char Str[2] = {(uint8)(0x5684), 0x11};
  I2C_Master_transmitString(&I2C_1, (uint8)(0xA0 | ((0x5684 & 0x0700)>>7)), Str);

  I2C_Master_start(&I2C_1);
  
 
  I2C_writeAddress(&I2C_1, (uint8)((0xA0) | ((0x5684 & 0x0700)>>7)));
  
  I2C_writeData(&I2C_1, (uint8)(0x5684));
  I2C_Master_start(&I2C_1);
  I2C_writeAddress(&I2C_1, (uint8)((0xA0) | ((0x5684 & 0x0700)>>7) | 1));
  I2C_read(&I2C_1, data1);
   
  //I2C_Master_stop(&I2C_1);
  
  
  if(*data1 == 0x11)
  {
 ConfigurationPin pin5PortA = {PORTA_ID, PIN5_ID, OUTPUT_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, NO_ALTERNATE};
  PORT_configurePin(&pin5PortA);
  } 
  while(1){
    
  }
  
  return 0;
  
}
