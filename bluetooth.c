/******************************************************************************
 *
 * Module: Bluetooth driver
 *
 * File Name: bluetooth.c
 *
 * Author: Mazen Tarek
 *
 *******************************************************************************/

#include "bluetooth.h"

USART_STRUCT usartConfig;

char bluetoothBuffer[BLUETOOTH_BUFFER_SIZE];
//volatile uint8_t bluetoothBufferIndex = 0;

void Bluetooth_Init(uint32 uart_type) {
    // Initialize UART
    usartConfig.type = uart_type;  // Change this if using a different USART
    usartConfig.state = UART_ENABLE;
    usartConfig.word_length = UART_8_BIT_WORD;
    usartConfig.stop_bits = UART_1_STOP_BIT;
    usartConfig.baud_rate = 38400;  // Adjust baud rate as needed
    UART_init(&usartConfig);

    // Enable USART2 interrupt
//    USART2->CR1 |= USART_CR1_RXNEIE;

    // Enable USART2 in the NVIC
//    NVIC_SetPriority(USART2_IRQn, 0);
//    NVIC_EnableIRQ(USART2_IRQn);
}

//void USART2_IRQHandler(void) {
    //if (USART2->SR & USART_SR_RXNE) {
     //   char receivedChar = USART2->DR;

        // Check for the end of the string (assuming '\r' is the end character)
      //  if (receivedChar == '\r') {
      //      bluetoothBuffer[bluetoothBufferIndex] = '\0'; // Null-terminate the string
      //      bluetoothBufferIndex = 0;
       // } else {
        //    bluetoothBuffer[bluetoothBufferIndex++] = receivedChar;

            // Check for buffer overflow
          //  if (bluetoothBufferIndex >= BLUETOOTH_BUFFER_SIZE - 1) {
                // Buffer full, reset index
           //     bluetoothBufferIndex = 0;
          //  }
     //   }
   // }
//}

void Bluetooth_ReceiveString(uint8* receivedString) {
    // Copy the received string to the provided buffer
  //  strncpy(receivedString, bluetoothBuffer, maxSize);
    UART_receiveString(&usartConfig, receivedString);
    // Null-terminate the copied string
   // receivedString[maxSize�-�1]�=�'\0';
}

void Bluetooth_sendString(uint8* sendString)
{
  UART_sendString(&usartConfig, sendString);
}