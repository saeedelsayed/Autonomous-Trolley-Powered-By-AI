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

#define BLUETOOTH_BUFFER_SIZE 64

void Bluetooth_Init(uint32 uart_type);
void Bluetooth_ReceiveString(uint8* receivedString);
void Bluetooth_sendString(uint8* sendString);


#endif /* BLUETOOTH_DRIVER_H�*/