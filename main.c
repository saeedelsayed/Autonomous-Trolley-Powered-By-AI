#include "port.h"
#include "i2c_driver.h"
#include "i2c_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "Qmc5883l.h"

uint8 controlRegister = 0;
Qmc5883l_DataType compassData = {0, 0, 0, 0};

int main()
{
  /* enable clock for STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /*enable clock for PORT B */
  *((uint32*)0x40023830) |= (1 << 1);
  
  /*enable clock for PORT A */
  *((uint32*)0x40023830) |= (1 << 0);
  
  /* pin configuration for pin 6 and pin 7 in PORT B */
  ConfigurationPin pin6PortB = {PORTB_ID, PIN6_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
  ConfigurationPin pin7PortB = {PORTB_ID, PIN7_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
  PORT_configurePin(&pin6PortB);
  PORT_configurePin(&pin7PortB);
  
  
  /* configuration of I2C 1 */
  I2C_config_t I2C_1 = {I2C1, I2C_MODE_I2C};
  I2C_init(&I2C_1);
  
  /* initializing of the compass sensor */
  QMC5883l_SetInOutModule(&I2C_1);
  QMC5883l_Init();
  
  QMC5833l_ReadReg(QMC5883l_CONFIG_REG_1, &controlRegister);
  
  
  while(1){   
    QMC5883l_GetAngel(&compassData);
  }
  
  return 0;
  
}
