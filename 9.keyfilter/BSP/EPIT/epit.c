#include "epit.h"
#include "bsp_int.h"
#include "led.h"


void epit_init(unsigned int prescalar,unsigned int Load_Value)
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

    system_register_irqhandler(EPIT1_IRQn,Irq_Epit1_Hander,NULL);   //注册中断处理函数

    EPIT1->CR |= (0x01 << 0);        //使能EPIT1中断

}

void Irq_Epit1_Hander(unsigned int gicciar ,void *param)
{

    static unsigned int Led_status = 0;

    Led_status = !Led_status ;
    if(EPIT1->SR & (1<<0)) /* 判断比较事件发生 */   
    {
        Switch_Led (Led_status); /* 定时器周期到，反转 LED */
    }

    EPIT1->SR |= 1<<0; /* 清除中断标志位 */

}