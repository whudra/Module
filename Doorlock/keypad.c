#include "keypad.h"

const int KeypadTable[10]= {
	KEYPAD_PB1, KEYPAD_PB2, KEYPAD_PB3, 
	KEYPAD_PB5, KEYPAD_PB6, KEYPAD_PB7,
	
	KEYPAD_PB9, KEYPAD_PB10, KEYPAD_PB11,
	KEYPAD_PB14
};

int readKeypad(void)
{
	int i,nKeypadstate;
        nKeypadstate = 0;
	for(i =0; i<MAX_KEY_BT_NUM; i++) {
		if(!digitalRead(KeypadTable[i])) {
			nKeypadstate |= (1<<i);
		}
	}
    return nKeypadstate;
}

int initKeypad(void)
{
#if 0
	if (wiringPiSetupGpio()<0)
		return 1;
#endif
	int i;
	for(i =0; i<MAX_KEY_BT_NUM; i++) {
		pinMode(KeypadTable[i],INPUT);
	}
	printf("Keypad Initialize\n");
	return 0;
}
