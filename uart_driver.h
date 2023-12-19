/******************************************************************************
 *
 * Module: UART module
 *
 * File Name: uart_driver.h
 *
 * Description: header file for the UART module
 *
 * Author: AHMED RADWAN & SAEED ELSAYED
 *
 *******************************************************************************/

#ifndef _UART_DRIVER_H
#define _UART_DRIVER_H

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "std_types.h"

/*******************************************************************************************/
/************************************ Defines **********************************************/
/*******************************************************************************************/
//#define CLEAR_ALL_BITS           0x0000

/* uart configuration */
#define UART_ENABLE              0x01
#define UART_DISABLE             0x00

/* uart word length */
#define UART_8_BIT_WORD          0x00
#define UART_9_BIT_WORD          0x01

/* uart stop bit */
#define UART_1_STOP_BIT          0x00
#define UART_2_STOP_BIT          0x01
#define UART_1_5_STOP_BIT        0x02


/*******************************************************************************************/
/*********************************** USART_STRUCT ******************************************/
/*******************************************************************************************/

/* a struct that holds the required information of the uart to configure it */
typedef struct {
	uint32 type;   /* holds the start address of the UART */
	uint8 state;   /* holds the initial state of the UART */
	uint8 word_length; /* holds the number of bits of the UART word*/
	uint8 stop_bits;  /* holds the number of stop bits of the UART word*/
	uint32 baud_rate; /* holds the baud rate of the UART */
}USART_STRUCT;

/*******************************************************************************************/
/*********************************** Function Declarations *********************************/
/*******************************************************************************************/

/*
 * description : the function is responsible for initializing  the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information.
 *
 * return value : NONE.
 */
void UART_init(USART_STRUCT * usart);

/*
 * description : the function is responsible for sending one byte using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, the data which is desired to be sent
 *
 * return value : NONE.
 */
void UART_sendByte(USART_STRUCT * usart, uint8 data);

/*
 * description : the function is responsible for receiving one byte using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information.
 *
 * return value : the data received by the UART.
 */
uint8 UART_receiveByte(USART_STRUCT * usart);

/*
 * description : the function is responsible for sending a string using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, pointer to the string which is desired 
 *               to be sent 
 *
 * return value : NONE.
 */
void UART_sendString(USART_STRUCT * usart, uint8* str);

/*
 * description : the function is responsible for receiving a string using the UART.
 *
 * parameters  : pointer of type USART_STRUCT which holds the UART
 *               configuration information, pointer to the array in which we will
 *               store the data               
 *
 * return value : NONE.
 */
void UART_receiveString(USART_STRUCT * usart, uint8* Str);



#endif /* _UART_DRIVER_H */
