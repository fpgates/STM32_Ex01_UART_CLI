#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "usart.h"
#include "../Defines.h"
#include "Uart.h"

static bool mb_Debug_Print_On;

Uart_Dev_t mta_Uart_Dev[] =
  {
    { USART3_BASE, USART3_IRQn, 0 },
    { USART2_BASE, USART2_IRQn, 0 } };

s1_t gs1a_PrintBuff[UART_PACKET_SIZE_MAX] =
  { 0, };

void
Uart_Init ()
{
  MX_USART3_UART_Init ();
}

bool
Uart_GetFifo (Uart_Dev_ID_t t_ID, s1_t *s1p_Data)
{
  USART_TypeDef *t_USART;

  t_USART = (USART_TypeDef*) mta_Uart_Dev[t_ID].u4_BASE;

  if(t_USART->SR & USART_SR_RXNE_Msk) // Read Data Register Not Empty
  {
    *s1p_Data = t_USART->DR;
    return true;
  }

  return false;
}

s4_t
Uart_GetCmdPacket (Uart_Dev_ID_t t_ID, s1_t *s1p_CmdPacket)
{
  s1_t s1_Data = 0;
  u4_t u4_PacketSize;

  if(!Uart_GetFifo (t_ID, &s1_Data))
    return 0;

  u4_PacketSize = mta_Uart_Dev[t_ID].u4_PacketSize;

//	if((s1_Data >= '0' && s1_Data <='9') || (s1_Data >= 'a' && s1_Data <= 'z')
//		|| (s1_Data >= 'A' && s1_Data <= 'Z') || s1_Data == '-'  || s1_Data == '+'
//		|| s1_Data == ' ' || s1_Data == '_' || s1_Data == '#')
  if(s1_Data >= ' ' && s1_Data <= '}')
  {
    s1p_CmdPacket[u4_PacketSize] = s1_Data;
    u4_PacketSize++;
    if(u4_PacketSize > UART_PACKET_SIZE_MAX - 2)
      u4_PacketSize = UART_PACKET_SIZE_MAX - 2;
    mta_Uart_Dev[t_ID].u4_PacketSize = u4_PacketSize;
    return 0;
  }
  else if(s1_Data == '\n' || s1_Data == '\r')
  {
#if UART_DEBUG_LEVEL > 0
		printf_usb("[%d] Packet Size: %d\n\r", u1_Handle, u4_PacketSize);
#endif
    mta_Uart_Dev[t_ID].u4_PacketSize = 0;
    return u4_PacketSize;
  }
  else if(s1_Data == 0x08) //BS
  {
    if(u4_PacketSize != 0)
    {
      u4_PacketSize--;
      s1p_CmdPacket[u4_PacketSize] = 0;
    }
    mta_Uart_Dev[t_ID].u4_PacketSize = u4_PacketSize;
    return 0;
  }
  else
    return 0;
}

void
Uart_Inner_Print (Uart_Dev_ID_t t_ID, char *buf)
{

  int cnt;
  int len;
  len = strlen (buf);
  USART_TypeDef *t_USART;

  t_USART = (USART_TypeDef*) mta_Uart_Dev[t_ID].u4_BASE;

  for(cnt = 0; cnt < len; cnt++)
  {
    while(1)
    {
      if((t_USART->SR & USART_SR_TXE_Msk) && (t_USART->SR & USART_SR_TC_Msk))
      { //Transmit Data Register Empty && Transmission Complete
        t_USART->DR = buf[cnt];
        break;
      }
    }
  }
}

void
printf_debug_on ()
{
  mb_Debug_Print_On = true;
}

void
printf_debug_off ()
{
  mb_Debug_Print_On = false;
}

void
printf_debug (s1_t *s1p_Format, ...)
{
  __gnuc_va_list arglist;

  if(mb_Debug_Print_On == false)
    return;

  va_start(arglist, s1p_Format);
  vsprintf (gs1a_PrintBuff, s1p_Format, arglist);
  va_end(arglist);

  Uart_Inner_Print (UART_HOST_DEBUG, gs1a_PrintBuff);
}

void
printf_debug_time (s1_t *s1p_Format, ...)
{
  __gnuc_va_list arglist;

  if(mb_Debug_Print_On == false)
    return;

//	printf_debug("[%d]", times(NULL));
  printf_debug ("[%d]", HAL_GetTick ());

  va_start(arglist, s1p_Format);
  vsprintf (gs1a_PrintBuff, s1p_Format, arglist);
  va_end(arglist);

  Uart_Inner_Print (UART_HOST_DEBUG, gs1a_PrintBuff);
}

void
printf_all (s1_t *s1p_Format, ...)
{
  __gnuc_va_list arglist;

  va_start(arglist, s1p_Format);
  vsprintf (gs1a_PrintBuff, s1p_Format, arglist);
  va_end(arglist);

  Uart_Inner_Print (UART_HOST_DEBUG, gs1a_PrintBuff);
  Uart_Inner_Print (UART_HOST_USART2, gs1a_PrintBuff);
}

void
printf_ID (Uart_Dev_ID_t t_ID, s1_t *s1p_Format, ...)
{
  __gnuc_va_list arglist;

  va_start(arglist, s1p_Format);
  vsprintf (gs1a_PrintBuff, s1p_Format, arglist);
  va_end(arglist);

  if(t_ID == UART_HOST_DEBUG)
    Uart_Inner_Print (UART_HOST_DEBUG, gs1a_PrintBuff);
  if(t_ID == UART_HOST_USART2)
    Uart_Inner_Print (UART_HOST_USART2, gs1a_PrintBuff);
}

void
printf_CLI (s1_t *s1p_Format, ...)
{
  __gnuc_va_list arglist;

  va_start(arglist, s1p_Format);
  vsprintf (gs1a_PrintBuff, s1p_Format, arglist);
  va_end(arglist);

  Uart_Inner_Print (UART_HOST_DEBUG, gs1a_PrintBuff);
}
