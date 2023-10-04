/*
 * hw_def.h
 *
 *  Created on: Jun 9, 2023
 *      Author: gns2l
 */

#ifndef HW_HW_DEF_H_
#define HW_HW_DEF_H_



#include "bsp.h"


/****************************************************
   boot/ firmware memory information
 ****************************************************/
#define _DEF_FW_VERSION             "V230608R1"
#define _DEF_FW_NAME                "PortableXY_firm"
#define FLASH_ADDR_BOOT_VER         0x08000400
#define FLASH_ADDR_TAG              0x08005000
#define FLASH_ADDR_FW               0x08005400
#define FLASH_ADDR_FW_VER           0x08005800

#define FLASH_ADDR_START            0x08005000
#define FLASH_ADDR_END              (FLASH_ADDR_START + (128-20)*1024)
/* ------------------------------------------------- */


#ifdef _USE_HW_RTOS
#define _HW_DEF_RTOS_MEM_SIZE(x)              ((x)/4)

#define _HW_DEF_RTOS_THREAD_PRI_MAIN          osPriorityNormal//osPriorityRealtime
#define _HW_DEF_RTOS_THREAD_PRI_CLI           osPriorityNormal//
#define _HW_DEF_RTOS_THREAD_PRI_RECEIVE       osPriorityNormal
#define _HW_DEF_RTOS_THREAD_PRI_CMD           osPriorityNormal
#define _HW_DEF_RTOS_THREAD_PRI_TASK          osPriorityNormal//osPriorityHigh

#define _HW_DEF_RTOS_THREAD_MEM_MAIN          _HW_DEF_RTOS_MEM_SIZE( 3*1024)
#define _HW_DEF_RTOS_THREAD_MEM_CLI           _HW_DEF_RTOS_MEM_SIZE( 3*1024)
#define _HW_DEF_RTOS_THREAD_MEM_CMD           _HW_DEF_RTOS_MEM_SIZE( 3*1024)
#define _HW_DEF_RTOS_THREAD_MEM_RECEIVE       _HW_DEF_RTOS_MEM_SIZE( 3*1024)
#define _HW_DEF_RTOS_THREAD_MEM_TASK          _HW_DEF_RTOS_MEM_SIZE( 3*1024)

#endif


#define _USE_HW_FLASH

#define _USE_HW_RTC
#define _USE_HW_RESET

#define _USE_HW_LED
#define      HW_LED_MAX_CH          1


#define _USE_HW_BUZZER

#define _USE_HW_UART
#define      HW_UART_MAX_CH         4
#define      HW_UART_MOTOR          _DEF_UART1
#define      HW_UART_PC             _DEF_UART2
#define      HW_UART_LOG            _DEF_UART3

#define _USE_HW_UART_1_DMA
#define _USE_HW_UART_2_DMA
#define _USE_HW_UART_3_DMA


//#define _USE_HW_LOG
#define      HW_LOG_CH              HW_UART_LOG
#define      HW_LOG_BOOT_BUF_MAX    1024
#define      HW_LOG_LIST_BUF_MAX    2048

#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_SWTIMER
#define      HW_SWTIMER_MAX_CH      4

//#define _USE_HW_CAN
#define      HW_CAN_MAX_CH          1
#define      HW_CAN_MSG_RX_BUF_MAX  16

//#define _USE_HW_SPI
#define      HW_SPI_MAX_CH          1
//#define        _SPI_W25Q16          _DEF_SPI1
//#define        _SPI_SLAVE           _DEF_SPI2


//#define _USE_HW_I2C
#define      HW_I2C_MAX_CH          2
#define        _I2C_EXT_IO          _DEF_I2C1
#define        _I2C_EEPROM          _DEF_I2C2


#endif /* HW_HW_DEF_H_ */
