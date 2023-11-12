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

/**
 * @brief
 * It must be written in non-block code as a function called in 1ms time.
 * @param arg
 */
static void apISR_1ms(void *arg);
static void apISR_10ms(void *arg);
static enLed leds[AP_OBJ::LED_MAX];

ap_io mcu_io;

void apInit(void)
{
  

  {
    enLed::cfg_t cfg;
    cfg.gpio_port = STATUS_GPIO_Port;
    cfg.gpio_pin = STATUS_Pin;

    if (leds[AP_OBJ::LED_STATUS].Init(cfg) != ERROR_SUCCESS)
      LOG_PRINT("status_led Init Failed!");
  }

#ifdef _USE_HW_CLI
  cliOpen(HW_CLI_CH, 115200);
#endif

  for (int i = 0; i < 32; i += 1)
  {
    lcdClearBuffer(black);
    //lcdPrintfResize(0, 40 - i, green, 16, " -- WIZnet -- ");
    lcdPrintf(0, 40 - i, green, " -- WIZnet -- ");
    lcdDrawRect(0, 0, LCD_WIDTH, LCD_HEIGHT, white);
    lcdUpdateDraw();
    delay(10);
  }

  delay(1000);
  lcdClearBuffer(black);
  //lcdPrintfResize(0, 0, green, 16, "Getting IP..");
  lcdPrintf(0, 0, green, "Getting IP..");
  lcdUpdateDraw();

  /*Assign Obj */
  mcu_io.Init();

#ifdef _USE_HW_CLI
  cliAdd("app", cliApp);
#endif
}

void apMain(void)
{

  /**
   * @brief
   * register the function to the 1ms interrupt sw-timer.
   */
  {
    swtimer_handle_t timer_ch;
    timer_ch = swtimerGetHandle();
    if (timer_ch >= 0)
    {
      swtimerSet(timer_ch, 1, LOOP_TIME, apISR_1ms, NULL);
      swtimerStart(timer_ch);
    }
    else
    {
      LOG_PRINT("[NG] 1ms swtimerGetHandle()");
    }

    timer_ch = swtimerGetHandle();
    if (timer_ch >= 0)
    {
      swtimerSet(timer_ch, 10, LOOP_TIME, apISR_10ms, NULL);
      swtimerStart(timer_ch);
    }
    else
    {
      LOG_PRINT("[NG] 10ms swtimerGetHandle()");
    }
  }
  // end of swtimer
  
  uint32_t pre_time;
  pre_time = millis();

  while (1)
  {
    if (millis() - pre_time >= 1000)
    {
      pre_time = millis();

      // LOG_PRINT("HC165 STATE [%d]!",hc165_ReadInputs(0));
    }

    lcdUpdateDraw();

#ifdef _USE_HW_CLI
    cliMain();
#endif
  }
}

void updateLED()
{
  /**
   * @brief
   * status led
   */
  {
    static uint32_t pre_time_update_led;

    if (millis() - pre_time_update_led >= 1000)
    {
      pre_time_update_led = millis();
      leds[AP_OBJ::LED_STATUS].Toggle();
    }
  }
  // end of status led
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

void apISR_1ms(void *arg)
{
  /* 1. io register */
  mcu_io.Update_io();
}

void apISR_10ms(void *arg)
{
  updateLED();
}
