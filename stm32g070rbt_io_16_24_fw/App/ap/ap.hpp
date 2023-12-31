/*
 * ap.hpp
 *
 *  Created on: Apr 23, 2023
 *      Author: gns2l
 */

#ifndef INCLUDE_AP_HPP_
#define INCLUDE_AP_HPP_

/*

#include "utils.h"
#include "uart.h"
#include "led.h"
*/


#include "ap_def.h"


/* ap object*/
#include "ap_utils.hpp"
#include "ap_dat.hpp"

/* ap object */
/* register -> communication -> basic unit(engine) -> combined unit(engine) -> control */
//register + io_manager"
#include "ap_io.hpp"

//basic


//control


//api


void  apInit(void);
void  apMain(void);

#endif /* INCLUDE_AP_HPP_ */
