/*
 * bsp.c
 *
 *  Created on: Aug 21, 2022
 *      Author: gns2l
 *
 *  for stm32g070 bootloader fw
 *  to reduce the file size, the function is simplified.
 *  logPrintf  -> (system callback function)print
 *
 *  LL_RCC_LSI_Enable - to use reset count function.
 */





#include "bsp.h"
#include "uart.h"

void SystemClock_Config(void);


bool bspInit(void)
{
	HAL_Init();

	SystemClock_Config();

	return true;
}

void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}


void bspDeInit(void)
{
  HAL_RCC_DeInit();

  // arm M0
  // Disable Interrupts
  NVIC->ICER[0] = 0xFFFFFFFF;
  __DSB();
  __ISB();

  SysTick->CTRL = 0;
}


#ifndef _USE_HW_LOG
int __io_putchar(int ch)
{
	int ret = 0;
	ret = (int)uartWrite(HW_LOG_CH, (uint8_t *)&ch, 1);
	return ret ;
}
#endif


void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
	{
	}

	/* HSI configuration and activation */
	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1)
	{
	}

	/* LSI configuration and activation */
	LL_RCC_LSI_Enable();
	while(LL_RCC_LSI_IsReady() != 1)
	{
	}

	LL_PWR_EnableBkUpAccess();
	/* Main PLL configuration and activation */
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_Enable();
	LL_RCC_PLL_EnableDomain_SYS();
	while(LL_RCC_PLL_IsReady() != 1)
	{
	}

	/* Set AHB prescaler*/
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

	/* Sysclk activation on the main PLL */
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}

	/* Set APB1 prescaler*/
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	/* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
	LL_SetSystemCoreClock(64000000);

	/* Update the time base */
	if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
	{
		Error_Handler();
	}


}

void Error_Handler(void)
{
  while(1)
  {
  }

}
