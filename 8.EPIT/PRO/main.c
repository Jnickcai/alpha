#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "clock.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "epit.h"


int main(void)
{   
    int_init();         //中断初始化  
    sys_colock_init();  //主频初始化
    exit_init();   
    sys_init();         //打开所有时钟开关
    epit_init(0, 66000000/2);//定时器初始化
    led_init();         //LED初始化
    beep_init();
    while(1)
    {   
        delay_ms(500);
    }
    return 0;
}