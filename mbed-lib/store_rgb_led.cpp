#include "mbed.h"

Serial pc(USBTX, USBRX);
AnalogIn x_axis (PC_2);
AnalogIn y_axis (PC_3);

DigitalIn btn1(PA_14);
DigitalIn btn2(PB_7);
DigitalIn btn3(PC_4); 

DigitalOut led1(PA_13);
DigitalOut led2(D6);

PwmOut r (A1);
PwmOut g (PC_6);
PwmOut b (A3);
double rgb_arr[6] = {0.0, };

int x, y, press, press_num, debug_print;
Ticker joystick;

void joystick_handler(){
	x = x_axis.read() * 1000;
	y = y_axis.read() * 1000;
	debug_print = 1;
}

int main(){
	pc.baud(9600);
	joystick.attach(joystick_handler, 0.005);
	
	r.period(0.001);
	g.period(0.001);
	b.period(0.001);
	
	press_num = 0;
	while(1){
		if(!btn1){ 
			pc.printf("Push Button1(SW2) Pressed \r\n");
			press_num++;
			
			if (press_num == 1){
				rgb_arr[0] = x/255.0; // r
				rgb_arr[2] = y/255.0; // b
				rgb_arr[1] = 1.0 - b; // g
				
				pc.printf("Save Red : %lf\r\n", rgb_arr[0]);
				pc.printf("Save Green : %lf\r\n", rgb_arr[1]);
				pc.printf("Save Blue : %lf\r\n", rgb_arr[2]);	

				led1 = 1;
			}
			if (press_num == 2){
				rgb_arr[3] = x/255.0; // r
				rgb_arr[5] = y/255.0; // b
				rgb_arr[4] = 1.0 - b; // g
				 
				pc.printf("Save Red : %lf\r\n", rgb_arr[3]);
				pc.printf("Save Green : %lf\r\n", rgb_arr[4]);
				pc.printf("Save Blue : %lf\r\n", rgb_arr[5]);
				
				led2 = 1;
			}
			if (press_num > 2) {
				pc.printf("Push Button1(SW2) has already been pressed more than twice...\r\n");
			}
			
			wait(0.5);
		}
		if(!btn2){
			pc.printf("Push Button2(SW9) Pressed \r\n");
			pc.printf("Red : %lf, Green : %lf, Blue : %lf \r\n", rgb_arr[0], rgb_arr[1], rgb_arr[2]);
			
			r = rgb_arr[0];
			g = rgb_arr[1];
			b = rgb_arr[2];
			
			wait(2);
		}
		if(!btn3){
			pc.printf("Push Button3(SW10) Pressed \r\n");
			pc.printf("Red : %lf, Green : %lf, Blue : %lf \r\n", rgb_arr[3], rgb_arr[4], rgb_arr[5]);
			
			r = rgb_arr[3];
			g = rgb_arr[4];
			b = rgb_arr[5];
			
			wait(2);
		}
		if(debug_print){
			if(115 <= x && x <= 125 && 120 <= y && y <= 125){ 
				r = 0.0;
				b = 0.0;
				g = 0.0;
				
				pc.printf("Red : %lf, Green : %lf, Blue : %lf \r\n", 0.0, 0.0, 0.0);
			}
			else{
				r = x/255.0;
				b = y/255.0;
				g = 1.0 - b;
				
				pc.printf("Red : %lf, Green : %lf, Blue : %lf \r\n", x/255.0, 1.0 - b, y/255.0);
			}
			
			debug_print = 0;
			wait (0.5);
		}
	}
}