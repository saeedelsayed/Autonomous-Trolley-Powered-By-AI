/*
 * Data.h
 *
 *  Created on: Dec 24, 2023
 *      Author: abram
 */

#ifndef SRC_CAR_H_
#define SRC_CAR_H_

typedef struct {
	dc_motor rightMotor;
	dc_motor leftMotor;
	uint8 frame[4];
	uint8 carAngle;
	uint8 carSpeed;
	uint8 carDirection;
}car_dataType;

typedef enum {
	CAR_VALID_FRAME,
	CAR_INVALID_FRAME
}Car_frameStateType;


void Car_init(void);
Car_frameStateType Car_isValidFrame(uint8 * frame);
void Car_setFrame(uint8 * frame);
void Car_setDirection(void);
void Car_moveForward(void);
void car_rotateRight(void);
void car_rotateLeft(void);
void Car_setSpeed(void);
void Car_setAngel(void);
void Car_stopMoving(void);
void Car_go(uint8 * frame);

#endif /* SRC_CAR_H_ */
