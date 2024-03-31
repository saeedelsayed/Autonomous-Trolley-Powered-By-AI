/******************************************************************************
 *
 * Module: DC motor module
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the DC motor module
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "gpio.h"
#include "pwm.h"
#include "dc_motor.h"
#include "util/delay.h"
/*
 * description : the function is responsible for initializing the DC motor terminals and
 *               the PWM channel connected to it. it is also responsible for reporting success
 *               or failure of the initialization.                 
 *
 * parameters  : pointer of type dc_motor which holds the DC motor information.
 *
 * return value : the function returns success or failure of the initialization.
 */
uint8 DCmotor_init(dc_motor* dcMotor){
	/* variable that holds success or failure of the initialization */
	uint8 returnValue = SUCCESS;
	
	#if (DCMOTOR_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if(dcMotor == NULL_PTR){
		returnValue = FAIL;
	}
	#endif
	
	/* configure the positive terminal of the DC motor */
	returnValue = returnValue && GPIO_pinConfiguration(dcMotor->positiveTerminal.portId, dcMotor->positiveTerminal.pinId, OUTPUT_PIN,
	LOGIC_LOW,PULL_UP_DEACTIVATION);
	
	/* configure the negative terminal of the DC motor */
	returnValue = returnValue && GPIO_pinConfiguration(dcMotor->negativeTerminal.portId, dcMotor->negativeTerminal.pinId, OUTPUT_PIN,
	LOGIC_LOW,PULL_UP_DEACTIVATION);
	
	/* initialize the PWM channel connected to the DC motor */
	returnValue = returnValue && PWM_init(dcMotor->pwmChannelId);
	
	/* return success or failure of the initialization */
	return returnValue;
}

/*
 * description : the function is responsible for setting the speed of the DC motor. it is also
 *               responsible for reporting success or failure of the operation.              
 *
 * parameters  : pointer of type dc_motor which holds the DC motor information and
 *               speed which hold the required speed to set.
 *
 * return value : the function returns success or failure of the operation.
 */
uint8 DCmotor_setSpeed(dc_motor* dcMotor, uint8 speed){
	/* variable that holds success or failure of the operation */
	uint8 returnValue = SUCCESS;
	
	#if (DCMOTOR_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if(dcMotor == NULL_PTR){
		returnValue = FAIL;
	}
	#endif
	
	/* set the speed by setting the PWM channel duty cycle */
	returnValue = returnValue && PWM_setDutyCycle(dcMotor->pwmChannelId, speed);
	
	/* return success or failure of the operation */
	return returnValue;
}

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
uint8 DCmotor_setSpeedAndDirection(dc_motor* dcMotor, uint8 speed, uint8 direction){
	/* variable that holds success or failure of the operation */
	uint8 returnValue = SUCCESS;
	
	#if (DCMOTOR_REPORTING_ERROR == ON)
	/* checking for any errors in the parameters */
	if(dcMotor == NULL_PTR || (direction != CLOCK_WISE && direction != ANTI_CLOCK_WISE)){
		returnValue = FAIL;
	}
	#endif
	
	/* set the speed by setting the PWM channel duty cycle */
	returnValue = returnValue && DCmotor_setSpeed(dcMotor, speed);
	
	/* setting the direction of the DC motor as clock wise or anti clock wise */
	if(direction == CLOCK_WISE){
		returnValue = returnValue && GPIO_writePin(dcMotor->positiveTerminal.portId, dcMotor->positiveTerminal.pinId,LOGIC_HIGH);
		returnValue = returnValue && GPIO_writePin(dcMotor->negativeTerminal.portId, dcMotor->negativeTerminal.pinId,LOGIC_LOW);
		}else{
		returnValue = returnValue && GPIO_writePin(dcMotor->positiveTerminal.portId, dcMotor->positiveTerminal.pinId,LOGIC_LOW);
		returnValue = returnValue && GPIO_writePin(dcMotor->negativeTerminal.portId, dcMotor->negativeTerminal.pinId,LOGIC_HIGH);
	}
	
	/* return success or failure of the operation */
	return returnValue;
}
uint8 DCmotor_rotate(dc_motor* dcMotor,uint16 degree){
	float64 time = degree*16.66667;
	DCmotor_setSpeedAndDirection(dcMotor, 80, CLOCK_WISE);
	_delay_ms(time);
}
