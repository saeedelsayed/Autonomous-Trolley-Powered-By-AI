#include "port.h"
#include "uart_driver.h"
#include "uart_registers.h"



int main()
{
  /* enable clock for portA */
  *((uint32*)0x40023800) |= (1 << 0);
  *((uint32*)0x40023830) |= (1 << 0);
  
  
  for(uint8 i = PIN0_ID; i <= PIN15_ID; i++)
  {
      ConfigurationPin pin = {PORTA_ID, i, INPUT_MODE, OUTPUT_PUSH_PULL, PULL_UP, LOGIC_LOW, NO_ALTERNATE};
 
      PORT_configurePin(&pin);
  }
  /* testing if the port & uart drivers work together or not */
  ConfigurationPin pin9PortA = {PORTA_ID, PIN9_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, PULL_UP, LOGIC_LOW, AF7};
  ConfigurationPin pin10PortA = {PORTA_ID, PIN10_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, PULL_UP, LOGIC_LOW, AF7};
  
  PORT_configurePin(&pin9PortA);
  PORT_configurePin(&pin10PortA);
  
  USART_STRUCT usart1 = {USART1, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 9600};
  UART_init(&usart1);
  
  uint8* Str = "final\r\n";
  UART_sendString(&usart1, Str);
  uint8 data;  
  while(1){
   
    data = UART_receiveByte(&usart1);
    UART_sendByte(&usart1,data);
  }
 
}
