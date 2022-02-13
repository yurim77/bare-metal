#include "mbed.h"

void GPIO_Config(){
	RCC->AHB1ENR |= (1<<0); // GPIOA
	
	GPIOA->MODER &= ~(1<<29); // PA14 SW2
	GPIOA->MODER &= ~(1<<28); 

	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}

void delay(uint32_t time){
	while(time--);
}

int main(){
	GPIO_Config();
	while(1){
		if((GPIOA->IDR & (1<<14)) == 0){
			GPIOA->ODR |= (1<<13);
			wait(1);
			// delay(20000000);
			GPIOA->ODR &= ~(1<<13);
			wait(1);
			// delay(20000000);
		}
	}
}