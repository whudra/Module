
#include <softTone.h>
#include "buzzer.h"

int initBuzzer(void)
{
#if 0
	//wiringpi Init	
	if(wiringPiSetupGpio() == -1) {
		return 1;
	}	
#endif

	// BUZZER Init
	pinMode(BUZZER_PIN, OUTPUT);		// BUZZER PIN OUTPUT SET
	digitalWrite(BUZZER_PIN, LOW);		// BUZZER OFF	
	
	printf("Buzzer Initialize\n");

	softToneCreate (BUZZER_PIN) ;
	STOP_FREQ();
	return 0;
}	

void Change_FREQ(unsigned int freq)
{
	pwmWrite(BUZZER_PIN, freq);
	softToneWrite (BUZZER_PIN, freq);
}
void STOP_FREQ (void)
{
	softToneWrite (BUZZER_PIN, 0);
}

void playBuzzer(unsigned char status)
{
	int i;
	if (status == 1) {
		digitalWrite(BUZZER_PIN, HIGH);
		delay(10);
		digitalWrite(BUZZER_PIN, LOW);
		delay(10);
	}		
}
