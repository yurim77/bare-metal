#include "mbed.h"

DigitalIn motion(D5);
DigitalOut led1(LED1);
Serial pc(USBTX, USBRX);

volatile int sensor = 0;

int main(){
	pc.baud(9600);

	while(1){
		int sensor = motion;
		if(sensor){
			led1 = 1;
			pc.printf("Human Detected -> LED ON\r\n");
			sensor = 0;
			wait(3);
		}
		led1 = 0;
	}
}