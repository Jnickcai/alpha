#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"
#include "key.h"

int main(void)
{   
    u8 led_status= 0 ,key_status = 0;
    u16 volatile i = 0;
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
        if(i > 10)
        {
            Switch_Led (led_status);
            if(led_status == 0 )    led_status = 1;
            else                    led_status = 0;
            i=0;
        }
        delay_ms(50);
    }
    return 0;
}