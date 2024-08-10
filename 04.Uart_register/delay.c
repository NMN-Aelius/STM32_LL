#include "delay.h"
#include "rcc_stm32f1.h"

void TIM2_config(void)
{
	/* 1. enable timer clock
	2. set prescaler and ARR
	3. enable timer and wait for flag*/
	
	/*1. enable timer 2 at APB1 bus*/
	RCC->APB1ENR |= (1<<0);
	/* this is same with the previous one 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  */
	
	/* 2. set the prescaler at TIM2 register*/
	TIM2->ARR = 0xffff -1; // 16bits register have been set as maxmium
	TIM2->PSC = 72-1; //frequency is 1Mhz
	
	TIM2->CR1 |= (1<<0);
	//TIM2->CR1 = TIM_CR1_CEN; //enable counter timer
	//while(!(TIM2->SR & TIM_SR_UIF)); //false is continue while
	while(!(TIM2->SR & (1<<0))); //false is continue while
	//		!(	0			 &			1) => continue
	//		!(	1			 &			1) => got interrupt => discontinue 
}

void ud_delay_us(uint16_t us)
{
	/* reset counter */
	TIM2->CNT = 0;
	//previous is same TIM2->CNT &= ~(TIM_CNT_CNT);
	
	while(TIM2->CNT < us); //true continue loop
}

void ud_delay_ms(uint16_t ms)
{
	for(uint16_t index =0; index <ms; index++)
	{
		ud_delay_us(1000); //equivalent to 1ms
	}
}