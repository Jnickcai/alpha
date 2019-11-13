#include "key.h"
#include "delay.h"
#include "bsp_gpio.h"

void key_init()
{
    gpio_pin_config_t key_config;

/* 1、初始化 IO 复用, 复用为 GPIO1_IO18 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);

/* 2、、配置 UART1_CTS_B 的 IO 属性
*bit 16:0 HYS 关闭
*bit [15:14]: 11 默认 22K 上拉
*bit [13]: 1 pull 功能
*bit [12]: 1 pull/keeper 使能
*bit [11]: 0 关闭开路输出
*bit [7:6]: 10 速度 100Mhz
*bit [5:3]: 000 关闭输出
*bit [0]: 0 低转换率
*/
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
    key_config.direction = gpio_pin_input;
    gpio_init(GPIO1,18,&key_config);
}


/*
 * @description : 获取按键值
 * @param : 无
 * @return : 0 没有按键按下，其他值:对应的按键值
 */
 int key_getvalue(void)
 {
    int ret = 0;
    //static unsigned char release = 1; /* 按键松开 */

    if(gpio_read_pin(GPIO1, 18) == 0) /* KEY0 按下 */
    {
        delay_ms(10); /* 延时消抖  */
    //    release = 0; /* 标记按键按下 */
        if(gpio_read_pin(GPIO1, 18) == 0)
        ret = KEY0_VALUE;
    }
    else if(gpio_read_pin(GPIO1, 18) == 1) /* KEY0 未按下 */
    {
        ret = 0;
        //release = 1; /* 标记按键释放 */
    }
    return ret;
}