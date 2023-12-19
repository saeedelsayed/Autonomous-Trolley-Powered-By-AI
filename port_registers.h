/*******************************************************************************
 *
 * Module: PORT module
 *
 * File Name: port_registers.h
 *
 * Description: registers defintion for the PORT module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef PORT_REGISTERS_H_
#define PORT_REGISTERS_H_


#include "std_types.h"


/* Definition of the start address of the ports */
#define PORTA_BASE_ADDRESS     ((uint32 *)0x40020000)
#define PORTB_BASE_ADDRESS     ((uint32 *)0x40020400)
#define PORTC_BASE_ADDRESS     ((uint32 *)0x40020800)


/* definition of the offset of the registers from start address */
#define PORTx_MODER_OFFSET           (0x00)
#define PORTx_OTYPER_OFFSET          (0x04)
#define PORTx_PUPDR_OFFSET           (0x0C)
#define PORTx_ODR_OFFSET             (0x14)
#define PORTx_AFRL_OFFSET            (0x20)
#define PORTx_AFRH_OFFSET            (0x24)


#endif /* PORT_REGISTERS_H_ */