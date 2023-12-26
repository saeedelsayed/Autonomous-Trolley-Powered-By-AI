/*******************************************************************************
 *
 * Module: DIO module
 *
 * File Name: Dio.h
 *
 * Description: header file for the DIO module
 *
 * Author: Saeed Elsayed
 *
 *******************************************************************************/

#ifndef DIO_H_
#define DIO_H_


#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* definition for the ports ID */
#define PORTA_ID           (0x00)
#define PORTB_ID           (0x01)
#define PORTC_ID           (0x02)

/* definition for the pins ID */
#define PIN0_ID            (0x00)
#define PIN1_ID            (0x01)
#define PIN2_ID            (0x02)
#define PIN3_ID            (0x03)
#define PIN4_ID            (0x04)
#define PIN5_ID            (0x05)
#define PIN6_ID            (0x06)
#define PIN7_ID            (0x07)
#define PIN8_ID            (0x08)
#define PIN9_ID            (0x09)
#define PIN10_ID           (0x0A)
#define PIN11_ID           (0x0B)
#define PIN12_ID           (0x0C)
#define PIN13_ID           (0x0D)
#define PIN14_ID           (0x0E)
#define PIN15_ID           (0x0F)


/*******************************************************************************
 *                                Declarations                                 *
 *******************************************************************************/

/* strucutre to know which pin and port need to be read or written */
typedef struct{
  /* port ID of the pin */
  uint8 portNumber;
  /* pin ID */
  uint8 pinNumber;

}DioPin;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * description : the function is responsible for writing on the pin.
 *
 * parameters  : pointer of type DioPin which holds the pin information.
 *                   
 * return value : NONE.
 */
void Dio_writePin(DioPin* Dio_pin, uint8 data);

/*
 * description : the function is responsible for reading the pin.
 *
 * parameters  : pointer of type DioPin which holds the pin information.
 *                   
 * return value : the input pin value.
 */
uint8 Dio_readPin(DioPin* Dio_pin);

#endif /* DIO_H_ */