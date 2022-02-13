#include "mbed.h"
// #include "stm32f401xe.h"

Serial PC(USBTX, USBRX);

void ADC_Init(){
	RCC->APB2ENR |= (1<<8);
	RCC->AHB1ENR |= (1<<2);
	
	ADC->CCR |= 1<<16;
	
	ADC1->CR1 = (1<<8);
	ADC1->CR1 &= ~(1<<24);
	
	ADC1->CR2 |= (1<<1);
	ADC1->CR2 |= (1<<10);
	ADC1->CR2 &= ~(1<<11);
	
	ADC1->SMPR1 &= ~((1<<6)|(1<<9));
	
	ADC1->SQR1 |= (1<<20);
	
	GPIOC->MODER |= (3<<4);
	GPIOC->MODER |= (3<<6);
	
}

void ADC_Enable(){
	ADC1->CR2 |= 1<<0;
	uint32_t delay = 10000;
	while(delay--);
}

void ADC_Start(int channel){
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (channel<<0);
	
	ADC1->SR = 0;
	
	ADC1->CR2 |= (1<<30);
}

void ADC_WaitForConv(){
	while(!(ADC1->SR & (1<<1)));
}

uint16_t ADC_GetVal(){
	return ADC1->DR;
}

void ADC_Disable(){
	ADC1->CR2 &= ~(1<<0);
}

uint16_t ADC_VAL[2] = {0, 0};

void delay(uint32_t time){
	while(time--);
}

int main(){
	ADC_Init();
	ADC_Enable();
	while(1){
		ADC_Start(12);
		ADC_WaitForConv();
		ADC_VAL[0] = ADC_GetVal();

		
		ADC_Start(13);
		ADC_WaitForConv();
		ADC_VAL[1] = ADC_GetVal();
		
		PC.printf("%d and %d\r\n", ADC_VAL[0], ADC_VAL[1]);
	}
}
