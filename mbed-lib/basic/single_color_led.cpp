#include "mbed.h"
Serial pc(USBTX, USBRX);

DigitalIn button1(PA_14);
DigitalIn button2(PB_7);
DigitalIn button3(PC_4);

DigitalOut led1(PA_13);
DigitalOut led2(D6);
DigitalOut led3(A2);

int main(){
	pc.printf("Hello World\r\n");
	while(1){
		pc.printf("testing...\r\n"):
		if(!button1){
			pc.printf("BUTTON 1 is pressed\r\n");
			led1 = !led1;
		}
		if(!button2){
			pc.printf("BUTTON 2 is pressed\r\n");
			led2 = !led2;
		}
		if(!button3){
			pc.printf("BUTTON 3 is pressed\r\n");
			led3 = !led3;
		}
		wait(0.2);
	}
}