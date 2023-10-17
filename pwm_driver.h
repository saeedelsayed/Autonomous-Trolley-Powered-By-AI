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
#include "gpio.h"

/*******************************************************************************************/
/************************************ TOP MACROS ***********************************************/
/*******************************************************************************************/
#define PWM_CHANNEL_ID0_TOP 0xff
#define PWM_CHANNEL_ID1_TOP 0xff
#define PWM_CHANNEL_ID2_TOP 0xff
#define PWM_CHANNEL_ID3_TOP 0xff

/*******************************************************************************************/
/************************************ PWM Channels *****************************************/
/*******************************************************************************************/
#define PWM_CHANNEL_ID0 0x00
#define PWM_CHANNEL_ID1 0x01
#define PWM_CHANNEL_ID2 0x02
#define PWM_CHANNEL_ID3 0x03

/*******************************************************************************************/
/************************************ Duty Cycle Range *************************************/
/*******************************************************************************************/
#define PWM_DUTY_CYCLE_MIN 0x00
#define PWM_DUTY_CYCLE_MAX 0x64

/*******************************************************************************************/
/*********************************** Timer0 Registers **************************************/
/*******************************************************************************************/
#define TCNT0 (*((volatile uint8 *)0x52))
#define OCR0 (*((volatile uint8 *)0x5C))

#define TCCR0 (*((volatile uint8 *)0x53))
#define FOC0 7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02 2
#define CS01 1
#define CS00 0

/*******************************************************************************************/
/*********************************** Timer1 Registers **************************************/
/*******************************************************************************************/
#define ICR1 (*((volatile uint16 *)0x46))
#define ICR1L (*((volatile uint8 *)0x46))
#define ICR1H (*((volatile uint8 *)0x47))

#define OCR1B (*((volatile uint16 *)0x48))
#define OCR1BL (*((volatile uint8 *)0x48))
#define OCR1BH (*((volatile uint8 *)0x49))

#define OCR1A (*((volatile uint16 *)0x4A))
#define OCR1AL (*((volatile uint8 *)0x4A))
#define OCR1AH (*((volatile uint8 *)0x4B))

#define TCNT1 (*((volatile uint16 *)0x4C))
#define TCNT1L (*((volatile uint8 *)0x4C))
#define TCNT1H (*((volatile uint8 *)0x4D))

#define TCCR1B (*((volatile uint8 *)0x4E))
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#define TCCR1A (*((volatile uint8 *)0x4F))
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A 3
#define FOC1B 2
#define WGM11 1
#define WGM10 0


/*******************************************************************************************/
/************************************ Timer2 Registers *************************************/
/*******************************************************************************************/
#define OCR2 (*((volatile uint8 *)0x43))
#define TCNT2 (*((volatile uint8 *)0x44))

#define TCCR2 (*((volatile uint8 *)0x45))
#define FOC2 7
#define WGM20 6
#define COM21 5
#define COM20 4
#define WGM21 3
#define CS22 2
#define CS21 1
#define CS20 0


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
