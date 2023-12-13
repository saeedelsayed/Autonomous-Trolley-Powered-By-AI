#include "port.h"
#include "uart_driver.h"
#include "uart_registers.h"
#include "gps.h"

int main()
{
  
  /* enable clock for the STM32 */
  *((uint32*)0x40023800) |= (1 << 0);
  
  /* enable clock for port A */
  *((uint32*)0x40023830) |= (1 << 0);
  
  /* configuration of pin 9 and pin 10 of PORT A */
  ConfigurationPin pin9PortA = {PORTA_ID, PIN9_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
  ConfigurationPin pin10PortA = {PORTA_ID, PIN10_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
  PORT_configurePin(&pin9PortA);
  PORT_configurePin(&pin10PortA);
  
  /* configuration of UART */
  USART_STRUCT usart1 = {USART1, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 9600};
  UART_init(&usart1);
  
  
  /* configuration of the GPS */
  GPS_setInputOutputModule(&usart1); 
  GPS_init();
  
  //UART_receiveByte(&usart1);
  
  while(1){
    GPS_updateLatitudeAndLongitude();
    GPS_updateLatitudeAndLongitude();
  }
  
  
  
  return 0;  
}
