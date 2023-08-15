/*
 * hw.c
 *
 *  Created on: Jun 9, 2023
 *      Author: gns2l
 */


#include "hw.h"

__attribute__((section(".version"))) firm_version_t boot_ver =
    {
        _DEF_BOOT_VERSION,
        _DEF_BOARD_NAME
    };


bool hwInit(void)
{
	bspInit();

#ifdef _USE_HW_CLI
	cliInit();
#endif
	//logInit();
	ledInit();
	//spiInit();

	uartInit();
	for (int i=0; i<HW_UART_MAX_CH; i++)
	{
		uartOpen(i, 115200);
	}

#ifdef _USE_HW_LOG
	ret &= logInit();
	logOpen(HW_LOG_CH, 115200);
#else // use small size log func
	uartOpen(HW_LOG_CH, 115200);
#endif
	logPrintf("\r\n[ Bootloader Begin... ]\r\n");
	logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
	logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_BOOT_VERSION);
	logPrintf("Booting..Clock\t\t: %d Mhz\r\n", (int)HAL_RCC_GetSysClockFreq()/1000000);
	logPrintf("\n");

	rtcInit();
	resetInit();

	//faultInit();
	//spiFlashInit();

	flashInit();

	return true;
}


