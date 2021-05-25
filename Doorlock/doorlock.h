#ifndef __DOORLOCK_H__
#define __DOORLOCK_H__

#include <stdio.h>
#include <wiringPi.h>

int PasswardVerify(void);
void ErrorPassward(void);
void ButtonDetect(void);
void PasswardVerifySuccess(void);

void OpenDoorBeep(void);
void ErrorBeep(void);

int openDoor(void);
int closeDoor(void);

int controlDoorlock(int doorStatus);

int getSensorData(void);
int setupWiringPiGpio(void);

#endif  /* __DOORLOCK_H__ */