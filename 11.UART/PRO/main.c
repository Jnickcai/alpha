#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "clock.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "epit.h"
#include "key_filter.h"
#include "uart.h"


int main(void)
{   
    unsigned char a;
    int_init();         //中断初始化  
    sys_colock_init();  //主频初始化
    sys_init();         //打开所有时钟开关
    led_init();         //LED初始化
    epit_init(0, 66000000/10);//定时器初始化
    usrt1_init(); //串口初始化
    key_filter_init();  //按键初始化，定时器消抖
    beep_init();
    while(1)
    {   
        Uart_Send_String("请输入一个字符");
        a = Uart_Get_char();
        Uart_Send_String("\r\n");
        Uart_Send_String("输入的字符为：");
        Uart_Send_char(a);
        Uart_Send_String("\r\n");
    }
    return 0;
}