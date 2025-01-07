/*
 * ExtInterrupt_private.h
 *
 *  Created on: Sep 12, 2022
 *      Author: abram
 */

#ifndef INC_EXTINTERRUPT_PRIVATE_H_
#define INC_EXTINTERRUPT_PRIVATE_H_



/******************************************************************
 * External Interrupt Registers
 *****************************************************************/
#define MCUCR	                        *((volatile uint8*) 0x55)
#define MCUCSR	                        *((volatile uint8*) 0x54)
#define GICR	                        *((volatile uint8*) 0x5B)
#define GIFR	                        *((volatile uint8*) 0x5A)
/******************************************************************
 * Global Interrupt Enable Registers
 *****************************************************************/
#define SREG	                        *((volatile uint8*) 0x5F)



/***************EXternal Interrupt***************/
#define VECTOR_INT0           __vector_1
#define VECTOR_INT1           __vector_2
#define VECTOR_INT2           __vector_3



#define ISR(vector) \
void vector(void) __attribute__((signal)); \
void vector(void)


/************* MCUCR Register Bits *************/
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

/************* MCUCSR Register Bits *************/
#define MCUCSR_ISC2 6

/************* GICR Register Bits *************/
#define GICR_INT2 5
#define GICR_INT0 6
#define GICR_INT1 7

/************* GIFR Register Bits *************/
#define GIFR_INTF2 5
#define GIFR_INTF0 6
#define GIFR_INTF1 7
#define SREG_I 7

/************* Configurations *************/
#define EXTERNAL_INTERRUPT_RISING       1
#define EXTERNAL_INTERRUPT_FALLING      2
#define EXTERNAL_INTERRUPT_ON_CHANGE    3
#define EXTERNAL_INTERRUPT_LOW_LEVEL    4
#define EXTERNAL_INTERRUPT_OFF          5

#endif /* INC_EXTINTERRUPT_PRIVATE_H_ */
