/*
 * hc165.c
 *
 *  Created on: Oct 4, 2023
 *      Author: gns2l
 */

#include "hc165.h"
#ifdef _USE_EXHW_HC165
#include "cli.h"



#ifdef _USE_HW_CLI
void clihc165(cli_args_t *args);
#endif

#define HC165_MAX_CH _EXHW_HC165_MAX_CH

typedef struct
{
  bool is_int;
  uint8_t input_state; // 74HC165 8bit 입력 상태 저장 배열
} hc165_tbl_t;

static hc165_tbl_t hc165_tbl[HC165_MAX_CH];

bool hc165_Init(void)
{
  for (int i = 0; i < HC165_MAX_CH; i++)
  {
    hc165_tbl[i].is_int = false;
    hc165_tbl[i].input_state = 0;
  }
#ifdef _USE_HW_CLI
  cliAdd("app", clihc165);
#endif

  return true;
}

bool hc165_IsInit(uint8_t ch)
{
  return hc165_tbl[ch].is_int;
}

/**
 * @brief 74HC165 read state
 * @param ch 74HC165 channel
 * @return 74HC165 8bit 입력 상태 저장 배열
 * bit 0 ~ 7 : input state 0 ~ 7
 * 
*/
uint8_t hc165_ReadInputs(uint8_t ch)
{
  HAL_GPIO_WritePin(HC165_SH_LD_GPIO_Port, HC165_SH_LD_Pin, GPIO_PIN_RESET); // SH/LD 핀 LOW로 설정
  HAL_GPIO_WritePin(HC165_SH_LD_GPIO_Port, HC165_SH_LD_Pin, GPIO_PIN_SET);   // SH/LD 핀 HIGH로 설정

  HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET); // CLK 핀 LOW로 설정
  hc165_tbl[ch].input_state = 0xff;                                      // 74HC165 8bit 입력 상태 저장 배열 초기화
  uint8_t input_state[8] = {
      0,
  }; // 74HC165 8bit 입력 상태 저장 배열
  // CLK 핀을 8번 토글하여 8비트 데이터 읽기
  uint8_t pin_value = 1 << 7;
  const uint8_t pin_in_on = 0;
  input_state[7] = HAL_GPIO_ReadPin(HC165_QH_GPIO_Port, HC165_QH_Pin);
  if (input_state[7] == pin_in_on)
    hc165_tbl[ch].input_state -= pin_value;
  for (int i = 1; i < 8; i++)
  {
    // 74HC165의 출력 상태를 읽어와 input_state 배열에 저장
    HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_SET);   // CLK 핀 HIGH로 설정
    HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET); // CLK 핀 LOW로 설정

    input_state[7 - i] = HAL_GPIO_ReadPin(HC165_QH_GPIO_Port, HC165_QH_Pin);
    uint8_t value = 1 << (7 - i);
    if (input_state[7 - i] == pin_in_on)
      hc165_tbl[ch].input_state -= value;
  }
  HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_SET);   // CLK 핀 HIGH로 설정
  HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET); // CLK 핀 LOW로 설정

  // LOG_PRINT("input_state [%d] :[%d][%d][%d][%d][%d][%d][%d][%d]", hc165_tbl[ch].input_state,
  //           input_state[0], input_state[1], input_state[2], input_state[3],
  //           input_state[4], input_state[5], input_state[6], input_state[7]);
  return hc165_tbl[ch].input_state;
}

#ifdef _USE_HW_CLI
void clihc165(cli_args_t *args)
{
  bool ret = false;

  if (args->argc == 1 && args->isStr(0, "info"))
  {
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "read"))
  {
    uint8_t hc165_ch;
    hc165_ch = constrain(args->getData(1), 1, HC165_MAX_CH) - 1;
    cliPrintf("hc165 read ch[%d] : value [%d]\n", hc165_ch, hc165_ReadInputs(hc165_ch));
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("hc165 info\n");
    cliPrintf("hc165 read ch[1~%d]\n", HC165_MAX_CH);
  }
}
#endif



#endif