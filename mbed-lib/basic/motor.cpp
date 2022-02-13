#include "mbed.h"
#include "motordriver.h"

Motor mt(D11, PC_8);

int main(){
	while(1){
		for(float s=0; s<1.0f; s+=0.1f){
			mt.forward(s);
			wait(0.5);
		}
		mt.stop();
		wait(3);

		for(float s=0; s<1.0f; s+=0.1f){
			mt.backward(s);
			wait(0.5);
		}
		mt.stop();
		wait(3);
	}
}