/*******************************************************************************
*
* Module: Services for the main application
*
* File Name: services.c
*
* Description: source file for the services of main application
*
* Author: All team
*
*******************************************************************************/

#include "services.h"
#include "uart_registers.h"
#include "i2c_registers.h"
#include "gps.h"
#include "bluetooth.h"
#include "Qmc5883l.h"
#include <stdlib.h>
#include <math.h>

/* definition of the constant PI */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* definition of the request ID to get user data */
#define REQUEST_TO_GET_USER_DATA_ID  'S'

/* definition of the address of the AVR slave */
#define AVR_SLAVE_ADDRESS            0x0F

/* pin definition for USART1 */
ConfigurationPin usart1TX = {PORTA_ID, PIN9_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
ConfigurationPin usart1RX = {PORTA_ID, PIN10_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};

/* pin definition for USART2 */
ConfigurationPin usart2TX = {PORTA_ID, PIN2_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};
ConfigurationPin usart2RX = {PORTA_ID, PIN3_ID, ALTERNATE_MODE, OUTPUT_PUSH_PULL, NO_PULL_UP_DOWN, LOGIC_HIGH, AF7};

/* pin definition for I2C1 */
ConfigurationPin i2c1SDA = {PORTB_ID, PIN7_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};
ConfigurationPin i2c1SCL = {PORTB_ID, PIN6_ID, ALTERNATE_MODE, OUTPUT_OPEN_DRAIN, PULL_UP, LOGIC_HIGH, AF4};

/* definition of USART1 I/O module */
USART_STRUCT usart1 = {USART1, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 9600};

/* definition of USART2 I/O module */
USART_STRUCT usart2 = {USART2, UART_ENABLE, UART_8_BIT_WORD, UART_1_STOP_BIT, 38400};

/* definition of I2C1 I/O module */
I2C_config_t i2c1 = {I2C1, I2C_MODE_I2C};

/* variable to hold the user latitude */
float64 userLatitude = 0.0;

/* variable to hold the user longitiude */
float64 userLongitude = 0.0;

/* variable to hold the user direction */
uint8 userDirection = 0.0;


/* function prototype to convert degree to radian */
static float64 toRadians(float64 degree);

/* function prototype to rquest user data */
static void SERVICES_requestToGetUserData(void);

/* function prototype to convert integer to string */
static void SERVICES_convertIntToString(uint8* str, uint16 number);


/*
* description : the function is responsible for initializing the system.
*
* parameters  : NONE.
*
* return value : NONE.
*/
void SERVICES_systemInit(void){
  
  /* configure of pins of USART1 */
  PORT_configurePin(&usart1TX);
  PORT_configurePin(&usart1RX);
  
  /* configure of pins of USART2 */
  PORT_configurePin(&usart2TX);
  PORT_configurePin(&usart2RX);
  
  /* configure of pins of I2C1 */
  PORT_configurePin(&i2c1SCL);
  PORT_configurePin(&i2c1SDA);
  
  /* initialize USART1 */
  UART_init(&usart1);
  
  /* initialize USART2 */
  UART_init(&usart2);
  
  /* initialize I2C1 */
  I2C_init(&i2c1);
  
  /* set the I/O module for the GPS */
  GPS_setInputOutputModule(&usart1);
  
  /* initialize the GPS module */
  GPS_init();
  
  /* set the I/O module for the Bluetooth */
  Bluetooth_setInputOutputModule(&usart2);
  
  /* set the I/O module for the compass sensor */
  //QMC5883l_SetInOutModule(&i2c1);
  
  /* initialize the compass sensor */
  //QMC5883l_Init();
}


/*
* description : the function is responsible for updating user data.
*
* parameters  : NONE.
*
* return value : NONE.
*/
void SERVICES_updateUserData(void){
  
  /* array to hold the user data coming from bluetooth module */ 
  uint8 temp[100];
  
  /* request for user data first */
  SERVICES_requestToGetUserData();
  
  /* receive the user latitude */
  Bluetooth_receiveString(temp);
  
  /* convert the user latitude to float */
  userLatitude = atof((char const *)temp);
  
  /* receive the user longitude */
  Bluetooth_receiveString(temp);
  
  /* convert the user longitude to float */
  userLongitude = atof((char const *)temp);
  
  /* receive the user direction */
  Bluetooth_receiveString(temp);
  
  /* convert the user direction to integer */
  userDirection = temp[0] - '0';
}


/*
* description : the function is responsible for updating trolley data.
*
* parameters  : NONE.
*
* return value : NONE.
*/
void SERVICES_updateTrolleyData(void){
  
  /* update trolly latitude and longitude */
  GPS_updateLatitudeAndLongitude();
  
  /* update trolley direction */
  //QMC5883l_GetAngel();
}


/*
* description : the function is responsible for getting the distance between the user and
the trolley.
*
* parameters  : NONE.
*
* return value : the distance.
*/
float32 SERVICES_getDistance(void){
  float64 dlat = toRadians(latitude) - toRadians(userLatitude);
  float64 dlong = toRadians(longitude) - toRadians(userLongitude);
  
  float64 ans = pow(sin(dlat / 2), 2) + cos(toRadians(userLatitude)) * cos(toRadians(latitude)) * pow(sin(dlong / 2), 2);
  
  ans = 2 * asin(sqrt(ans));
  
  float64 R = 6371;
  
  ans = ans * R * 1000;
  
  return ans;
}


/*
* description : the function is responsible for getting the difference in angle
*               between the user and the trolley.
*
* parameters  : NONE.
*
* return value : the difference in angle.
*/
sint8 SERVICES_getDifferenceInAngle(void){
  sint8 differenceInAngle = compassData.direction - userDirection;
  return differenceInAngle;
}


/*
* description : the function is responsible for sending commands to the avr slave.
*
* parameters  : direction of movement and speed of movement or angle of rotation.
*
* return value : NONE.
*/
uint8 SERVICES_sendCommandToAvrSlave(uint8 direction, uint16 speedOrAngle){
  
  uint8 returnValue = SUCCESS;
  
  /* buffer to hold the data to be sent */
  uint8 dataToBeSent[10];
  
  /* prepare the data to be sent */
  SERVICES_convertIntToString(dataToBeSent, speedOrAngle);
  dataToBeSent[3] = direction;
  dataToBeSent[4] = '\0';
  
  /* sent the data to the AVR slave through I2C module */
  returnValue = I2C_Master_transmitString(&i2c1, (AVR_SLAVE_ADDRESS << 1), dataToBeSent);
  
  return returnValue;
}


/*
* description : the function is responsible for converting degree to radian.
*
* parameters  : degree.
*
* return value : radian.
*/
static float64 toRadians(float64 degree)
{
  float64 one_deg = (M_PI) / 180.0;
  return (one_deg * degree);
}

/*
* description : the function is responsible for requesting user data.
*
* parameters  : NONE.
*
* return value : NONE.
*/
static void SERVICES_requestToGetUserData(void){
  Bluetooth_sendCharacter(REQUEST_TO_GET_USER_DATA_ID);
}


/*
* description : the function is responsible for converting an integer to string.
*
* parameters  : number to be converted and the buffer the hold the string.
*
* return value : NONE.
*/
static void SERVICES_convertIntToString(uint8* str, uint16 number){
  
  /* variable to hold the index to the buffer */
  sint8 i = 2;
  
  /* converting the 3 digit integer to a string */
  while(i >= 0){
    str[i] = (number % 10) + '0';
    number /= 10;
    i--;
  }
}

void SERVICES_decideDirection(uint16 * angleOrSpeed, uint8 * direction){
  sint8 angleBetweenUserAndTrolley = SERVICES_getDifferenceInAngle();
  
  if((angleBetweenUserAndTrolley <= -1) && (angleBetweenUserAndTrolley >= -4)){
    *direction = MOVE_RIGHT;
    *angleOrSpeed = 45 * abs(angleBetweenUserAndTrolley);
  }
  else if (angleBetweenUserAndTrolley < -4){
    *direction = MOVE_LEFT;
    *angleOrSpeed = 45 * (angleBetweenUserAndTrolley + 8);
  }
  else if((angleBetweenUserAndTrolley >= 1) && (angleBetweenUserAndTrolley <= 4)){
    *direction = MOVE_LEFT;
    *angleOrSpeed = 45 * angleBetweenUserAndTrolley;
  }
  else if (angleBetweenUserAndTrolley > 4){
    *direction = MOVE_RIGHT;
    *angleOrSpeed = 45 * (8 - angleBetweenUserAndTrolley);
  }
  else{
    *direction = MOVE_FORWARD;
    *angleOrSpeed = 80;
  }
}


