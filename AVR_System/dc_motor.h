/******************************************************************************
 *
 * Module: DC motor module
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the DC motor module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Declarations                                 *
 *******************************************************************************/

/* structure to represent the motor terminals */
typedef struct{
	/* terminal port */
	uint8 portId;
	
	/* terminal pin */
	uint8 pinId;
}terminal;

/* structure to represent the DC motor modules */
typedef struct{
	/* positive terminal of the motor */
	terminal positiveTerminal;
	
	/* negative terminal of the motor */
	terminal negativeTerminal;
	
	/* DC motor id */
	uint8 dcMotorId;
	
	/* PWM channel connected to the DC motor */
	uint8 pwmChannelId;
}dc_motor;


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* definition for the motor direction */
#define CLOCK_WISE      0x00
#define ANTI_CLOCK_WISE 0x01

/* reporting Error enable */
#define DCMOTOR_REPORTING_ERROR OFF

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * description : the function is responsible for initializing the DC motor terminals and
 *               the PWM channel connected to it. it is also responsible for reporting success
 *               or failure of the initialization.                 
 *
 * parameters  : pointer of type dc_motor which holds the DC motor information.
 *
 * return value : the function returns success or failure of the initialization.
 */
uint8 DCmotor_init(dc_motor* dcMotor);

/*
 * description : the function is responsible for setting the speed of the DC motor. it is also
 *               responsible for reporting success or failure of the operation.              
 *
 * parameters  : pointer of type dc_motor which holds the DC motor information and
 *               speed which hold the required speed to set.
 *
 * return value : the function returns success or failure of the operation.
 */
uint8 DCmotor_setSpeed(dc_motor* dcMotor, uint8 speed);

/*
 * description : the function is responsible for setting the speed of the DC motor and 
 *               direction at once. it is also responsible for reporting success or failure
 *               of the operation.             
 *
 * parameters  : pointer of type dc_motor which holds the DC motor information,
 *               speed which holds the required speed to set, direction which hold the required
 *               direction
 *
 * return value : the function returns success or failure of the operation.
 */
uint8 DCmotor_setSpeedAndDirection(dc_motor* dcMotor, uint8 speed, uint8 direction);

uint8 DCmotor_rotate(dc_motor* dcMotor,uint16 degree);

#endif /* DC_MOTOR_H_ */
