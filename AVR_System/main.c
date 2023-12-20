/*
 * AVR_System.c
 *
 * Created: 12/9/2023 1:38:05 PM
 * Author : Abdelrahman Saeed
 */

#include "dc_motor.h"
#include "pwm.h"
#include "gpio.h"
#include "util/delay.h"
#include "I2c.h"

dc_motor rightDcMotor = {{PORTC_ID, PIN0_ID}, {PORTC_ID, PIN1_ID}, 0, PWM_CHANNEL0_ID};
dc_motor leftDcMotor = {{PORTC_ID, PIN4_ID}, {PORTC_ID, PIN5_ID}, 1, PWM_CHANNEL1_ID};
uint8 Commad[4] = {0};
uint8 speed = 0;
uint16 angel = 0;
int main(void)
{
	DCmotor_init(&rightDcMotor);
	DCmotor_init(&leftDcMotor);
	I2c_Slave_Init(0x0F);
	GPIO_pinConfiguration(PORTA_ID,PIN0_ID, OUTPUT_PIN, LOGIC_HIGH,  PULL_UP_DEACTIVATION);
	GPIO_pinConfiguration(PORTA_ID,PIN1_ID, OUTPUT_PIN, LOGIC_HIGH,  PULL_UP_DEACTIVATION);
	

	while (1)
	{
		GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_HIGH);
		I2c_Slave_Receive(Commad, 4);
		if ((Commad[0] >= '0' && Commad[0] <= '9') && (Commad[1] >= '0'&& Commad[1] <= '9') && (Commad[2] >= '0' && Commad[2] <= '9'))
		{
			if (Commad[3] == 'F')
			{
				GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
				GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
				speed = (Commad[0] - '0') * 100 + (Commad[1] - '0') * 10 + (Commad[2] - '0');
				DCmotor_setSpeed(&rightDcMotor, speed);
			}
			else
			{
				angel = (Commad[0] - '0') * 100 + (Commad[1] - '0') * 10 + (Commad[2] - '0');
				if (Commad[3] == 'R')
				{
					GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
					DCmotor_setSpeed(&rightDcMotor, 0);
					DCmotor_rotate(&leftDcMotor, angel);
				}
				else
				{	
					GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
					DCmotor_setSpeed(&leftDcMotor, 0);
					DCmotor_rotate(&rightDcMotor, angel);
				}
			}
		}
		
	}
}
