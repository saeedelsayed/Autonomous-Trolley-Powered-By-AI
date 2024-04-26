/*
 * Data.c
 *
 *  Created on: Dec 24, 2023
 *      Author: abram
 */

#include "dc_motor.h"
#include "pwm.h"
#include "gpio.h"
#include "std_types.h"
#include "Car.h"
#include "util/delay.h"

static car_dataType carData = {
	{{PORTC_ID, PIN5_ID}, {PORTC_ID, PIN4_ID}, 0, PWM_CHANNEL0_ID},
	{{PORTC_ID, PIN3_ID}, {PORTC_ID, PIN2_ID}, 1, PWM_CHANNEL1_ID},
	{{PORTA_ID, PIN1_ID}, {PORTA_ID, PIN2_ID}, 2, PWM_CHANNEL2_ID},
	{{PORTA_ID, PIN3_ID}, {PORTA_ID, PIN4_ID}, 3, PWM_CHANNEL3_ID},
	{0, 0, 0, 0},
	45,
	70,
	0};
void Car_init(void)
{
	DCmotor_init(&(carData.rightFrontMotor));
	DCmotor_init(&(carData.leftFrontMotor));
	DCmotor_init(&(carData.rightBackMotor));
	DCmotor_init(&(carData.leftBackMotor));
	DCmotor_setSpeedAndDirection(&(carData.rightFrontMotor), 0, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&(carData.leftFrontMotor), 0, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&(carData.rightBackMotor), 0, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&(carData.leftBackMotor), 0, CLOCK_WISE);
}

Car_frameStateType Car_isValidFrame(uint8 *frame)
{
	if ((frame[0] >= '0' && frame[0] <= '9') && (frame[1] >= '0' && frame[1] <= '9') && (frame[2] >= '0' && frame[2] <= '9'))
	{
		if ((frame[3] == 'F') || (frame[3] == 'R') || frame[3] == 'L' || frame[3] == 'B')
		{
			return CAR_VALID_FRAME;
		}
	}
	return CAR_INVALID_FRAME;
}
void Car_setFrame(uint8 *frame)
{
	for (uint8 i = 0; i < 4; i++)
	{
		carData.frame[i] = frame[i];
	}
}
void Car_setDirection(void)
{
	carData.carDirection = carData.frame[3];
}
void Car_moveForward(void)
{
	DCmotor_setSpeedAndDirection(&carData.rightFrontMotor, carData.carSpeed, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftFrontMotor, carData.carSpeed, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.rightBackMotor, carData.carSpeed, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftBackMotor, carData.carSpeed, CLOCK_WISE);
}
void Car_MoveBack(void)
{
	Car_stopMoving();
	_delay_ms(500);
	DCmotor_setSpeedAndDirection(&carData.rightFrontMotor, carData.carSpeed, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftFrontMotor, carData.carSpeed, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.rightBackMotor, carData.carSpeed, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftBackMotor, carData.carSpeed, ANTI_CLOCK_WISE);
	_delay_ms(800);
	Car_stopMoving();
}

void Car_rotateRight(void)
{
	Car_stopMoving();
	_delay_ms(500);
	DCmotor_setSpeedAndDirection(&carData.rightFrontMotor, 100, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftFrontMotor, 100, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.rightBackMotor,100, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftBackMotor, 100, CLOCK_WISE);
	float64 time = carData.carAngle * 20;
	_delay_ms(time);
	Car_stopMoving();
}
void Car_rotateLeft(void)
{
	Car_stopMoving();
	_delay_ms(500);
	DCmotor_setSpeedAndDirection(&carData.rightFrontMotor,100, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftFrontMotor, 100, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.rightBackMotor, 100, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&carData.leftBackMotor, 100, ANTI_CLOCK_WISE);
	float64 time = carData.carAngle * 20;
	_delay_ms(time);
	Car_stopMoving();
}
void Car_setSpeed(void)
{
	uint8 speed = (carData.frame[0] - '0') * 100 + (carData.frame[1] - '0') * 10 + (carData.frame[2] - '0');
	if (speed > 100)
	{
		speed = 100;
	}
	carData.carSpeed = speed;
}

void Car_setAngel(void)
{
	carData.carAngle = (carData.frame[0] - '0') * 100 + (carData.frame[1] - '0') * 10 + (carData.frame[2] - '0');
}
void Car_stopMoving(void)
{
	DCmotor_setSpeed(&carData.rightFrontMotor, 0);
	DCmotor_setSpeed(&carData.leftFrontMotor, 0);
	DCmotor_setSpeed(&carData.rightBackMotor, 0);
	DCmotor_setSpeed(&carData.leftBackMotor, 0);
}

void Car_calibration(uint16 time)
{
	DCmotor_setSpeedAndDirection(&(carData.rightFrontMotor), 100, CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&(carData.leftFrontMotor), 100, ANTI_CLOCK_WISE);
	_delay_ms(time);
	Car_moveForward();
	_delay_ms(1000);
	DCmotor_setSpeedAndDirection(&(carData.rightFrontMotor), 100, ANTI_CLOCK_WISE);
	DCmotor_setSpeedAndDirection(&(carData.leftFrontMotor), 100, CLOCK_WISE);
	_delay_ms(time);
	Car_stopMoving();
}

void Car_go(uint8 *frame)
{
	Car_frameStateType state = Car_isValidFrame(frame);
	if (state == CAR_VALID_FRAME)
	{
		Car_setFrame(frame);
		Car_setDirection();
		if (carData.carDirection == 'F')
		{
			Car_setSpeed();
			Car_moveForward();
		}
		else if (carData.carDirection == 'B')
		{
			Car_MoveBack();
		}
		else if (carData.carDirection == 'R')
		{
			Car_setAngel();
			Car_rotateRight();
		}
		else
		{
			Car_setAngel();
			Car_rotateLeft();
		}
	}
}
