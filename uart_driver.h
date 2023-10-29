/**
 * @file uart_driver.h
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief uart driver header file
 * @date 27-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _UART_DRIVER_H
#define _UART_DRIVER_H

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "std_types.h"

/*******************************************************************************************/
/************************************ Defines **********************************************/
/*******************************************************************************************/
#define CLEAR_ALL_BITS           0x00

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

/* uart dma configuration */
#define UART_DISABLE_DMA         0x00
#define UART_ENABLE_DMA          0x01

/* uart pins configuration */
#define UART1_PIN_PA9_PA10        0x01
#define UART2_PIN_PA2_PA3         0x00
#define UART6_PIN_PC6_PC7         0x02

/*******************************************************************************************/
/*********************************** Function Declarations *********************************/
/*******************************************************************************************/

/**
 * @brief uart driver initialization function
 * 
 */
void UART_init(uint8 uart_PinConfig);
/**
 * @brief uart driver send function
 *
 * @param data
 */
void UART_send(uint8 data);
/**
 * @brief uart driver receive function
 * 
 * @return uint8 
 */
uint8 UART_receive(void);





#endif // _UART_DRIVER_H