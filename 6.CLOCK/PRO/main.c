#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"
#include "key.h"
#include "clock.h"

int main(void)
{   
    u8 led_status= 0 ,key_status = 0;
    u16 volatile i = 0;
    sys_colock_init();  //主频初始化
    sys_init();
    led_init();
    beep_init();
    key_init();
    while(1)
    {   
        key_status =key_getvalue();
        if ( key_status == 1)
        {
             beep_switch(ON); 
           
        }
        else 
        {
            beep_switch(OFF); 
        }
        i++;
        if(i > 10)          //  LED 闪烁  
        {
            Switch_Led (led_status);
            led_status = !led_status;
            i=0;
        }
        delay_ms(50);
    }
    return 0;
}