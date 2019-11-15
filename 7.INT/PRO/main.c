#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "clock.h"
#include "bsp_int.h"

int main(void)
{   
    u8 led_status= 0 ;
    sys_colock_init();  //主频初始化
    int_init();         //中断初始化     
    sys_init();         //打开所有时钟开关
    led_init();         //LED初始化
    beep_init();
    key_init();
    while(1)
    {   
        Switch_Led (led_status);
        led_status = !led_status;
        delay_ms(50);
    }
    return 0;
}