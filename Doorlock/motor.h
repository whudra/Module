#ifndef	__MOTOR_H__
#define	__MOTOR_H__

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define MOTOR_LEFT_ROTATE_PIN	4
#define MOTOR_RIGHT_ROTATE_PIN	17

#define LEFT_ROTATE		1
#define RIGHT_ROTATE	2

int initMotor(void);
void MotorStop();
void MotorControl(unsigned char speed, unsigned char rotate);

#endif	/* __MOTOR_H__ */
