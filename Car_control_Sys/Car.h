/*
 * Data.h
 *
 *  Created on: Dec 24, 2023
 *      Author: abram
 */

#ifndef SRC_CAR_H_
#define SRC_CAR_H_

typedef struct
{
	dc_motor rightFrontMotor;
	dc_motor rightBackMotor;
	dc_motor leftFrontMotor;
	dc_motor leftBackMotor;
	uint8 frame[4];
	uint8 carAngle;
	uint8 carSpeed;
	uint8 carDirection;
} car_dataType;

typedef enum
{
	CAR_VALID_FRAME,
	CAR_INVALID_FRAME
} Car_frameStateType;

void Car_init(void);
Car_frameStateType Car_isValidFrame(uint8 *frame);
void Car_setFrame(uint8 *frame);
void Car_setDirection(void);
void Car_moveForward(void);
void Car_rotateRight(void);
void Car_rotateLeft(void);
void Car_setSpeed(void);
void Car_setAngel(void);
void Car_stopMoving(void);
void Car_go(uint8 *frame);
void Car_MoveBack(void);
void Car_calibration(uint16 time);

#endif /* SRC_CAR_H_ */
