/*******************************************************************************
 *
 * Module: DIO module
 *
 * File Name: Dio.c
 *
 * Description: source file for the DIO module
 *
 * Author: Saeed Elsayed
 *
 *******************************************************************************/

#include "Dio.h"
#include "Dio_registers.h"
#include "common_macros.h"


/*
 * description : the function is responsible for writing on the pin.
 *
 * parameters  : pointer of type DioPin which holds the pin information.
 *                   
 * return value : NONE.
 */
void Dio_writePin(DioPin* Dio_pin, uint8 data)
{
     /* pointer to hold the start address of the port */
  uint32* outputDataRegisterPtr = NULL_PTR;
  
  /* select the start address of the port */
  switch(Dio_pin->portNumber){
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
  
  /* write the required data on the pin through the output register */
  if(data == LOGIC_HIGH)
  {
    SET_BIT(*((uint32*)(((uint8*)outputDataRegisterPtr) + PORTx_ODR_OFFSET)),Dio_pin->pinNumber);
  }
  else if(data == LOGIC_LOW)
  {
    CLEAR_BIT(*((uint32*)(((uint8*)outputDataRegisterPtr) + PORTx_ODR_OFFSET)),Dio_pin->pinNumber);
  }
  
}

/*
 * description : the function is responsible for reading the pin.
 *
 * parameters  : pointer of type DioPin which holds the pin information.
 *                   
 * return value : the input pin value.
 */
uint8 Dio_readPin(DioPin* Dio_pin)
{
  /* variable to carry the value of the pin */
  uint8 data;
  /* pointer to hold the start address of the port */
  uint32* inputDataRegisterPtr = NULL_PTR;
  
  /* select the start address of the port */
  switch(Dio_pin->portNumber){
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
  /* read the specific pin data and return it */
  data = (*((uint32*)(((uint8*)inputDataRegisterPtr) + PORTx_IDR_OFFSET)) & (1 << Dio_pin->pinNumber)) >> Dio_pin->pinNumber;
  return data;
}