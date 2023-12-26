/*******************************************************************************
 *
 * Module: DIO module
 *
 * File Name: Dio_registers.h
 *
 * Description: registers defintion for the DIO module
 *
 * Author: Saeed Elsayed
 *
 *******************************************************************************/

#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Definition of the start address of the ports */
#define PORTA_BASE_ADDRESS     ((uint32 *)0x40020000)
#define PORTB_BASE_ADDRESS     ((uint32 *)0x40020400)
#define PORTC_BASE_ADDRESS     ((uint32 *)0x40020800)


#define PORTx_IDR_OFFSET             (0x10) 
#define PORTx_ODR_OFFSET             (0x14)

#endif /* DIO_REGISTERS_H_ */