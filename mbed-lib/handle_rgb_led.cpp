#include "mbed.h"

Serial pc(USBTX, USBRX);
AnalogIn x_axis (PC_2);
AnalogIn y_axis (PC_3);
InterruptIn button (PA_15);

int x, y, press, debug_print;
Ticker joystick;
DigitalOut led(LED1);


PwmOut r (A1);
PwmOut g (PC_6);
PwmOut b (A3);

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
			printf("\r\n Button Pressed");
			led = !led;
			wait(0.5);
			press = 0;
			}
		if(debug_print){
			pc.printf("\rX=%3d, Y=%3d \n", x, y);
			r = x/255.0;
			b = y/255.0;
			g = 1.0 - b;
			debug_print = 0;
			wait (0.01);
		}
	}
}
