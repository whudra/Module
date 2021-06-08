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

int openDoor(char*);
int closeDoor(char*);

int controlDoorlock(int doorStatus, char *sn);


int getSensorData();
int setupWiringPiGpio(void);

#endif  /* __DOORLOCK_H__ */
