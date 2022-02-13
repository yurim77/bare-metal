#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn button(PA_14);

int main(){
	while(1) {
		if(!button) {
			myled = !myled
		}
	}
}