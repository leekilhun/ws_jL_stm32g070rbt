/*
 * ap.cpp
 *
 *  Created on: Apr 23, 2023
 *      Author: gns2l
 */

#include "ap.hpp"



#ifdef _USE_HW_CLI
static void cliApp(cli_args_t *args);
#endif



ap_io mcu_io;

void apInit(void)
{

#ifdef _USE_HW_CLI
  cliOpen(HW_UART_LOG, 115200);
#endif

  /*Assign Obj */
  mcu_io.Init();


#ifdef _USE_HW_CLI
  cliAdd("app", cliApp);
#endif
}


void apMain(void)
{
  uint32_t pre_time;
  pre_time = millis();
  

  while (1)
  {
    if (millis() - pre_time >= 1000)
    {

      //cliPrintf("Hello World! %d\n", millis());
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

#ifdef _USE_HW_CLI
    cliMain();
#endif

    /* 1. io register */
    mcu_io.Update_io();
  }
  

}




#ifdef _USE_HW_CLI

void cliApp(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1)
  {
    if (args->isStr(0, "info") == true)
    {
      ret = true;
    }
    else if (args->isStr(0, "sys_io_show") == true)
    {
      while (cliKeepLoop())
      {

      }

      ret = true;
    }
    else if (args->isStr(0, "io_in") == true)
    {
      cliPrintf("mcu io in [%d] \n", mcu_io.m_in.data);
      ret = true;
    }
  }
  else if (args->argc == 2)
  {

    if (args->isStr(0, "io_on") == true)
    {
      uint8_t idx = (uint8_t)args->getData(1);

      if (mcu_io.OutputOn(idx + AP_DEF_START_OUT_ADDR) == ERROR_SUCCESS)
      {
        cliPrintf("io_on [%d] success! \n", idx + AP_DEF_START_OUT_ADDR);
        ret = true;
      }
    }
    else if (args->isStr(0, "io_off") == true)
    {
      uint8_t idx = (uint8_t)args->getData(1);
      if (mcu_io.OutputOff(idx + AP_DEF_START_OUT_ADDR) == ERROR_SUCCESS)
      {
        cliPrintf("io_off [%d] success! \n", idx + AP_DEF_START_OUT_ADDR);
        ret = true;
      }
    }
  }
  else if (args->argc == 3)
  {

  }
  else if (args->argc == 4)
  {

  }

  if (ret == false)
  {
    cliPrintf("app info \n");
    cliPrintf("app sys_io_show \n");
    cliPrintf("app io_in \n");
    cliPrintf("app io_on [0:7] \n");
    cliPrintf("app io_off [0:7] \n");
  }
}
#endif

