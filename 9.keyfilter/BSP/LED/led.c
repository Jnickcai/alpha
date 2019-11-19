#include "led.h"



/*initialize led*/
void led_init(void)
{
    
    /* 1、初始化 IO 复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /* 2、、配置 GPIO1_IO03 的 IO 属性
    *bit 16:0 HYS 关闭
    *bit [15:14]: 00 默认下拉
    *bit [13]: 0 kepper 功能
    *bit [12]: 1 pull/keeper 使能
    *bit [11]: 0 关闭开路输出
    *bit [7:6]: 10 速度 100Mhz
    *bit [5:3]: 110 R0/6 驱动能力
    *bit [0]: 0 低转换率
    */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    /* 3、初始化 GPIO,设置 GPIO1_IO03 设置为输出 */
    GPIO1->GDIR |= (1 << 3);

    /* 4、设置 GPIO1_IO03 输出高电平，关闭 LED0 */
    GPIO1->DR|= (0x1<<3);

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
            GPIO1->DR &= ~(0x1<<3);
            break;
        case OFF:
            GPIO1->DR|= (0x1<<3);
            break;
        default:
            break;
}

}

