/******************************************************************************
 *
 * Module: Services for the main application
 *
 * File Name: services.h
 *
 * Description: header file for the services of main application
 *
 * Author: All team
 *
 *******************************************************************************/

#ifndef SERVICES_H_
#define SERVICES_H_

#include "port.h"
#include "uart_registers.h"
#include "i2c_registers.h"
#include "uart_driver.h"
#include "i2c_driver.h"
#include "gps.h"
#include "bluetooth.h"
#include "Qmc5883l.h"


/*******************************************************************************
 *                                pin declarations                             * 
 *******************************************************************************/

/* pin declaration for USART1 */
extern ConfigurationPin usart1TX;
extern ConfigurationPin usart1RX;

/* pin declaration for USART2 */
extern ConfigurationPin usart2TX;
extern ConfigurationPin usart2RX;

/* pin declaration for I2C1 */
extern ConfigurationPin i2c1SDA;
extern ConfigurationPin i2c1SCL;

/*******************************************************************************
 *                                I/O modules declarations                     * 
 *******************************************************************************/

/* declaration of USART1 I/O module */
extern USART_STRUCT usart1;

/* declaration of USART2 I/O module */
extern USART_STRUCT usart2;

/* declaration of I2C1 I/O module */
extern I2C_config_t i2c1;

/*******************************************************************************
 *                                function prototypes                          * 
 *******************************************************************************/

/*
 * description : the function is responsible for initializing the system.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
*/
void SERVICES_systemInit(void);

#endif