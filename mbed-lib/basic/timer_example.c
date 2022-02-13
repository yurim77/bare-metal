#include "mbed.h"

Timer myTimer;

DigitalOut led1(LED1);
Serial pc(USBTX, USBRX);

int main(){
    pc.baud(9600);

    while(1){
        myTimer.start();
        pc.printf("Timer started... ");
        myTimer.stop();
        pc.printf("and stopped. it took %f seconds\r\n", myTimer.read());

        wait(3);
    }
}