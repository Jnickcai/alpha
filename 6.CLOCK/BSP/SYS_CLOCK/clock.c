#include "clock.h"


/*
 * @description : 初始化主频
 * @param : 无
 * @return : 武
 */

void sys_colock_init(void)
{
    //配置主频为528M
    CCM->CCSR   &=    ~(0x01<<8);   //设置step_clk为24M晶振
    CCM->CCSR   |=    (0x01 <<2);   //转换内核时钟为 step_clk

    CCM->CACRR  =0x01;              //设置PPL1 2分频       1052/2=528

    CCM_ANALOG->PLL_ARM  = (CCM_ANALOG->PLL_ARM & 0xffffff80) | 0x58;    //设置PLL1 24M倍频88  0x58
    CCM_ANALOG->PLL_ARM |= (0x01<<13);  //使能时钟输出

    CCM->CCSR   &=    ～(0x01 <<2);   //转换内核时钟为pll_main_clk

    //配置PLL2 4路PFD
    
}