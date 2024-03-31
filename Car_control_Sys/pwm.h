/**
 * @file pwm_driver.h
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief pwm_driver header file
 * @date 16-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PWM_DRIVER_H
#define	PWM_DRIVER_H

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/
#include "std_types.h"

/*******************************************************************************************/
/************************************ TOP MACROS ***********************************************/
/*******************************************************************************************/
#define PWM_CHANNEL0_TOP 0xff
#define PWM_CHANNEL1_TOP 0xff
#define PWM_CHANNEL2_TOP 0xff
#define PWM_CHANNEL3_TOP 0xff

/*******************************************************************************************/
/************************************ PWM Channels *****************************************/
/*******************************************************************************************/
#define PWM_CHANNEL0_ID 0x00
#define PWM_CHANNEL1_ID 0x01
#define PWM_CHANNEL2_ID 0x02
#define PWM_CHANNEL3_ID 0x03

#define PWM_CHANNEL0_PORT PORTB_ID
#define PWM_CHANNEL0_PIN  PIN3_ID

#define PWM_CHANNEL1_PORT PORTD_ID
#define PWM_CHANNEL1_PIN  PIN5_ID

#define PWM_CHANNEL2_PORT PORTD_ID
#define PWM_CHANNEL2_PIN  PIN4_ID

#define PWM_CHANNEL3_PORT PORTD_ID
#define PWM_CHANNEL3_PIN  PIN7_ID

/*******************************************************************************************/
/************************************ Duty Cycle Range *************************************/
/*******************************************************************************************/
#define PWM_DUTY_CYCLE_MIN 0x00
#define PWM_DUTY_CYCLE_MAX 0x64

/*******************************************************************************************/
/************************************ reporting error enable *******************************/
/*******************************************************************************************/
#define PWM_REPORTING_ERROR OFF

/*******************************************************************************************/
/************************************ Function Prototypes **********************************/
/*******************************************************************************************/

/*
 * description : Initializes internal variables
 *               and the PWM unit of the micro controller.
 *               This function must be called before calling
 *               any other function of the PWM module.
 * 
 * parameters  : PWM Channel Id
 *
 * return value: SUCCESS or FAIL
 */
uint8 PWM_init(const uint8 Channel_Id);

/*
 * description : This service sets the duty cycle for a channel
 *               of the PWM module.
 *               The function PWM_init() must be called before
 *               calling this function.
 *               The duty cycle is represented by a number between
 *               0 and 100.
 * 
 * parameters  : PWM Channel Id and PWM Duty Cycle
 *
 * return value: SUCCESS or FAIL
 */
uint8 PWM_setDutyCycle(const uint8 Channel_Id, const uint8 DutyCycle);

#endif	/* PWM_DRIVER_H */
