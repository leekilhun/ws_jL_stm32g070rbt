/*
 * hw.h
 *
 *  Created on: Jun 9, 2023
 *      Author: gns2l
 */

#ifndef HW_HW_H_
#define HW_HW_H_



#ifdef __cplusplus
extern "C" {
#endif


#include "hw_def.h"

#include "led.h"
#include "log.h"
#include "uart.h"
#include "cmd.h"
#include "flash.h"
#include "rtc.h"
#include "reset.h"


bool hwInit(void);



#ifdef __cplusplus
}
#endif



#endif /* HW_HW_H_ */
