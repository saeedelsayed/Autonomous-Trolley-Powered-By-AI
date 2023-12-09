/*
 * AVR_System.c
 *
 * Created: 12/9/2023 1:38:05 PM
 * Author : Abdelrahman Saeed
 */ 

#include "dc_motor.h"
#include "pwm.h"
#include "gpio.h"

int main(void)
{
	
	dc_motor dcMotorOne = {{PORTC_ID,PIN0_ID}, {PORTC_ID,PIN1_ID}, 0, PWM_CHANNEL0_ID};
	dc_motor dcMotorTwo = {{PORTD_ID,PIN0_ID}, {PORTD_ID,PIN1_ID}, 1, PWM_CHANNEL1_ID};
	
	
	DCmotor_init(&dcMotorOne);
	DCmotor_setSpeedAndDirection(&dcMotorOne, 100, CLOCK_WISE);
	
	DCmotor_init(&dcMotorTwo);
	DCmotor_setSpeedAndDirection(&dcMotorTwo, 100, CLOCK_WISE);
	
    while (1) 
    {
    }
}

