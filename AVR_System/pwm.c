/**
 * @file pwm_driver.c
 * @author Ahmed Radwan (ahmedradwan01126239771@gmail.com)
 * @brief pwm_driver source file
 * @date 16-10-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************************/
/************************************ Includes *********************************************/
/*******************************************************************************************/

#include "gpio.h"
#include "pwm_registers.h"
#include "pwm.h"


/*******************************************************************************************/
/************************************ Functions ********************************************/
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
uint8 PWM_init(const uint8 Channel_Id)
{
	uint8 returnValue = SUCCESS;
	
	#if (PWM_REPORTING_ERROR == ON)
    if (Channel_Id > PWM_CHANNEL3_ID)
    {
        returnValue = FAIL;
    }
	#endif
    
    // Set the PWM Channel Id
    switch (Channel_Id)
    {
    case PWM_CHANNEL0_ID: // Timer 0
        // Set the TCNT0 Register Initial Value to 0
        TCNT0 = 0x00;
        // Set the OCR0 Register Initial Value to 255
        OCR0 = PWM_CHANNEL0_TOP;

        // Clear the Timer Mode Bits
        TCCR0 &= ~(0x01 << WGM00);
        TCCR0 &= ~(0x01 << WGM01);                                   
        // Set the Timer Mode to Fast PWM
        TCCR0 |= (0x01 << WGM00);
        TCCR0 |= (0x01 << WGM01);

        // Clear the Compare Output Mode Bits
        TCCR0 &= ~(0x03 << COM00);                                      
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR0 |= (0x01 << COM01);

        // Clear the Pre-scaler Bits
        TCCR0 &= ~(0x07 << CS00);                                       
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR0 |= (0x01 << CS00); 
		
		// Set the PWM Channel Pin as Output Pin
		returnValue = returnValue && GPIO_pinConfiguration(PWM_CHANNEL0_PORT, PWM_CHANNEL0_PIN, OUTPUT_PIN, LOGIC_LOW, PULL_UP_DEACTIVATION);                                      

        break;

    case PWM_CHANNEL1_ID: // Timer 1 Channel A
        // Set the TCNT1 Register Initial Value to 0
        TCNT1 = 0x00;
        // Set the OCR1A Register Initial Value to 255
        OCR1A = PWM_CHANNEL1_TOP;

        // Clear the Timer Mode Bits                                 
        TCCR1A &= ~(0x03 << WGM10);
        TCCR1B &= ~(0x03 << WGM12);                                     
        // Set the Timer Mode to Fast PWM                                 
        TCCR1A |= (0x01 << WGM11);
        TCCR1B |= (0x03 << WGM12);
        // Set the ICR1 Register Value to TOP Value (0xff)
        ICR1 = PWM_CHANNEL1_TOP;

        // Clear the Compare Output Mode Bits
        TCCR1A &= ~(0x03 << COM1A0);                                    
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR1A |= (0x01 << COM1A1);                                     

        // Clear the Pre-scaler Bits
        TCCR1B &= ~(0x07 << CS10);                                     
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR1B |= (0x01 << CS10); 
		
		// Set the PWM Channel Pin as Output Pin
		returnValue = returnValue && GPIO_pinConfiguration(PWM_CHANNEL1_PORT, PWM_CHANNEL1_PIN, OUTPUT_PIN, LOGIC_LOW, PULL_UP_DEACTIVATION);                                     

        break;

    case PWM_CHANNEL2_ID: // Timer 1 Channel B
        // Set the TCNT1 Register Initial Value to 0
        TCNT1 = 0x00;
        // Set the OCR1B Register Initial Value to 255
        OCR1B = PWM_CHANNEL2_TOP;

        // Clear the Timer Mode Bits
        TCCR1A &= ~(0x03 << WGM10);
        TCCR1B &= ~(0x03 << WGM12);
        // Set the Timer Mode to Fast PWM
        TCCR1A |= (0x01 << WGM11);
        TCCR1B |= (0x03 << WGM12);
        // Set the ICR1 Register Value to TOP Value (0xff)
        ICR1 = PWM_CHANNEL2_TOP;

        // Clear the Compare Output Mode Bits
        TCCR1A &= ~(0x03 << COM1B0);                                    
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR1A |= (0x01 << COM1B1);

        // Clear the Pre-scaler Bits
        TCCR1B &= ~(0x07 << CS10);
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR1B |= (0x01 << CS10);    
		
		// Set the PWM Channel Pin as Output Pin
		returnValue = returnValue && GPIO_pinConfiguration(PWM_CHANNEL2_PORT, PWM_CHANNEL2_PIN, OUTPUT_PIN, LOGIC_LOW, PULL_UP_DEACTIVATION);                                   

        break;

    case PWM_CHANNEL3_ID: // Timer 2
        // Set the TCNT2 Register Initial Value to 0
        TCNT2 = 0x00;
        // Set the OCR2 Register Initial Value to 255
        OCR2 = PWM_CHANNEL3_TOP;

        // Clear the Timer Mode Bits
        TCCR2 &= ~(0x01 << WGM20);
        TCCR2 &= ~(0x01 << WGM21);
        // Set the Timer Mode to Fast PWM
        TCCR2 |= (0x01 << WGM20);
        TCCR2 |= (0x01 << WGM21);

        // Clear the Compare Output Mode Bits
        TCCR2 &= ~(0x03 << COM20);
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR2 |= (0x01 << COM21);

        // Clear the Pre-scaler Bits
        TCCR2 &= ~(0x07 << CS20);
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR2 |= (0x01 << CS20);
		
		// Set the PWM Channel Pin as Output Pin
		returnValue = returnValue && GPIO_pinConfiguration(PWM_CHANNEL3_PORT, PWM_CHANNEL3_PIN, OUTPUT_PIN, LOGIC_LOW, PULL_UP_DEACTIVATION);

        break;      
    
    default:
        break;
    }

    return returnValue;
}

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
uint8 PWM_setDutyCycle(const uint8 Channel_Id, const uint8 DutyCycle)
{
	#if (PWM_REPORTING_ERROR == ON)
    if (DutyCycle > PWM_DUTY_CYCLE_MAX || Channel_Id > PWM_CHANNEL3_ID)
    {
        return FAIL;
    } 
	#endif
	
    // Set the Top Value of the PWM Channel
    uint8 top = 0x00;
    switch (Channel_Id)
    {
    case PWM_CHANNEL0_ID:
        top = PWM_CHANNEL0_TOP;
        break;

    case PWM_CHANNEL1_ID:
        top = PWM_CHANNEL1_TOP;
        break;

    case PWM_CHANNEL2_ID:
        top = PWM_CHANNEL2_TOP;
        break;

    case PWM_CHANNEL3_ID:   
        top = PWM_CHANNEL3_TOP;
        break;

    default:
        break;
    }

    // Set the PWM Channel Id
    switch (Channel_Id)
    {
    case PWM_CHANNEL0_ID: // Timer 0
        // Set the OCR0 Register Value
        OCR0 = (((uint32)top) * DutyCycle) / PWM_DUTY_CYCLE_MAX;
        break;

    case PWM_CHANNEL1_ID: // Timer 1 Channel A
        // Set the OCR1A Register Value
        OCR1A = (((uint32)top) * DutyCycle) / PWM_DUTY_CYCLE_MAX;
        break;
    case PWM_CHANNEL2_ID: // Timer 1 Channel B
        // Set the OCR1B Register Value
        OCR1B = (((uint32)top) * DutyCycle) / PWM_DUTY_CYCLE_MAX;
        break;

    case PWM_CHANNEL3_ID: // Timer 2
        // Set the OCR2 Register Value
        OCR2 = (((uint32)top) * DutyCycle) / PWM_DUTY_CYCLE_MAX;
        break;  
    
    default:
        break;
    }

    return SUCCESS;

}