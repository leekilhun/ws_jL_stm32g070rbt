/*
 * hc165.c
 *
 *  Created on: Oct 4, 2023
 *      Author: gns2l
 */

#include "hc165.h"
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
  return true;
}

bool hc165_IsInit(uint8_t ch)
{
  return hc165_tbl[ch].is_int;
}

uint8_t hc165_ReadInputs(uint8_t ch)
{
  HAL_GPIO_WritePin(HC165_SH_LD_GPIO_Port, HC165_SH_LD_Pin, GPIO_PIN_RESET); // SH/LD 핀 LOW로 설정
  HAL_GPIO_WritePin(HC165_SH_LD_GPIO_Port, HC165_SH_LD_Pin, GPIO_PIN_SET); // SH/LD 핀 HIGH로 설정

  HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET); // CLK 핀 LOW로 설정
  hc165_tbl[ch].input_state = 0; // 74HC165 8bit 입력 상태 저장 배열 초기화
  // CLK 핀을 8번 토글하여 8비트 데이터 읽기
  for (int i = 0; i < 8; i++)
  {
    HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_SET);   // CLK 핀 HIGH로 설정
    
    HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET); // CLK 핀 LOW로 설정

    // 74HC165의 출력 상태를 읽어와 input_state 배열에 저장
    uint8_t value = 1 << i;
    if (HAL_GPIO_ReadPin(HC165_QH_GPIO_Port, HC165_QH_Pin) == GPIO_PIN_RESET)
    {
      // off
      hc165_tbl[ch].input_state -= value;
    }
    else
    {
      // on
      hc165_tbl[ch].input_state += value;
    }
  }


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
