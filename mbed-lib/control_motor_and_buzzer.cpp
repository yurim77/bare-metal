#include "mbed.h"
#include "motordriver.h"

DigitalIn btn1(PA_14);
DigitalIn btn2(PB_7);
DigitalIn btn3(PC_4); 

PwmOut sound(PC_9);
Motor mt(D11, PC_8);

int main(){
	while(1){
		if(!btn1){
			sound.period(0.0000833);
			sound = 0.5;
			mt.forward(0.2f);
		}
		if(!btn2){
			sound.period(0.000253096);
			sound = 0.5;
			mt.backward(0.4f);
		}
		if(!btn3){
			sound.period(0.000337842);
			sound = 0.5;
			mt.forward(0.6f);
		}
		wait(0.2);
	}
}