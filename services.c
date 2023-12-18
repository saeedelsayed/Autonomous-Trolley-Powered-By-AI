/******************************************************************************
*
* Module: Services for the main application
*
* File Name: services.c
*
* Description: source file for the services of main application
*
* Author: All team
*
*******************************************************************************/

#include "services.h"

/* pin definition for USART1 */
ConfigurationPin usart1TX = {PORTA_ID, PIN9_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
ConfigurationPin usart1RX = {PORTA_ID, PIN10_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};

/* pin definition for USART2 */
ConfigurationPin usart2TX = {PORTA_ID, PIN2_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
ConfigurationPin usart2RX = {PORTA_ID, PIN3_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};

/* pin definition for I2C1 */
ConfigurationPin i2c1SDA = {PORTB_ID, PIN7_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
ConfigurationPin i2c1SCL = {PORTB_ID, PIN6_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};

/* definition of USART1 I/O module */
USART_STRUCT usart1 = {USART1, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 9600};

/* definition of USART2 I/O module */
USART_STRUCT usart2 = {USART2, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 38400};

/* definition of I2C1 I/O module */
I2C_config_t i2c1 = {I2C1, I2C_MODE_I2C};


/*
 * description : the function is responsible for initializing the system.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
*/
void SERVICES_systemInit(void){
  
  /* configure of pins of USART1 */
  PORT_configurePin(&usart1TX);
  PORT_configurePin(&usart1RX);
  
  /* configure of pins of USART2 */
  PORT_configurePin(&usart2TX);
  PORT_configurePin(&usart2RX);
  
  /* configure of pins of I2C1 */
  PORT_configurePin(&i2c1SDA);
  PORT_configurePin(&i2c1SCL);
  
  /* initialize USART1 */
  UART_init(&usart1);
  
  /* initialize USART2 */
  UART_init(&usart2);
  
  /* initialize I2C1 */
  I2C_init(&i2c1);
  
  /* set the I/O module for the GPS */
  GPS_setInputOutputModule(&usart1);
  
  /* initialize the GPS module */
  GPS_init();
  
  /* set the I/O module for the Bluetooth */
  Bluetooth_setInputOutputModule(&usart2);
  
  /* set the I/O module for the compass sensor */
  QMC5883l_SetInOutModule(&i2c1);
  
  /* initialize the compass sensor */
  QMC5883l_Init();
}
