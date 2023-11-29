/******************************************************************************
 *
 * Module: PORT module
 *
 * File Name: port.c
 *
 * Description: source file for the PORT module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "std_types.h"
#include "port_registers.h"
#include "port.h"

/*
 * description : the function is responsible for configuration the pin.
 *
 * parameters  : pointer of type ConfigurationPin which holds the pin
 *               configuration information.
 *
 * return value : NONE.
 */
void PORT_configurePin(ConfigurationPin* configurationPin){
  /* pointer to hold the start address of the port */
  uint32* startAddressPtr = NULL_PTR;
  
  /* select the start address of the port */
  switch(configurationPin->portNumber){
  case PORTA_ID:
    /* start address of port A */
    startAddressPtr = PORTA_BASE_ADDRESS;
    break;
  case PORTB_ID:
    /* start address of port B */
    startAddressPtr = PORTB_BASE_ADDRESS;
    break;
  case PORTC_ID:
    /* start address of port C */
    startAddressPtr = PORTC_BASE_ADDRESS;
    break;
  }
  
  /* set the pin mode through the mode register */
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_MODER_OFFSET)) &=
    ~(0x03 << (configurationPin->pinNumber * 2));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_MODER_OFFSET)) |=
     (configurationPin->pinMode << (configurationPin->pinNumber * 2));
  
  /* set the output type through the output type register */ 
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_OTYPER_OFFSET)) &=
    ~(0x01 << (configurationPin->pinNumber));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_OTYPER_OFFSET)) |=
     (configurationPin->pinOutputType << (configurationPin->pinNumber));
  
  /* set the internal resistor option through the pull up pull down register */
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_PUPDR_OFFSET)) &=
    ~(0x03 << (configurationPin->pinNumber * 2));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_PUPDR_OFFSET)) |=
     (configurationPin->pinPullUpDownOption << (configurationPin->pinNumber * 2));
  
  /* set the pin with initial value through output data register */
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_ODR_OFFSET)) &=
    ~(0x01 << (configurationPin->pinNumber));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_ODR_OFFSET)) |=
     (configurationPin->pinInitialValue << (configurationPin->pinNumber));

  /* set the alternate function of the pin */
  if(configurationPin->pinAlternateFunction != NO_ALTERNATE){
    /* set alternate function of pins to 7 */
    if(configurationPin->pinNumber < PIN8_ID){
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_AFRL_OFFSET)) &=
    ~(0x0F << (configurationPin->pinNumber * 4));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_AFRL_OFFSET)) |=
     (configurationPin->pinAlternateFunction << (configurationPin->pinNumber * 4));
    }else{
      /* set alternate function of pins 8 to 15 */
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_AFRH_OFFSET)) &=
    ~(0x0F << (configurationPin->pinNumber * 4));
  *((uint32*)(((uint8*)startAddressPtr) + PORTx_AFRH_OFFSET)) |=
     (configurationPin->pinAlternateFunction << ((configurationPin->pinNumber - 8) * 4));
    }
  }
}