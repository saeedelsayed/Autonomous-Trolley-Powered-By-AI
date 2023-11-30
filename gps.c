/******************************************************************************
*
* Module: GPS module
*
* File Name: gps.c
*
* Description: source file for the GPS module
*
* Author: Abdelrahman Saeed
*
*******************************************************************************/

#include "std_types.h"
#include "gps_commands.h"
#include "gps.h"
#include "uart_driver.h"
#include <stdlib.h>
#include <string.h>

/* variable to hold latitude */
float64 latitude = 0.0;

/* variable to hold longitude */
float64 longitude = 0.0;

/* pointer to the I/O module used to communicate with the GPS module */
static USART_STRUCT* gpsInputOutputModule = NULL_PTR;

/* array to hold the GLL message sent by the GPS module */
static uint8 gpsGllMessage[100];

/* prototype of the private function used to decode the GLL message */
static void GPS_decodeGllMessage(void);


/*
* description : the function is responsible for configuration of the GPS module.
*
* parameters  : NONE.
*
* return value : NONE.
*/
void GPS_init(void){
  /* configure the GPS to send GLL message only */
  
  /* disable VTG message */
  GPS_sendCommand(DISABLE_VTG_MESSAGE);
  
  /* disable RMC message */
  GPS_sendCommand(DISABLE_RMC_MESSAGE);
  
  /* disable GGA message */
  GPS_sendCommand(DISABLE_GGA_MESSAGE);
  
  /* disable GSA message */
  GPS_sendCommand(DISABLE_GSA_MESSAGE);
  
  /* disable GSV message */
  GPS_sendCommand(DISABLE_GSV_MESSAGE);
}

/*
* description : the function is responsible for sending commands to the GPS module.
*
* parameters  : pointer to the command to be send.
*
* return value : NONE.
*/
void GPS_sendCommand(uint8* command){
  /* send the command through the I/O module to the GPS */
  UART_sendString(gpsInputOutputModule, command);
}

/*
* description : the function is responsible for seting the I/O module 
used to communicate with the GPS module.
*
* parameters  : pointer to the UART I/O module.
*
* return value : NONE.
*/
void GPS_setInputOutputModule(USART_STRUCT* uart){
  gpsInputOutputModule = uart;
}

/*
* description : the function is responsible for getting new value
of the latitude and the longitude.
*
* parameters  : NONE.
*
* return value : NONE.
*/
void GPS_updateLatitudeAndLongitude(void){
  /* get new GLL message from the GPS */
  UART_receiveString(gpsInputOutputModule, gpsGllMessage);
  
  /* decode the message to get the value of the latitude and the longitude */
  GPS_decodeGllMessage();
}

/*
* description : the function is responsible for decoding the GLL message.
*
* parameters  : NONE.
*
* return value : NONE.
*/
static void GPS_decodeGllMessage(void){
  
  /* check if there is a vaild message */
  if(gpsGllMessage[strlen((char const *)gpsGllMessage) - 6] == 'V'){
    return;
  }
  
  /* extract the latitude and the longitude from the message */
  latitude = atof((char const *)(gpsGllMessage + 7));
  longitude = atof((char const *)(gpsGllMessage + 19));
  
  /* convert the degrees and minutes to decimal */
  float64 temp = ((uint32) (latitude / 100.0));
  latitude = temp + ((latitude - (temp * 100)) / 60.0);
  
  temp = ((uint32) (longitude / 100.0));
  longitude = temp + ((longitude - (temp * 100)) / 60.0);
  
  /* set the negative sign in case of south and west */
  if(gpsGllMessage[17] == 'S'){
    latitude = -1 * latitude;
  }
  
  if(gpsGllMessage[30] == 'W'){
    longitude = -1 * longitude;
  }
}