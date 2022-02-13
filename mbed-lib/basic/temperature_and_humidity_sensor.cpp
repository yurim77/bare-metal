#include "mbed.h"
#include "DHT22.h"
#include <stdio.h>

DHT22 sensor (PB_2);
Serial pc(USBTX, USBRX);

int main(){
	float h=0.0f, c=0.0f;
	int temp, humid;
	
	pc.baud(9600);
	
	while(1){
		wait(2);
		sensor.sample();
		
		c=sensor.getTemperature();
		h=sensor.getHumidity();
		temp = (int)c;
		humid = (int)h;
		
		pc.printf("Temp: %d, Humid: %d\r\n", temp, humid);
	}
}
