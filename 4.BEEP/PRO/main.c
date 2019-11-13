#include "main.h"
#include "led.h"
#include "delay.h"



int main(void)
{
    sys_init();
    led_init();
    while(1)
    {
        Switch_Led (ON);
        delay_ms(500);
        Switch_Led (OFF);
        delay_ms(500);
    }
    return 0;
}