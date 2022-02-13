#include "stm32f4xx.h"   

#define CLK 8400000UL

// Function prototype
void RCC_Config(void);
void GPIO_Init(void);
void TIM3_Init(void);
void TIM5_Init(void);


uint32_t count = 0, cap_var = 0;

void delay(uint32_t tm)
{
   while(tm--);
}

int main()
{
   RCC_Config();
   GPIO_Init();
   TIM5_Init();
   TIM3_Init();

    while(1)
   {
      while(TIM5->CCR2<=TIM3->ARR)
      {
         TIM5->CCR2 -= 1;
         TIM3->CCR3 +=1;
         //TIM3->CCR1 += 1;
         delay(5000);
      }
      TIM5->CCR2 &= ~(0xFFFFFFFF);
      TIM3->CCR3 &= ~(0xFFFFFFFF);
      // TIM3->CCR1 &= ~(0xFFFFFFFF);
      // TIM3->CCR1 &= ~(0xFFFFFFFF);
   }
}

void RCC_Config() // Fosc=8MHz 
{
   RCC->CR   |=   (1<<16);             // HSE ON
   while(!(RCC->CR   &(1<<17)));       // HSE ready waiting
   RCC->CFGR   |=   (1<<12);           // APB1 PSC=0
   RCC->CFGR   &=   ~(7<<13);          // APB2 PSC=0
   RCC->CFGR   |=   (10<<4);           // AHB PSC=8
   RCC->PLLCFGR   &=   ~(0xFFFFFFFF);  // APB2 PSC=0
   RCC->PLLCFGR   |=   (1<<22);        // HSE selected
   RCC->PLLCFGR   &=   ~(3<<16);       // PLLP=2
   RCC->PLLCFGR   |=   (64<<6);        // PLLN=64
   RCC->PLLCFGR   |=   (1<<2);         // PLLM=4
   RCC->PLLCFGR   |=   (1<<29);        // PLLR=2
   RCC->PLLCFGR   |=   (1<<25);        // PLLQ=2
   
   RCC->CR   |=   (1<<24);             // PLL ON
   while(!(RCC->CR   &(1<<25)));       // PLL ready waiting   
}

void GPIO_Init()
{
   RCC->AHB1ENR   |=   (1<<0);         // GPIOA clock enable
   RCC->AHB1ENR   |=   (1<<1);         // GPIOB clock enable
   RCC->AHB1ENR   |=   (1<<2);         // GPIOC clock enable
   
   GPIOA->MODER   |=   (1<<3);         // PA1 Alternate Function mode
   GPIOB->MODER   |=   (1<<1);         // PB0 Alternate Function mode
   GPIOC->MODER   |=   (1<<13);        // PC6 Alternate Function mode
   // GPIOC->OTYPER   &=   ~(1<<6);    // Push-Pull select
   
   GPIOA->PUPDR   &=   ~(3<<2);        // No push-No pull select
   GPIOA->AFR[0]   =   (1<<5);         // PA1 AF02(TIM5_CH2) alternate function
   
   GPIOB->PUPDR   &=   ~(3<<0);        // No push-No pull select
   GPIOB->AFR[0]   =   (1<<1);         // PB0 AF02(TIM3_CH3) alternate function
   
   GPIOC->PUPDR   &=   ~(3<<12);       // No push-No pull select
   GPIOC->AFR[0]   =   (1<<25);        // PC6 AF02(TIM3_CH1) alternate function
}

void TIM3_Init()
{
   RCC->APB1ENR   |=   (1<<1);         // TIM3 clock enable
   
   TIM3->PSC   |=   84-1;              // Prescaler value
   
   TIM3->ARR   = 1000;                 // Auto reload value
   
   TIM3->CCMR2   |=   (3<<5);          // PWM mode 1 - In upcounting, channe3 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
   TIM3->CCMR2   |=   (1<<3);          // Preload register on TIMx_CCR3 enabled. Read/Write operations access the preload register. TIMx_CCR3 preload value is loaded in the active register at each update event.
   
   // TIM3->CCMR1   |=   (3<<5);       // PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
   // TIM3->CCMR1   |=   (1<<3);       // Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload register. TIMx_CCR1 preload value is loaded in the active register at each update event.
   
   TIM3->CR1   |=   (1<<7);            // TIMx_ARR register is buffered
   TIM3->CR2   |=   (1<<7);            // TIMx_ARR register is buffered
   
   TIM3->EGR   |=   (1<<0);            // Re-initialize the counter and generates an update of the registers.
   
   TIM3->CCER   &=   ~(1<<1);          // OC1 active high
   TIM3->CCER   &=   ~(1<<3);          // CC1NP must be kept cleared in this case.
   TIM3->CCER   |=   (1<<0);           // On - OC1 signal is output on the corresponding output pin
   
   TIM3->CCER   &=   ~(1<<9);          // OC3 active high
   TIM3->CCER   &=   ~(1<<11);         // CC3NP must be kept cleared in this case.
   TIM3->CCER   |=   (1<<8);           // On - OC3 signal is output on the corresponding output pin
   
   TIM3->DIER   |=   (1<<1);           // capture/compare 1 interrupt enable
   
   TIM3->DIER   |=   (1<<3);           // capture/compare 3 interrupt enable
   
   TIM3->SR     &=   ~(1<<1);            // Capture interrupt flag clear
   
   TIM3->CCR3   |=   1000 ;            // Duty cycle control value 
   // TIM3->CCR1   |=   1000 ;         // Duty cycle control value 
   
   TIM3->CR1   |=   (1U<<0);           // Run timer3
   TIM3->CR2   |=   (1U<<0);           
}

void TIM5_Init()
{
   RCC->APB1ENR   |=   (1<<3);   //   TIM5 clock enable
   
   TIM5->PSC   |=   84-1;        //   Prescaler value
   
   TIM5->ARR   = 1000;           //   Auto reload value
   
   TIM5->CCMR1   |=   (3<<13);   //   PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
   TIM5->CCMR1   |=   (1<<11);   //  Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload register. TIMx_CCR1 preload value is loaded in the active register at each update event.
   
   TIM5->CR1   |=   (1<<7);      //   TIMx_ARR register is buffered
   
   TIM5->EGR   |=   (1<<0);      //    Re-initialize the counter and generates an update of the registers.
   
   TIM5->CCER   &=   ~(1<<1);    //   OC1 active high
   TIM5->CCER   &=   ~(1<<3);    //   CC1NP must be kept cleared in this case.
   TIM5->CCER   |=   (1<<0);     //   On - OC1 signal is output on the corresponding output pin
   
   TIM5->DIER   |=   (1<<1);     //   capture/compare 1 interrupt enable
   
   TIM5->SR   &=   ~(1<<1);      //   Capture interrupt flag clear
   
   TIM5->CCR2   |=   1000 ;      //   Duty cycle control value 
   
   TIM5->CR1   |=   (1U<<0);     //   Run timer5
}
