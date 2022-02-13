#include "mbed.h"

Serial pc(USBTX,USBRX);
AnalogIn x_axis(PC_2);
AnalogIn y_axis(PC_3);
InterruptIn button(PA_14);

int x, y, press, debug_print;
Ticker joystick;
DigitalOut led(LED1);

void joystick_handler(){
	x = x_axis.read() * 1000;
	y = y_axis.read() * 1000;
	debug_print = 1;
}

void BUTTON_ISR(){
	press = 1;
}

int main(){
	pc.baud(9600);
	joystick.attach(joystick_handler, 0.005);
	button.rise(&BUTTON_ISR);
	
	while(1){
		if(press){
			pc.printf("\r\n Button Pressed");
			led = !led;
			wait(0.5);
			press = 0;
		}
		if(debug_print){
			pc.printf("\rX=%3d, Y=%3d \n", x, y);
			debug_print = 0;
		}
	}
}