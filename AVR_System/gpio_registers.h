/******************************************************************************
 *
 * Module: GPIO module
 *
 * File Name: gpio_registers.h
 *
 * Description: registers defintion for the GPIO module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef GPIO_REGISTERS_H_
#define GPIO_REGISTERS_H_

#include "std_types.h"

/* Definition of tha start address of the ports */
#define PORTA_START_ADDRESS    ((uint8 *)0x39)
#define PORTB_START_ADDRESS    ((uint8 *)0x36)
#define PORTC_START_ADDRESS    ((uint8 *)0x33)
#define PORTD_START_ADDRESS    ((uint8 *)0x30)

/* Definition of the offset of registers from start address */
#define DATA_INPUT_REGISTER_OFFSET          (0x00)
#define DATA_DIRECTION_REGISTER_OFFSET      (0x01)
#define DATA_OUTPUT_REGISTER_OFFSET         (0x02)

#endif /* GPIO_REGISTERS_H_ */
