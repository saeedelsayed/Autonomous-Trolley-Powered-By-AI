/******************************************************************************
 *
 * Module: GPS module
 *
 * File Name: gps.h
 *
 * Description: header file for the GPS module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef GPS_H_
#define GPS_H_

#include "std_types.h"
#include "uart_driver.h"


/*******************************************************************************
 *                                External Variables                           *
 *******************************************************************************/

/* varible to hold the latitude value */
extern float64 latitude;

/* varible to hold the longitude value */
extern float64 longitude;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * description : the function is responsible for configuration of the GPS module.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
 */
void GPS_init(void);

/*
 * description : the function is responsible for sending commands to the GPS module.
 *
 * parameters  : pointer to the command to be send.
 *
 * return value : NONE.
 */
void GPS_sendCommand(uint8* command);

/*
 * description : the function is responsible for seting the I/O module 
                 used to communicate with the GPS module.
 *
 * parameters  : pointer to the UART I/O module.
 *
 * return value : NONE.
 */
void GPS_setInputOutputModule(USART_STRUCT* uart);

/*
 * description : the function is responsible for getting new value
                 of the latitude and the longitude.
 *
 * parameters  : NONE.
 *
 * return value : NONE.
 */
void GPS_updateLatitudeAndLongitude(void);

#endif /* GPS_H_ */