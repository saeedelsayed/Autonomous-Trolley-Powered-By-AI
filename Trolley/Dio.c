#include "Dio.h"
#include "common_macros.h"

void Dio_writePin(ConfigurationPin* configurationPin, uint8 data)
{
     /* pointer to hold the start address of the port */
  uint32* outputDataRegisterPtr = NULL_PTR;
  
  /* select the start address of the port */
  switch(configurationPin->portNumber){
  case PORTA_ID:
    /* start address of port A */
    outputDataRegisterPtr = PORTA_BASE_ADDRESS;
    break;
  case PORTB_ID:
    /* start address of port B */
    outputDataRegisterPtr = PORTB_BASE_ADDRESS;
    break;
  case PORTC_ID:
    /* start address of port C */
    outputDataRegisterPtr = PORTC_BASE_ADDRESS;
    break;
  }
  
  if(data == LOGIC_HIGH)
  {
    SET_BIT(*((uint32*)(((uint8*)outputDataRegisterPtr) + PORTx_ODR_OFFSET)),configurationPin->pinNumber);
  }
  else if(data == LOGIC_LOW)
  {
    CLEAR_BIT(*((uint32*)(((uint8*)outputDataRegisterPtr) + PORTx_ODR_OFFSET)),configurationPin->pinNumber);
  }
}

uint8 Dio_readPin(ConfigurationPin* configurationPin)
{
  uint8 data;
       /* pointer to hold the start address of the port */
  uint32* inputDataRegisterPtr = NULL_PTR;
  
  /* select the start address of the port */
  switch(configurationPin->portNumber){
  case PORTA_ID:
    /* start address of port A */
    inputDataRegisterPtr = PORTA_BASE_ADDRESS;
    break;
  case PORTB_ID:
    /* start address of port B */
    inputDataRegisterPtr = PORTB_BASE_ADDRESS;
    break;
  case PORTC_ID:
    /* start address of port C */
    inputDataRegisterPtr = PORTC_BASE_ADDRESS;
    break;
  }
  
  data = (*((uint32*)(((uint8*)inputDataRegisterPtr) + PORTx_IDR_OFFSET)) & (1 << configurationPin->pinNumber)) >> configurationPin->pinNumber;
  return data;
}