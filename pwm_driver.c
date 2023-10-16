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

#include "pwm_driver.h"

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
    if (Channel_Id > 4 || Channel_Id < 1)
    {
        return FAIL;
    }
    // Set the TCNT0 Register Initial Value to 0
    TCNT0 = 0x00;
    // Set the OCR0 Register Initial Value to 255
    OCR0 = 0xff;
    // Set the PWM Channel Id
    switch (Channel_Id)
    {
    case ID0: // Timer 0

        // Clear the Timer Mode Bits
        TCCR0 &= ~(72 << WGM00);                                       
        // Set the Timer Mode to Fast PWM
        TCCR0 |= (72 << WGM00);                                        

        // Clear the Compare Output Mode Bits
        TCCR0 &= ~(48 << COM01);                                      
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR0 |= (1 << COM01);

        // Clear the Pre-scaler Bits
        TCCR0 &= ~(7 << CS02);                                       
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR0 |= (1 << CS00);                                       

        break;

    case ID1A: // Timer 1 Channel A

        // Clear the Timer Mode Bits                                 
        TCCR1A &= ~(3 << WGM11);                                     
        // Set the Timer Mode to Fast PWM                                 
        TCCR1A |= (3 << WGM11);                                     

        // Clear the Compare Output Mode Bits
        TCCR1A &= ~(192 << COM1A1);                                    
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR1A |= (1 << COM1A1);                                     

        // Clear the Pre-scaler Bits
        TCCR1B &= ~(7 << CS12);                                     
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR1B |= (1<<CS10);                                      

        break;

    case ID1B: // Timer 1 Channel B

        // Clear the Timer Mode Bits
        TCCR1B &= ~(24 << WGM13);                                     
        // Set the Timer Mode to Fast PWM
        TCCR1B |= (24 << WGM13);                                   

        // Clear the Compare Output Mode Bits
        TCCR1A &= ~(48 << COM1B1);                                    
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR1A |= (1<<COM1B1);

        // Clear the Pre-scaler Bits
        TCCR1B &= ~(7 << CS12);
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR1B |= (1<<CS10);                                       

        break;

    case ID2: // Timer 2

        // Clear the Timer Mode Bits
        TCCR2 &= ~(27 << WGM20);                                    
        // Set the Timer Mode to Fast PWM
        TCCR2 |= (72 << WGM20);                                     

        // Clear the Compare Output Mode Bits
        TCCR2 &= ~(48 << COM21);                                    
        // Set the Compare Output Mode to Non-Inverting Mode
        TCCR2 |= (1 << COM21);                                     

        // Clear the Pre-scaler Bits
        TCCR2 &= ~(7 << CS22);                                    
        // Set the Pre-scaler to 1 (No Pre-scaling)
        TCCR2 |= (1 << CS20);                                     

        break;      
    
    default:
        break;
    }

    return SUCCESS;
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
    if (DutyCycle > 100 || DutyCycle < 0)
    {
        return FAIL;
    }
    
    // Set the PWM Channel Id
    switch (Channel_Id)
    {
    case ID0: // Timer 0
        // Set the OCR0 Register Value
        OCR0 = DutyCycle;
        break;

    case ID1A: // Timer 1 Channel A
        // Set the OCR1A Register Value
        OCR1A = DutyCycle;
        break;
    case ID1B: // Timer 1 Channel B
        // Set the OCR1B Register Value
        OCR1B = DutyCycle;
        break;

    case ID2: // Timer 2
        // Set the OCR2 Register Value
        OCR2 = DutyCycle;
        break;  
    
    default:
        break;
    }

    return SUCCESS;

}