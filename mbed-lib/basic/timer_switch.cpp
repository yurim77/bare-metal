#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn button(PA14);

int main(){
	while(1){
		if(!button) {
			myled = 1;	// LED is ON
			wait(5);	// 5 seconds
			myled = 0;	// LED is OFF
		}
	}
}