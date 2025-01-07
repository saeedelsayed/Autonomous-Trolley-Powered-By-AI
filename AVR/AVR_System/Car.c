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


static car_dataType carData = {
		{{PORTC_ID, PIN2_ID}, {PORTC_ID, PIN3_ID}, 0, PWM_CHANNEL0_ID},
		{{PORTC_ID, PIN4_ID}, {PORTC_ID, PIN5_ID}, 1, PWM_CHANNEL1_ID},
		{0,0,0,0},
		0,
		0,
		0
};
void Car_init(void){
	DCmotor_init(&carData.rightMotor);
	DCmotor_init(&carData.leftMotor);
}

Car_frameStateType Car_isValidFrame(uint8 * frame){
	if ((frame[0] >= '0' && frame[0] <= '9') && (frame[1] >= '0'&& frame[1] <= '9') && (frame[2] >= '0' && frame[2] <= '9')){
		if((frame[3]=='F')||(frame[3]=='R')||frame[3]=='L'){
			return CAR_VALID_FRAME;
		}
	}
	return CAR_INVALID_FRAME;
}
void Car_setFrame(uint8 * frame){
	for(uint8 i =0 ;i<4;i++){
		carData.frame[i]=frame[i];
	}
}
void Car_setDirection(void){
carData.carDirection = carData.frame[3];
}
void Car_moveForward(void){
	DCmotor_setSpeed(&carData.rightMotor,carData.carSpeed);
	DCmotor_setSpeed(&carData.leftMotor,carData.carSpeed);
}
void car_rotateRight(void){
	DCmotor_setSpeed(&carData.rightMotor, 0);
	DCmotor_rotate(&carData.leftMotor, carData.carAngle);
}
void car_rotateLeft(void){
	DCmotor_setSpeed(&carData.leftMotor, 0);
	DCmotor_rotate(&carData.rightMotor, carData.carAngle);
}
void Car_setSpeed(void){
	uint8 speed = (carData.frame[0] - '0') * 100 + (carData.frame[1] - '0') * 10 + (carData.frame[2] - '0');
	if (speed>100){
		speed = 100;
	}
	carData.carSpeed= speed;
}

void Car_setAngel(void){
	carData.carAngle= (carData.frame[0] - '0') * 100 + (carData.frame[1] - '0') * 10 + (carData.frame[2] - '0');
}
void Car_stopMoving(void){
	DCmotor_setSpeed(&carData.rightMotor,0);
	DCmotor_setSpeed(&carData.leftMotor,0);
}
void Car_go(uint8 * frame){
	Car_frameStateType state =Car_isValidFrame(frame);
	if(state==CAR_VALID_FRAME){
		Car_setFrame(frame);
		Car_setDirection();
		if(carData.carDirection == 'F'){
			Car_setSpeed();
			Car_moveForward();
		}
		else if(carData.carDirection == 'R'){
			Car_setAngel();
			car_rotateRight();
		}
		else{
			Car_setAngel();
			car_rotateLeft();
		}
	}

}


