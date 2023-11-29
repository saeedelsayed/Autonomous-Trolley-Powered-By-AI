/******************************************************************************
 *
 * Module: UART module
 *
 * File Name: uart_registers.h
 *
 * Description: registers file for the UART module
 *
 * Author: AHMED RADWAN & SAEED ELSAYED
 *
 *******************************************************************************/

#ifndef UART_REGISTERS_H
#define	UART_REGISTERS_H

/*******************************************************************************************/
/*********************************** UART Registers ****************************************/
/*******************************************************************************************/

/* the start address of each UART */
#define USART1 0x40011000
#define USART2 0x40004400
#define USART6 0x40011400

/* the offset of registers of the UART */
#define USART_SR_ADDRESS_OFFSET  0x00
#define USART_DR_ADDRESS_OFFSET  0x04
#define USART_BRR_ADDRESS_OFFSET 0x08
#define USART_CR1_ADDRESS_OFFSET 0x0C
#define USART_CR2_ADDRESS_OFFSET 0x10


/*******************************************************************************************/
/*********************************** Registers enums****************************************/
/*******************************************************************************************/

/* enum for bits of the Status register */
typedef enum {
    PE = 0,
    FE,
    NF,
    ORE,
    IDLE,
    RXNE,
    TC,
    TXE,
    LBD,
    CTS
} USART_SR_BITS;

/* enum for start bits of mantissa and fraction parts 
   in the baud rate register */
typedef enum {
    DIV_MANTISSA = 4,
    DIV_FRACTION = 0
} USART_BRR_BITS;

/* enum for bits of the control register 1 */
typedef enum
{
    SBK,
    RWU,
    RE,
    TE,
    IDLEIE,
    RXNEIE,
    TCIE,
    TXEIE,
    PEIE,
    PS,
    PCE,
    WAKE,
    M,
    UE
} USART_CR1_BITS;

/* enum for bits of the control register 2 */
typedef enum {
    ADD   = 0,
    LBDL  = 5,
    LBDIE = 6,
    LBCL  = 8,
    CPHA  = 9,
    CPOL  = 10,
    CLKEN = 11,
    STOP  = 12,
    LINEN = 14
} USART_CR2_BITS;


#endif    /* UART_REGISTERS_H */
