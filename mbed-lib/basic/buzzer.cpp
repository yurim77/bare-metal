#include "mbed.h"
PwmOut sound(PC_9);
DigitalOut myled(LED1);

int main(){
	sound.period(0.0000833);
	// sound.period(1.0); // stop, sound off 사람이 들을 수 없는 소리
	// sound.write(0); // stop, sound off
	sound = 0.5;
	myled = 0;
	
	while(1){
		myled = !myled;
		wait(1);SS
	}
} 