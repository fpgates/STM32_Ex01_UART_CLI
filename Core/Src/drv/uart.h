#ifndef _UART_H_
#define _UART_H_

#define UART_DEBUG_LEVEL 0

#define UART_RX_BUFFER_SIZE (100)
#define UART_PACKET_SIZE_MAX (100)

typedef enum Uart_Dev_ID_e
{
  UART_HOST_DEBUG = 0,
  UART_HOST_USART2 = 1,
  UART_HOST_MAX = 2
} Uart_Dev_ID_t;

typedef struct Uart_Dev_s
{
  u4_t u4_BASE;
  u4_t u4_IRQ;
  u4_t u4_PacketSize;
} Uart_Dev_t;

bool Uart_GetFifo (Uart_Dev_ID_t t_ID, s1_t *s1p_Data);
s4_t Uart_GetCmdPacket (Uart_Dev_ID_t t_ID, s1_t *s1p_CmdPacket);
void printf_debug_on ();
void printf_debug_off ();
void printf_debug (s1_t *s1p_Format, ...);
void printf_debug_time (s1_t *s1p_Format, ...);
void printf_all (s1_t *s1p_Format, ...);
void printf_ID (Uart_Dev_ID_t t_ID, s1_t *s1p_Format, ...);
void printf_CLI (s1_t *s1p_Format, ...);

#endif/*_UART_H_*/
