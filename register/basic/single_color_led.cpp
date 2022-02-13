#include "mbed.h"

void GPIO_Config(){
	RCC->AHB1ENR |= (1s<<0); // GPIOA
	
	GPIOA->MODER &= ~(1<<27); // PA13 LED1
	GPIOA->MODER |= (1<<26);

	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}

void delay(uint32_t time){
	while(time--);
}

int main(){
	GPIO_Config();
	while(1){
		GPIOA->ODR |= (1<<13);
		wait(1);
		// delay(20000000);
		GPIOA->ODR &= ~(1<<13);
		wait(1);
		// delay(20000000);
	}
}