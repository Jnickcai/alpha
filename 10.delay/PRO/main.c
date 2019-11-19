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


int main(void)
{   
    unsigned int led_status = 0;
    int_init();         //中断初始化  
    sys_colock_init();  //主频初始化
    sys_init();         //打开所有时钟开关
    delay_init();       //延时初始化
    key_filter_init();  //按键初始化，定时器消抖
    led_init();         //LED初始化
    beep_init();
    while(1)
    {   
        Switch_Led (led_status);
        led_status = !led_status;
        delay_ms(100);
    }
    return 0;
}