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
#include "ExtInterrupt.h"
#include "Car.h"

uint8 command[4] = {0};

void INT0_Handeller(void){
 Car_stopMoving();

}
int main(void)
{
	Car_init();
	I2c_Slave_Init(0x0F);
	ExtInterrupt_Init();
	ExtInterrupt_EnableNotification(EXT_INTERRUPT_INT0,INT0_Handeller);
	Gie_Enable();
	GPIO_pinConfiguration(PORTA_ID,PIN0_ID, OUTPUT_PIN, LOGIC_HIGH,  PULL_UP_DEACTIVATION);
	GPIO_pinConfiguration(PORTA_ID,PIN1_ID, OUTPUT_PIN, LOGIC_HIGH,  PULL_UP_DEACTIVATION);

	while (1)
	{

		I2c_Slave_Receive(command, 4);
		Car_go(command);

//		if ((command[0] >= '0' && command[0] <= '9') && (command[1] >= '0'&& command[1] <= '9') && (command[2] >= '0' && command[2] <= '9'))
//		{
//			if (command[3] == 'F')
//			{
//				GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
//				GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
//				speed = (command[0] - '0') * 100 + (command[1] - '0') * 10 + (command[2] - '0');
//				DCmotor_setSpeed(&rightDcMotor, speed);
//			}
//			else
//			{
//				angel = (command[0] - '0') * 100 + (command[1] - '0') * 10 + (command[2] - '0');
//				if (command[3] == 'R')
//				{
//					GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
//					DCmotor_setSpeed(&rightDcMotor, 0);
//					DCmotor_rotate(&leftDcMotor, angel);
//				}
//				else
//				{
//					GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
//					DCmotor_setSpeed(&leftDcMotor, 0);
//					DCmotor_rotate(&rightDcMotor, angel);
//				}
//			}
//		}
		
	}
}
