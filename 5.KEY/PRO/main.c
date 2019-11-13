#include "main.h"
#include "led.h"
#include "delay.h"
#include "beep.h"


int main(void)
{
    sys_init();
    led_init();
    beep_init();
    while(1)
    {
        Switch_Led (ON);
        beep_switch(ON);
        delay_ms(500);
        beep_switch(OFF);
        Switch_Led (OFF);
        delay_ms(1000);
    }
    return 0;
}