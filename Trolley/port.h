/*******************************************************************************
 *
 * Module: PORT module
 *
 * File Name: port.h
 *
 * Description: header file for the PORT module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

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

/* definition for the pin mode */
#define INPUT_MODE         (0x00)
#define OUTPUT_MODE        (0x01)
#define ALTERNATE_MODE     (0x02)
#define ANALOG_MODE        (0x03)

/* definition for the output type*/
#define OUTPUT_PUSH_PULL   (0x00)
#define OUTPUT_OPEN_DRAIN  (0x01)

/* definition for the internal resistor option */
#define NO_PULL_UP_DOWN    (0x00)
#define PULL_UP            (0x01)
#define PULL_DOWN          (0x02)

/* definition for the alternate functions of the pins */
#define NO_ALTERNATE       (0xFF)
#define AF0                (0x00)
#define AF1                (0x01)
#define AF2                (0x02)
#define AF3                (0x03)
#define AF4                (0x04)
#define AF5                (0x05)
#define AF6                (0x06)
#define AF7                (0x07)
#define AF8                (0x08)
#define AF9                (0x09)
#define AF10               (0x0A)
#define AF11               (0x0B)
#define AF12               (0x0C)
#define AF13               (0x0D)
#define AF14               (0x0E)
#define AF15               (0x0F)

/*******************************************************************************
 *                                Declarations                                 *
 *******************************************************************************/

/* strucutre for configuration the pins */
typedef struct{
  /* port ID of the pin */
  uint8 portNumber;
  
  /* pin ID */
  uint8 pinNumber;
  
  /* pin mode input, output, etc... */
  uint8 pinMode;
  
  /* pin output type push-pull, open drain */
  uint8 pinOutputType;
  
  /* pin resistor option */
  uint8 pinPullUpDownOption;
  
  /* initial value of the output pin */
  uint8 pinInitialValue;
  
  /* alternate function of the pin */
  uint8 pinAlternateFunction;
}ConfigurationPin;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * description : the function is responsible for configuration the pin.
 *
 * parameters  : pointer of type ConfigurationPin which holds the pin
 *               configuration information.
 *
 * return value : NONE.
 */
void PORT_configurePin(ConfigurationPin* configurationPin);

#endif /* PORT_H_ */