#include "mbed.h"

PwmOut r (A1);
PwmOut g (PC_6);
PwmOut b (A3);

int main(){
	r.period(0.001);
	g.period(0.001);
	b.period(0.001);
	
	while(1){
		for(double i = 0.0; i < 3.0; i += 0.01){
			r = ((i < 1.0) ? i : (i < 2.0) ? 1.0 : 3.0 - i);
			g = ((i < 1.0) ? 1 - i : (i < 2.0) ? 0.0 : i - 2.0);
			b = ((i < 1.0) ? i : (i < 2.0) ? 2.0 - i : i - 2.0);
			wait(0.01);
		}
	}
}