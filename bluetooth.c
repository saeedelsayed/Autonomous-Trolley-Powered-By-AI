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

static USART_STRUCT* bluetoothInputOuputModule = NULL_PTR;

void Bluetooth_setInputOutputModule(USART_STRUCT* uart){
  bluetoothInputOuputModule = uart;
}

void Bluetooth_receiveString(uint8* str) {
    UART_receiveString(bluetoothInputOuputModule, str);
}

void Bluetooth_sendString(uint8* str)
{
  UART_sendString(bluetoothInputOuputModule, str);
}

void Bluetooth_sendCharacter(uint8 character){
  UART_sendByte(bluetoothInputOuputModule, character);
}