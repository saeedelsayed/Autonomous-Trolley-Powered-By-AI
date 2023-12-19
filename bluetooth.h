/******************************************************************************
 *
 * Module: Bluetooth module
 *
 * File Name: bluetooth.h
 *
 * Description: header file for the Bluetooth module
 *
 * Author: Mazen Tarek
 *
 *******************************************************************************/

#ifndef BLUETOOTH_DRIVER_H
#define BLUETOOTH_DRIVER_H

#include "uart_driver.h"


void Bluetooth_setInputOutputModule(USART_STRUCT* uart);
void Bluetooth_receiveString(uint8* str);
void Bluetooth_sendString(uint8* str);
void Bluetooth_sendCharacter(uint8 character);


#endif /* BLUETOOTH_DRIVER_H */