#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "adc.h"

#include "../Defines.h"
#include "../drv/uart.h"
#include "../lib/Sscanf_str.h"
#include "UI_CLI.h"

#if CLI_ENABLE
#define IORD(BASE, REGNUM) \
  __builtin_ldwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)))
#define IOWR(BASE, REGNUM, DATA) \
  __builtin_stwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)), (DATA))

static s1_t gs1a_Packet[UART_PACKET_SIZE_MAX];

s1_t ms1_Celsius;
s1_t ms1_CelsiusWarning = 50;

void UI_UpdateProcess()
{
  u4_t u4_ADC1;
  const f4_t f4c_Vsense = 3.3 / 4095;
  const f4_t f4c_Avg_Slope = 0.0025;
  const f4_t f4c_V25 = 0.76;

  HAL_ADC_PollForConversion(&hadc1, 100);
  u4_ADC1 = HAL_ADC_GetValue(&hadc1);

  ms1_Celsius = ((u4_ADC1 * f4c_Vsense - f4c_V25) / f4c_Avg_Slope) + 25;
  if(ms1_Celsius > ms1_CelsiusWarning)
    printf_CLI("<<Warning>> High Temperature: %d deg C\r\n", ms1_Celsius);
}

u4_t gu4_DumpWidth = 8;

