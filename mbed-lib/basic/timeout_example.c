#include "mbed.h"

Timeout myTimeout;

DigitalOut led1(LED1);
DigitalIn button1(PA_14);
Serial pc(USBTX, USBRX);

void task_myTimeout(){
    pc.printf("timeout! task activated\r\n");
    led1 = !led1;
}

int main(){
    pc.baud(9600);

    while(1){
        if(!button){
            myTimeout.attach(&task_myTimeout, 3.0);
            led1 = !led1;
        }
    }
}