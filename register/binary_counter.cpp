#include "mbed.h"

Serial pc(USBTX, USBRX);

void GPIO_Config(){
	RCC->AHB1ENR |= (1<<0); // GPIOA
	RCC->AHB1ENR |= (1<<1); // GPIOB
	RCC->AHB1ENR |= (1<<2); // GPIOC
	
	GPIOA->MODER &= ~(1<<27); // PA13 LED1
	GPIOA->MODER |= (1<<26);
	
	GPIOB->MODER &= ~(1<<21); // PB10 LED2
	GPIOB->MODER |= (1<<20);
	
	GPIOA->MODER &= ~(1<<9); // PA4 LED3
	GPIOA->MODER |= (1<<8);
	
	GPIOA->MODER &= ~(1<<29); // PA14 SW2
	GPIOA->MODER &= ~(1<<28);
	
	GPIOB->MODER &= ~(1<<15); // PB7 SW9
	GPIOB->MODER &= ~(1<<14);
	
	GPIOC->MODER &= ~(1<<9); // PC4 SW10
	GPIOC->MODER &= ~(1<<8);
	
	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
	
	GPIOB->OTYPER = 0;
	GPIOB->OSPEEDR = 0;
	
	GPIOC->OTYPER = 0;
	GPIOC->OSPEEDR = 0;
}

void LED_ON(int num){
	int arr[3] = {0,};
	int c = 0;
	int mok, nmg;
	
	do{
		mok = num / 2;
		nmg = num - mok * 2;
		arr[c++] = nmg;
		num = mok;
	}while(mok != 0);
	
	pc.printf("cnt(2) : %d%d%d\r\n", arr[2], arr[1], arr[0]);
	if(arr[2] == 1) GPIOA->ODR |= (1<<13); // PA13 LED1
	if(arr[1] == 1) GPIOB->ODR |= (1<<10); // PB10 LED2
	if(arr[0] == 1) GPIOA->ODR |= (1<<4); // PA4 LED3
	wait(3);
	
	GPIOA->ODR &= ~(1<<13);
	GPIOB->ODR &= ~(1<<10);
	GPIOA->ODR &= ~(1<<4);
	wait(1);
}

int main(){
	int cnt = 0;
	pc.baud(9600);
	
	GPIO_Config();
	pc.printf("GPIO init\r\n");
	
	while(1){
		if((GPIOA->IDR & (1<<14)) == 0){ // PA14 SW2
			pc.printf("SW2 pressed\r\n");
			cnt--;
			pc.printf("cnt(10) : %d\r\n", cnt);
			
		}
		if((GPIOB->IDR & (1<<7)) == 0){ // PB7 SW9
			pc.printf("SW9 pressed\r\n");
			pc.printf("cnt(10) : %d\r\n", cnt);
			LED_ON(cnt);
		}
		if((GPIOC->IDR & (1<<4)) == 0){ // PC4 SW10
			pc.printf("SW10 pressed\r\n");
			cnt++;
			pc.printf("cnt(10) : %d\r\n", cnt);	
		}
		wait(0.5);
	}
}