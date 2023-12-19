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
#include "uart_driver.h"
#include "i2c_driver.h"

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
 *                                User Data                                    * 
 *******************************************************************************/

/* variable to hold the user latitude */
extern float64 userLatitude;

/* variable to hold the user longitiude */
extern float64 userLongitude;

/* variable to hold the user direction */
extern uint8 userDirection;

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

/*
 * description : the function is responsible for updating user data.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
*/
void SERVICES_updateUserData(void);

/*
 * description : the function is responsible for updating trolley data.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
*/
void SERVICES_updateTrolleyData(void);
   
/*
 * description : the function is responsible for getting the distance between the user and
                 the trolley.
 *
 * parameters  : NONE.
 *
 * return value : the distance.
*/
float32 SERVICES_getDistance(void);

#endif