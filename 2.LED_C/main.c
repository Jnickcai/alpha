#include "main.h"

/*enable all peripheral clock*/
void sys_init(void) 
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;

}

/*initialize led*/
void led_init(void)
{
    /*initialize IO reuse
    configure attribute for IO
    */
    SW_MUX_GPIO1_IO03  = 0x5;
    SW_PAD_GPIO1_IO03  = 0x10b0;
    
    /*Initialize gpio, gpio 1 _ io03 to output*/
    GPIO1_GDIR = 0X0000008;
    /*set LED for low,open led*/
    GPIO1_DR   = 0x0;
}

void led_on(void)
{
    GPIO1_DR &= ~(0x1<<3);
}

void led_off(void)
{
    GPIO1_DR |= (0x1<<3);
}
void delay_ms(volatile unsigned int n)      //must add volatile ,Prevention of Compiler Optimization 
{
    while(n--)
    {
       volatile unsigned int i = 0x7ff;
        while(i--);
    }
}

int main(void)
{
    sys_init();
    led_init();
    while(1)
    {
        led_on();
        delay_ms(100);
        led_off();
        delay_ms(100);
    }

    return 0;
}