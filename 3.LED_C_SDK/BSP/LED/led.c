#include "led.h"


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
/*
*Control the led0 switch.
* @param - status : 0，关闭 LED0，1 打开 LED0
* @return : 无
*/
void Switch_Led (int status)
{
    switch (status)
{       
        case ON:
            GPIO1_DR &= ~(0x1<<3);
            break;
        case OFF:
            GPIO1_DR |= (0x1<<3);
            break;
        default:
            break;
}

}

