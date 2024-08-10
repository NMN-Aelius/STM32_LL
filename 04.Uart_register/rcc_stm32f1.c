/*
Clock setup for stm32f103c8t6
Made by NhutNguyen - Aelius
Date: 10/08/2024
*/
#include "rcc_stm32f1.h"


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
	*						 Prescaler(1st)									= 1
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL                            = 8
  *            PLL_Mul                        = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */

void sys_clk_config()
{
	/*CLOCK CONFIG*/
	
	/*1. HSE CLOCK ENABLE*/
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSEON)); /* 0 continue */
	
	/*2.POWER ENBLE ABP1*/
	RCC->APB1ENR = RCC_APB1ENR_PWREN;
	
	/*3.PRESCALAR HCLK, PCLK1, PCLK2*/
	//ahb pr
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//apb1 pr
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	//apb2 pr
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
		
	/*4.PLL config*/
	//choose clock source
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;
	//multify number gain
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	
	/*5.Enable PLL*/
	//enable PLL to get 8Mhz*9 = 72MHz
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	/*6.System clock source*/
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	RCC->CFGR |= RCC_CFGR_SWS_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	/*7.Enable A port*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	/*8. Enable clock for USART1 */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

}