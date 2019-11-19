#ifndef __UART_H
#define __UART_H


#include "imx6ull.h"


void usrt1_init(void); //串口初始化
void Uart_Io_init(void);//初始化IO
void Uart_Disable(UART_Type *base);
void Uart_Enable(UART_Type *base);
void Uart_Restar(UART_Type *base);
void Uart_Send_char (unsigned char c);  /*通过UART 发送一个字符*/
unsigned char Uart_Get_char (void);  /*通过UART 接收数据*/
void Uart_Send_String(char *string);   /*通过串口发送一串字符*/

#endif // !__UART_H
