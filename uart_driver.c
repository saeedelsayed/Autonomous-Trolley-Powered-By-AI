/**
 * @file uart_driver.c
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief uart driver source file
 * @date 27-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "uart_driver.h"
#include "uart_registers.h"
#include "gpio.h"
#include "gpio_registers.h"

/*******************************************************************************************/
/*********************************** Function Definitions **********************************/
/*******************************************************************************************/

void UART_init(uint8 uart_PinConfig)
{
    switch (uart_PinConfig)
    {
    case UART1_PIN_PA9_PA10:
        GPIO_pinConfiguration(PORTA_ID, PIN9_ID, OUTPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);  // TX pin
        GPIO_pinConfiguration(PORTA_ID, PIN10_ID, INPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);  // RX pin

        USART1_CR1 = CLEAR_ALL_BITS;                                                          // clear all bits
        USART1_CR1 |= (UART_ENABLE << UE);                                                    // enable uart
        USART1_CR1 |= (UART_8_BIT_WORD << M);                                                 // 8 bit word
        USART1_CR2 |= (UART_1_STOP_BIT << STOP);                                              // 1 stop bit
        USART1_CR3 |= (UART_ENABLE_DMA << DMAT);                                              // enable dma

        USART1_BRR = CLEAR_ALL_BITS;                                                          // clear all bits
        USART1_BRR |= (USART_BRR_DIV_MANTISSA << DIV_MANTISSA);                               // set mantissa
        USART1_BRR |= (USART_BRR_DIV_FRACTION << DIV_FRACTION);                               // set fraction
        break;
    case UART2_PIN_PA2_PA3:
        GPIO_pinConfiguration(PORTA_ID, PIN2_ID, OUTPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);  // TX pin
        GPIO_pinConfiguration(PORTA_ID, PIN3_ID, INPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);   // RX pin

        USART2_CR1 = CLEAR_ALL_BITS;                                                          // clear all bits
        USART2_CR1 |= (UART_ENABLE << UE);                                                    // enable uart
        USART2_CR1 |= (UART_8_BIT_WORD << M);                                                 // 8 bit word
        USART2_CR2 |= (UART_1_STOP_BIT << STOP);                                              // 1 stop bit
        USART2_CR3 |= (UART_ENABLE_DMA << DMAT);                                              // enable dma

        USART2_BRR = CLEAR_ALL_BITS;                                                          // clear all bits
        USART2_BRR |= (USART_BRR_DIV_MANTISSA << DIV_MANTISSA);                               // set mantissa
        USART2_BRR |= (USART_BRR_DIV_FRACTION << DIV_FRACTION);                               // set fraction
        break;
    case UART6_PIN_PC6_PC7:
        GPIO_pinConfiguration(PORTC_ID, PIN6_ID, OUTPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);  // TX pin
        GPIO_pinConfiguration(PORTC_ID, PIN7_ID, INPUT_PIN, PIN_LOW, PULL_UP_DEACTIVATION);   // RX pin

        USART6_CR1 = CLEAR_ALL_BITS;                                                          // clear all bits
        USART6_CR1 |= (UART_ENABLE << UE);                                                    // enable uart
        USART6_CR1 |= (UART_8_BIT_WORD << M);                                                 // 8 bit word
        USART6_CR2 |= (UART_1_STOP_BIT << STOP);                                              // 1 stop bit
        USART6_CR3 |= (UART_ENABLE_DMA << DMAT);                                              // enable dma

        USART6_BRR = CLEAR_ALL_BITS;                                                          // clear all bits
        USART6_BRR |= (USART_BRR_DIV_MANTISSA << DIV_MANTISSA);                               // set mantissa
        USART6_BRR |= (USART_BRR_DIV_FRACTION << DIV_FRACTION);                               // set fraction
        break;
    default:
        break;
    }

}




