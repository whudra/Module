#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <stdio.h>
#include <wiringPi.h>

#define BUZZER_PIN	18

#define DO_L		523
#define RE			587
#define MI			659
#define FA			698
#define SOL			784
#define RA			880
#define SI			987
#define DO_H		1046

#define ON	1
#define OFF	0

int initBuzzer(void);
void playBuzzer(unsigned char status);
void Change_FREQ(unsigned int freq);
void STOP_FREQ (void);

unsigned int SevenScale (unsigned char scale);

#endif  /* __BUZZER_H__ */
