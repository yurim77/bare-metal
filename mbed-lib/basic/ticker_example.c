#include "mbed.h"

Ticker myTicker;

DigitalOut led1(LED1);
Serial pc(USBTX, USBRX);

void task_myTicker(){
    pc.printf("ticker activated! led toggled!\r\n");
    led1 = !led1;
}

int main(){
    pc.baud(9600);

    myTicker.attach(&task_myTicker, 1.1);

    while(1){
        pc.printf("main loop... waiting for Ticker...\r\n");
        wait(0.2);
    }
}