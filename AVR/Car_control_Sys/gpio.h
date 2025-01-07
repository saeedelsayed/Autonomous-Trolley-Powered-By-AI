/******************************************************************************
 *
 * Module: GPIO module
 *
 * File Name: gpio.h
 *
 * Description: header file for the GPIO module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* definition of total number pf ports and pins */
#define TOTAL_NUMBER_OF_PORTS   0x04
#define TOTAL_NUMBER_OF_PINS    0x08

/* ports definition */
#define PORTA_ID   0x00
#define PORTB_ID   0x01
#define PORTC_ID   0x02
#define PORTD_ID   0x03

/* pins definition */
#define PIN0_ID    0x00
#define PIN1_ID    0x01
#define PIN2_ID    0x02
#define PIN3_ID    0x03
#define PIN4_ID    0x04
#define PIN5_ID    0x05
#define PIN6_ID    0x06
#define PIN7_ID    0x07

/* pin mode definition */
#define INPUT_PIN  0x00
#define OUTPUT_PIN 0x01

/* pin pull up option activation */
#define PULL_UP_DEACTIVATION     0x00
#define PULL_UP_ACTIVATION       0x01

/* reporting Error enable */
#define GPIO_REPORTING_ERROR OFF

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * description : the function is used to configure the required pin in the required
 *               port as input or output as specified in the pinMode parameter. It is
 *               also responsible for reporting success or failure of the operation.
 *
 * parameters  : portId represents port number, pinId represents pin number,
 *               pinMode represents input or output mode of the pin, pinInitialState
 *               represents initial state of the output pin, pinPullUpActivation
 *               represents activation of the pull up option.
 *
 * return value : the function returns success or failure of the configuration.
 */
uint8 GPIO_pinConfiguration(uint8 portId, uint8 pinId, uint8 pinMode,
		uint8 pinInitialState, uint8 pinPullUpActivation);

/*
 * description : the function is used to write the required pin in the required
 *               port with the specified value in the pinValue parameter. It is
 *               also responsible for reporting success or failure of the operation.
 *
 * parameters  : portId represents port number, pinId represents pin number,
 *               pinValue represents the value to be written.
 *
 * return value : the function returns success or failure of the operation.
 */
uint8 GPIO_writePin(uint8 portId, uint8 pinId, uint8 pinValue);

/*
 * description : the function is used to read the required pin in the required
 *               port and put the value in the pinValue_ptr. It is also responsible
 *               for reporting success or failure of the operation.
 *
 * parameters  : portId represents port number, pinId represents pin number,
 *               pinValue_ptr represents the location in which the value should be
 *               written.
 *
 * return value : the function returns success or failure of the operation.
 */
uint8 GPIO_readPin(uint8 portId, uint8 pinId, uint8 *pinValue_ptr);

#endif /* GPIO_H_ */
