/******************************************************************************
 *
 * Module: UART module
 *
 * File Name: uart_driver.c
 *
 * Description: source file for the UART module
 *
 * Author: AHMED RADWAN & SAEED ELSAYED
 *
 *******************************************************************************/

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "uart_driver.h"
#include "uart_registers.h"
#include "common_macros.h"

#define F_CPU 16000000

#define RCC_APB1ENR   (*(unsigned long*) (0x40023800+0x40))
#define RCC_APB2ENR   (*(unsigned long*) (0x40023800+0x44))
   
/*******************************************************************************************/
/*********************************** Function Definitions **********************************/
/*******************************************************************************************/

/*
 * description : the function is responsible for initializing  the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information.
 *
 * return value : NONE.
 */
void UART_init(USART_STRUCT * usart)
{
        /* enable the clock for uart1 (warning!!!! it is static) */
        RCC_APB1ENR |= (1 << 17);
	RCC_APB2ENR |= (1 << 4);
	/* first clear all bits of the CR1 register */
	(*(uint32 *)(usart->type + USART_CR1_ADDRESS_OFFSET)) = CLEAR_ALL_BITS;
	/* enable usart */
	(*(uint32 *)(usart->type + USART_CR1_ADDRESS_OFFSET)) |= (UART_ENABLE << UE);
	/* choose the length of word */
	(*(uint32 *)(usart->type + USART_CR1_ADDRESS_OFFSET)) |= (usart->word_length << M);
	/* set number of stop bits */
	(*(uint32 *)(usart->type + USART_CR2_ADDRESS_OFFSET)) |= (usart->stop_bits << STOP);

	/* first clear all bits of the BRR register */
	(*(uint32 *)(usart->type + USART_BRR_ADDRESS_OFFSET)) = CLEAR_ALL_BITS;
	/* calculate the value of USARTDIV and store it in float */
	float32 USARTDIV = (float32)F_CPU/(8*2*usart->baud_rate);
	/* take the integer value to store it in the mantissa bits */
	uint16 USART_BRR_DIV_MANTISSA = (uint16)USARTDIV;
	/* convert the fraction part to an integer to store it in the fraction bits */
	uint8 USART_BRR_DIV_FRACTION = (uint8)( ((USARTDIV - USART_BRR_DIV_MANTISSA) * 16) + 0.5 );
	/* set mantissa */
	(*(uint32 *)(usart->type + USART_BRR_ADDRESS_OFFSET)) |= (USART_BRR_DIV_MANTISSA << DIV_MANTISSA);
	/* set fraction */
	(*(uint32 *)(usart->type + USART_BRR_ADDRESS_OFFSET)) |= (USART_BRR_DIV_FRACTION << DIV_FRACTION);
        /* enable transmitter */
	(*(uint32 *)(usart->type + USART_CR1_ADDRESS_OFFSET)) |= (1 << TE);
	/* enable receiver */
        (*(uint32 *)(usart->type + USART_CR1_ADDRESS_OFFSET)) |= (1 << RE);
}

/*
 * description : the function is responsible for sending one byte using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, the data which is desired to be sent
 *
 * return value : NONE.
 */
void UART_sendByte(USART_STRUCT * usart, uint8 data)
{
        /* wait until the content of the TDR register is been transferred into 
           the shift register */
	while(BIT_IS_CLEAR((*(uint32 *)(usart->type + USART_SR_ADDRESS_OFFSET)),TXE));
	/* write the data to the data register */ 
        (*(uint32 *)(usart->type + USART_DR_ADDRESS_OFFSET)) = data;
}

/*
 * description : the function is responsible for receiving one byte using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information.
 *
 * return value : the data received by the UART.
 */
uint8 UART_receiveByte(USART_STRUCT * usart)
{
        /* wait until the data register receive the data */
	while(BIT_IS_CLEAR((*(uint32 *)(usart->type + USART_SR_ADDRESS_OFFSET)),RXNE) );
	/* read the data */ 
        return (*((volatile uint32 *)(usart->type + USART_DR_ADDRESS_OFFSET)));
}

/*
 * description : the function is responsible for sending a string using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, pointer to the string which is desired 
 *               to be sent 
 *
 * return value : NONE.
 */
void UART_sendString(USART_STRUCT* usart, uint8* Str)
{
      /* a variable to check every index in the string to know if we reached the 
         end of the string('\0') or not yet */
	uint8 i = 0;
        /* as long as we did not reach the end of the string continue to send the bytes*/
	while(Str[i] != '\0')
	{
		UART_sendByte(usart, Str[i]);
		i++;
	}
}

/*
 * description : the function is responsible for receiving a string using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, pointer to the array in which we will
 *               store the data               
 *
 * return value : NONE.
 */
void UART_receiveString(USART_STRUCT* usart, uint8* Str)
{
	uint8 i = 0;
	Str[i] = UART_receiveByte(usart);
      /* check if we reached the end of the data ('\r' in case of bluetoohe module) */
	while(Str[i] != '\r')
	{
		i++;
		Str[i] = UART_receiveByte(usart);


	}
        UART_receiveByte(usart);
        Str[i] = '\0';
        volatile uint8 x =0;
        x++;
}
