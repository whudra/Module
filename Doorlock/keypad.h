#ifndef	__KEYPAD_H__
#define	__KEYPAD_H__

#include <wiringPi.h>
#include <stdio.h>

#define KEYPAD_PB1		6
#define KEYPAD_PB2		12
#define KEYPAD_PB3		13

#define KEYPAD_PB5		16
#define KEYPAD_PB6		19
#define KEYPAD_PB7		20

#define KEYPAD_PB9		26
#define KEYPAD_PB10		21

#define KEYPAD_PB11		11
#define KEYPAD_PB14		9

#define MAX_KEY_BT_NUM	10

int initKeypad(void);
int readKeypad(void);

#endif	/* __KEYPAD_H__ */
