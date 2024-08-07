#include "stm32f10x.h"
#include "stdint.h"


static void SysClockConfig(void)
{
	/* STM32F407VGT6
	1. Enable HSE and wait for the HSE to become ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PRETECH and the LATENCY Related
	4. Configure the Prescaler, HCLK, PCLK, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the clock source and wit for it to be set	
	*/
	
	/* 1. Enable HSE and wait for the HSE to become ready */
	RCC->CR |= RCC_CR_HSEON; /* 0x00010000 External High Speed clock enable */
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	/* 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	/*STM32F1 dont have VOS so not config it this time*/
	
	/* 3. Configure the FLASH PRETECH and the LATENCY Related */
	/* ((: datasheet doesnt have */
}

static void GPIO_config(void)
{
	/* GPIO port in APB2 register so we will using this one. */
	/* 1. Turn on clock for gpioA */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	/* 2. Config PA5 is a output push-pull pin */
	/* Go to port configuration registor low due to using pa5*/
	
	/* clear bit (GPIO_CRL_MODE5 = 0x00300000(8 bits represent for 8 gpio in low registor) = CNF(00)MODE(11))*/
	GPIOA -> CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
	/*Mergeing logic status at 2 bits*/
	GPIOA -> CRL |= (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0);
	/* Set bit for CNF at mode push-pull */
}

int main(void)
{
	SysClockConfig();
	GPIO_config();
	
	uint32_t i, j;
	
	while(1)
	{
	/* do jobs */
		GPIOA->BSRR = GPIO_BSRR_BS5; /* (=0x000000 20) */
		for (i = 0; i < 100000; i++);
		i=0;
		GPIOA->BSRR = GPIO_BSRR_BR5;
		for (j = 0; j < 100000; j++);
		j=0;
	}
}