void CLI_DebugProcess(void)
{
  int s4_Size = 0;
  GPIO_TypeDef *tp_GPIOx;
  u4_t u4_Temp1, u4_Temp2, u4_Temp3, u4_Temp4;
  s1_t s1_Temp1;
  u4_t *u4p_Data;
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
  volatile u1_t *u1p_DPRAM;

  s1_t s1a_CmdStr[16]; // Command or argument
  s1_t *s1p_ParamStr = NULL;

  s4_Size = Uart_GetCmdPacket(UART_HOST_DEBUG, gs1a_Packet);

  if(s4_Size > 0)
  {
    s1p_ParamStr = gs1a_Packet;

    s2_StrLen = sscanf_str(s1p_ParamStr, s1a_CmdStr, &s1_EOS);
    s1p_ParamStr = s1p_ParamStr + s2_StrLen + 1;

    if(strcmp(s1a_CmdStr, "io") == 0)
    {
      s2_ParamRead = sscanf_3u4(&s1p_ParamStr, &u4_Temp1, &u4_Temp2, &u4_Temp3,
                                16);
      switch(s2_ParamRead)
      {
        case 3:
          u4p_Data = (u4_t*) (u4_Temp1 + u4_Temp2);
          *u4p_Data = u4_Temp3;
          break;
        case 2:
          u4p_Data = (u4_t*) (u4_Temp1 + u4_Temp2);
          printf_CLI("%08X \n\r", *u4p_Data);
          break;
        default:
//        printf_CLI(" \re: io <Address to read in hex> <Offset Address in hex> [Data to Write] \n\r");
          break;
      }
    }

    else if(strcmp(s1a_CmdStr, "dump_width") == 0)
    {
      s2_ParamRead = sscanf_1u4(&s1p_ParamStr, &u4_Temp1, 10);

      switch(s2_ParamRead)
      {
        case 1:
          gu4_DumpWidth = u4_Temp1;
          break;
        default:
//        printf_CLI(t_ID, "Dump Width: %d\n\r", gu4_DumpWidth);
//        printf_CLI(t_ID, "Usage: dump_width [bytes per line in decimal]\n\r");
          break;
      }
    }
    else if(strcmp(s1a_CmdStr, "dump") == 0)
    {
      s2_ParamRead = sscanf_2u4(&s1p_ParamStr, &u4_Temp1, &u4_Temp2, 16);
      switch(s2_ParamRead)
      {
        case 1:
          u4_Temp2 = 256;
        case 2:
          for(u4_Temp3 = 0; u4_Temp3 < u4_Temp2; u4_Temp3 += 1)
          {
            u4p_Data = (u4_t*) (u4_Temp1 + u4_Temp3);
            if((u4_Temp3 % gu4_DumpWidth) == 0)
              printf_CLI("\n\r0x%08X:", (u4_Temp1 + (u4_Temp3 << 2)));
            printf_CLI(" %08X", *u4p_Data);
          }
          printf_CLI("\n\r");
          break;
        default:
          //				printf_CLI(t_ID, "Usage: io_dump <start address in hex> [size in hex, default=0x100(256)]\n\r");
          break;
      }
    }
    else if(strcmp(s1a_CmdStr, "fill") == 0)
    {
      s2_ParamRead = sscanf_3u4(&s1p_ParamStr, &u4_Temp1, &u4_Temp2, &u4_Temp3,
                                16);
      switch(s2_ParamRead)
      {
        case 1: // Temp1 = Base address
          u4_Temp2 = 256;
        case 2: // Temp1 = Base address, Temp2 = Data count to fill
          for(u4_Temp3 = 0; u4_Temp3 < u4_Temp2; u4_Temp3 += 1)
          {
            u4p_Data = (u4_t*) (u4_Temp1 + u4_Temp3);
            *u4p_Data = u4_Temp3;
          }
          break;
        case 3: // Temp1 = Base address, Temp2 = Data count to fill, Temp3 = Data to fill
          for(u4_Temp4 = 0; u4_Temp4 < u4_Temp2; u4_Temp4 += 1)
          {
            u4p_Data = (u4_t*) (u4_Temp1 + u4_Temp4);
            *u4p_Data = u4_Temp3;
          }
          break;
        default:
//        printf_CLI(t_ID, "Usage: io_dump <start address in hex> [size in hex, default=0x100(256)]\n\r");
          break;
      }
    }
    else if(strcmp(s1a_CmdStr, "gpio") == 0)
    {
      s2_ParamRead = sscanf_char(&s1p_ParamStr, &s1_Temp1);
      if(s2_ParamRead == 1)
      {
        switch(s1_Temp1)
        {
          case 'a': tp_GPIOx = GPIOA; break;
          case 'b': tp_GPIOx = GPIOB; break;
          case 'c': tp_GPIOx = GPIOC; break;
          case 'd': tp_GPIOx = GPIOD; break;
          case 'e': tp_GPIOx = GPIOE; break;
          case 'f': tp_GPIOx = GPIOF; break;
          case 'g': tp_GPIOx = GPIOG; break;
          case 'h': tp_GPIOx = GPIOH; break;
          case 'i': tp_GPIOx = GPIOI; break;
          case 'j': tp_GPIOx = GPIOJ; break;
          case 'k': tp_GPIOx = GPIOK; break;
        }
        s2_ParamRead = sscanf_1u4(&s1p_ParamStr, &u4_Temp1, 16);
        switch(s2_ParamRead)
        {
          case 1:
            tp_GPIOx->ODR = u4_Temp1;
          default:
            printf_CLI("%08X \n\r", tp_GPIOx->IDR);
            break;
        }
      }
    }
    else if(strcmp(s1a_CmdStr, "temp") == 0)
    {
      printf_CLI("%d\n\r", ms1_Celsius);
    }
    else if(strcmp(s1a_CmdStr, "temp_w") == 0)
    {
      s2_ParamRead = sscanf_1u4(&s1p_ParamStr, &u4_Temp1, 10);
      switch(s2_ParamRead)
      {
        case 1:
          ms1_CelsiusWarning = u4_Temp1;
        default:
          printf_CLI("%d\n\r", ms1_CelsiusWarning);
          break;
      }
    }
    else if(strcmp(s1a_CmdStr, "debug_on") == 0)
    {
      printf_debug_on();
    }
    else if(strcmp(s1a_CmdStr, "debug_off") == 0)
    {
      printf_debug_off();
    }
    memset(gs1a_Packet, 0, UART_PACKET_SIZE_MAX);
  }
}

#endif

