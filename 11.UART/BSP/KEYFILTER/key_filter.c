#include "key_filter.h"
#include "bsp_gpio.h"
#include "epit.h"
#include "bsp_int.h"
#include "beep.h"


/*按键初始化*/

void key_filter_init(void)
{
    gpio_pin_config_t key_config;
    key_config.direction = gpio_pin_input;
    key_config.int_mode = kgpio_IntfailEgde;

    /* 1、初始化 IO */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    gpio_init(GPIO1,18,&key_config);    //初始化GPIO，输出 下降沿触发

    filtertimer_init(0,66000000/100);
    gpio_enable(GPIO1,18);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,(system_irphandler_t)keyfilter_gpio1_16_31_irqhandler,NULL);

}


void filtertimer_init(unsigned int prescalar,unsigned int Load_Value)
{
    if (prescalar > 0xFFF)      //防止分频系数过大
    {
        prescalar = 0xFFF;
    }

    EPIT1->CR = 0; /* 先清零 CR 寄存器 */
    /*
    * CR 寄存器:
    * bit25:24 01 时钟源选择 Peripheral clock=66MHz
    * bit15:4 frac 分频值
    * bit3: 1 当计数器到 0 的话从 LR 重新加载数值
    * bit2: 1 比较中断使能
    * bit1: 1 初始计数值来源于 LR 寄存器值
    * bit0: 0 先关闭 EPIT1
    */
    EPIT1->CR |= (0x01 << 24) | (prescalar << 4) | (0x01 << 3) | (0x01 << 2) | (0x01 << 1) ;
    EPIT1->LR = Load_Value;        /* 加载寄存器值 */
    EPIT1->CMPR = 0;                /* 比较寄存器值 */

    GIC_EnableIRQ(EPIT1_IRQn);      //使能相应中断位

    system_register_irqhandler(EPIT1_IRQn,Irq_Epit1_keyfilter__Hander,NULL);   //注册中断处理函数

}


/*
* @description  : 关闭定时器
* @param : 无
* @return : 无
*/
void filtertimer_stop(void)
{
    EPIT1->CR &= ~(1<<0); /* 关闭定时器 */
}



/*
* @description  : 重启定时器
* @param – value : 定时器 EPIT 计数值
* @return : 无
*/
void filtertimer_restart(unsigned int value)
{
    EPIT1->CR &= ~(1<<0); /* 先关闭定时器 */
    EPIT1->LR = value; /* 计数值 */
    EPIT1->CR |= (1<<0); /* 打开定时器 */
}



void Irq_Epit1_keyfilter__Hander(unsigned int gicciar ,void *param)
{
    static unsigned int beep_status = 0;
    if(EPIT1->SR & (1<<0)) /* 判断比较事件发生 */   
    {   
        filtertimer_stop();         //停止定时器
        if (gpio_read_pin(GPIO1,18) == 0)
        {
            beep_status = !beep_status;
        }
       beep_switch(beep_status);
    }

    EPIT1->SR |= 1<<0; /* 清除中断标志位 */

}


void keyfilter_gpio1_16_31_irqhandler (void)
{
    filtertimer_restart(66000000/100);
    gpio_clearintflags(GPIO1, 18); /* 清除中断标志位 */
}