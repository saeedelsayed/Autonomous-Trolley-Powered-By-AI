/**
 * @file uart_registers.h
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief uart registers header file
 * @date 27-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UART_REGISTERS_H
#define	UART_REGISTERS_H

/*******************************************************************************************/
/*********************************** UART Registers ****************************************/
/*******************************************************************************************/
#define USART1 (*((volatile uint32 *)0x40011000))
#define USART2 (*((volatile uint32 *)0x40004400))
#define USART6 (*((volatile uint32 *)0x40011400))

#define USART1_SR (*((volatile uint32 *)0x40011000))
#define USART2_SR (*((volatile uint32 *)0x40004400))
#define USART6_SR (*((volatile uint32 *)0x40011400))
enum {
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

#define USART1_DR (*((volatile uint32 *)0x40011004))
#define USART2_DR (*((volatile uint32 *)0x40004404))
#define USART6_DR (*((volatile uint32 *)0x40011404))

#define USART1_BRR (*((volatile uint32 *)0x40011008))
#define USART2_BRR (*((volatile uint32 *)0x40004408))
#define USART6_BRR (*((volatile uint32 *)0x40011408))
#define USART_BRR_DIV_MANTISSA 0x222 // 546
#define USART_BRR_DIV_FRACTION 0xE   // 14
enum {
    DIV_MANTISSA = 4,
    DIV_FRACTION = 0
} USART_BRR_BITS;

#define USART1_CR1 (*((volatile uint32 *)0x4001100C))
#define USART2_CR1 (*((volatile uint32 *)0x4000440C))
#define USART6_CR1 (*((volatile uint32 *)0x4001140C))
enum {
    SBK = 0,
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

#define USART1_CR2 (*((volatile uint32 *)0x40011010))
#define USART2_CR2 (*((volatile uint32 *)0x40004410))
#define USART6_CR2 (*((volatile uint32 *)0x40011410))
enum {
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

#define USART1_CR3 (*((volatile uint32 *)0x40011014))
#define USART2_CR3 (*((volatile uint32 *)0x40004414))
#define USART6_CR3 (*((volatile uint32 *)0x40011414))
enum {
    EIE = 0,
    IREN,
    IRLP,
    HDSEL,
    NACK,
    SCEN,
    DMAR,
    DMAT,
    RTSE,
    CTSE,
    CTSIE,
    ONEBIT
} USART_CR3_BITS;

#define USART1_GTPR (*((volatile uint32 *)0x40011018))
#define USART2_GTPR (*((volatile uint32 *)0x40004418))
#define USART6_GTPR (*((volatile uint32 *)0x40011418))

#endif    /* UART_REGISTERS_H */