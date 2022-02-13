#include "mbed.h"

Serial pc(USBTX, USBRX);

DigitalIn btn1(PA_14);
DigitalIn btn2(PB_7);
DigitalIn btn3(PC_4); 

DigitalOut led1(PA_13);
DigitalOut led2(D6);
DigitalOut led3(A2);


int main(){	
	int phase = 0;
	int operand = 0;
	int val1, val2 = 0;
	
	pc.printf("Calculator Initiated\r\n");

	while(1){
		if(!btn2){
			phase = (phase+1)%4;
			pc.printf("phase shifted to %d\r\n", phase);
			
			wait(0.2);
			continue;
		}
		
		if(phase==0){
			led1 = 1;
			led2 = 0;
			led3 = 0;
			
			if(!btn1){
				val1++;
				pc.printf("val1 = %d\r\n", val1);
				
				wait(0.2);
				continue;
			}
			if(!btn3){
				val1--;
				pc.printf("val1 = %d\r\n", val1);
				
				wait(0.2);
				continue;
			}
		}
		
		if(phase==1){
			led1 = 0;
			led2 = 1;
			led3 = 0;
			
			if(!btn1){
				operand = 0;
				pc.printf("Plus");
				
				wait(0.2);
				continue;
			}
			if(!btn3){
				operand = 1;
				pc.printf("Minus");
				
				wait(0.2);
				continue;
			}
		}
		
		if(phase==2){
			led1 = 0;
			led2 = 0;
			led3 = 1;
			
			if(!btn1){
				val2++;
				pc.printf("val2 = %d\r\n", val2);
				
				wait(0.2);
				continue;
			}
			if(!btn3){
				val2--;
				pc.printf("val2 = %d\r\n", val2);
				
				wait(0.2);
				continue;
			}
		}
		
		if(phase==3){
			led1 = 1;
			led2 = 1;
			led3 = 1;
			
			if(operand == 0){
				pc.printf("answer : %d + %d = %d\r\n", val1, val2, val1+val2);
				
				phase = 0;
				pc.printf("phase shited to 0\r\n");
				
				wait(0.2);
			}
			if(operand == 1){
				pc.printf("answer : %d + %d = %d\r\n", val1, val2, val1-val2);
				
				phase = 0;
				pc.printf("phase shited to 0\r\n");
				
				wait(0.2);
			}
			
			operand = 0;
			val1 = 0;
			val2 = 0;
		}
		
		wait(0.1);
	}
}