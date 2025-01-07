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
#include <avr/io.h>
#include "Usart.h"

volatile uint8 command[4] = { 0 };
volatile uint8 obstaclesFlag = 0;


void INT0_Handeller(void) {
	Car_stopMoving();
}

void INT1_Handeller(void) {
	obstaclesFlag = 1;
}

int main(void) {
	ExtInterrupt_Init();
//	Usart_Init();
	Car_init();
	I2c_Slave_Init(0x0F);
	ExtInterrupt_EnableNotification(EXT_INTERRUPT_INT0, INT0_Handeller);
//	ExtInterrupt_EnableNotification(EXT_INTERRUPT_INT1, INT1_Handeller);
	Gie_Enable();
	PORTC |= (1 << 0) | (1 << 1);

//	uint8 var1  = 0;
//	uint8 var2  = 0;
//	uint8 var3  = 0;
//	GPIO_pinConfiguration(PORTB_ID,PIN5_ID,INPUT_PIN,LOGIC_HIGH ,PULL_UP_DEACTIVATION);
//	GPIO_pinConfiguration(PORTB_ID,PIN6_ID,INPUT_PIN,LOGIC_HIGH ,PULL_UP_DEACTIVATION);
//	GPIO_pinConfiguration(PORTB_ID,PIN7_ID,INPUT_PIN,LOGIC_HIGH ,PULL_UP_DEACTIVATION);

	while (1)
	{
//		command[0]= '0';
//		command[1]= '8';
//		command[2]= '0';
//		command[3]= 'F';

		I2c_Slave_Receive(command, 4);
		Car_go(command);


}
}

int main3(void) {
	Car_init();
//	Car_moveForward();
	Car_rotateRight();
	_delay_ms(1000);
	Car_rotateLeft();
	_delay_ms(1000);
	Car_MoveBack();
	while (1) {
	};
	//	Car_calibration(900);
}

// int main(void){
//	Car_init();
//	Car_moveForward();
// }




// arduino i2c

//			obticalFlag = 0;

//		if ((command[0] >= '0' && command[0] <= '9') && (command[1] >= '0'&& command[1] <= '9') && (command[2] >= '0' && command[2] <= '9'))
//		{
//			if (command[3] == 'F')
//			{
//				GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
//				GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
////				speed = (command[0] - '0') * 100 + (command[1] - '0') * 10 + (command[2] - '0');
////				DCmotor_setSpeed(&rightDcMotor, speed);
//			}
//			else
//			{
////				angel = (command[0] - '0') * 100 + (command[1] - '0') * 10 + (command[2] - '0');
//				if (command[3] == 'R')
//				{
//					GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
//					GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_HIGH);
////					DCmotor_setSpeed(&rightDcMotor, 0);
////					DCmotor_rotate(&leftDcMotor, angel);
//				}
//				else
//				{
//					GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
//					GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);
////					DCmotor_setSpeed(&leftDcMotor, 0);
////					DCmotor_rotate(&rightDcMotor, angel);
//				}
//			}
//		}



//
//
//if (obstaclesFlag == 0)
//		{
//			// esp uart
//			for (uint8 i = 0; i < 4; i++)
//			{
//				command[i] = Usart_Receive();
//				GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
//			}
//
////				Car_go(command);
//						if ((command[0] >= '0' && command[0] <= '9') && (command[1] >= '0'&& command[1] <= '9') && (command[2] >= '0' && command[2] <= '9'))
//						{
//							if (command[3] == 'F')
//							{
//								GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_LOW);
//								GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
//								_delay_ms(1000);
//							}
//							else if (command[3] == 'R')
//								{
//									GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_LOW);
//									GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_HIGH);
//									_delay_ms(1000);
//
//								}
//								else
//								{
//									GPIO_writePin(PORTC_ID, PIN1_ID, LOGIC_LOW);
//									GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);
//									_delay_ms(1000);
//				//
//								}
//							}
//
//
//		}



//		Car_go(command);
//		GPIO_readPin(PORTB_ID,PIN5_ID,&var1);
//		GPIO_readPin(PORTB_ID,PIN6_ID,&var2);
//		GPIO_readPin(PORTB_ID,PIN7_ID,&var3);
//
//		if(var1== 0 && var2 == 0 && var3 ==0)
//		{

//
//		}
//		else if (var1== 1 && var2 == 0 && var3 ==0)
//		{
//			command[0]= '1';
//						command[1]= '8';
//						command[2]= '0';
//						command[3]= 'R';
//		}
//		else if (var1==0  && var2 == 1 && var3 ==0)
//		{
//			command[0]= '1';
//									command[1]= '8';
//									command[2]= '0';
//									command[3]= 'L';
//
//		}
//		else if (var1==1  && var2 == 1 && var3 ==0)
//		{
//			command[0]= '0';
//			command[1]= '8';
//			command[2]= '0';
//			command[3]= 'F';
//
//		}
//		Car_go(command);
//		command[0]= '1';
//		command[1]= '8';
//		command[2]= '0';
//		command[3]= 'L';
//		Car_go(command);
//		command[0]= '1';
//		command[1]= '8';
//		command[2]= '0';
//		command[3]= 'R';
//		Car_go(command);


//	}
//		else {
////			I2c_Slave_Receive(command, 4);
////			Car_go(command);
//
//		}
