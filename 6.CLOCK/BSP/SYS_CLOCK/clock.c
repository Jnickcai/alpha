#include "clock.h"


/*
 * @description : 初始化主频
 * @param : 无
 * @return : wu
 */

void sys_colock_init(void) 
{
    unsigned int reg = 0;  
    //配置主频为528M
    /* 1.2、设置 pll1_main_clk 为 1056MHz,也就是 528*2=1056MHZ,
     * 因为 pll1_sw_clk 进 ARM 内核的时候会被二分频！
     * 配置 CCM_ANLOG->PLL_ARM 寄存器
     * bit13: 1 使能时钟输出
     * bit[6:0]: 88, 由公式：Fout = Fin * div_select / 2.0，
     * 1056=24*div_select/2.0, 得出：div_select=88。*/  

    CCM->CCSR   &=    ~(0x01<<8);   //设置step_clk为24M晶振
    CCM->CCSR   |=    (0x01 <<2);   //转换内核时钟为 step_clk

    CCM->CACRR  =0x00;              //设置PPL1 2分频       1052/2=528       --该处配置为696M

    CCM_ANALOG->PLL_ARM  = (CCM_ANALOG->PLL_ARM & 0xffffff80) | 0x3A;    //设置PLL1 24M倍频88  0x58
    CCM_ANALOG->PLL_ARM |= (0x01<<13);  //使能时钟输出

    CCM->CCSR   &=    ~(0x01 <<2);   //转换内核时钟为pll_main_clk

    //配置PLL2 4路PFD
    reg &= ~(0X3F3F3F3F);  /* 清除原来的设置 */
    reg |= 32<<24; /* PLL2_PFD3=528*18/32=297Mhz */
    reg |= 24<<16; /* PLL2_PFD2=528*18/24=396Mhz */
    reg |= 16<<8; /* PLL2_PFD1=528*18/16=594Mhz */
    reg |= 27<<0; /* PLL2_PFD0=528*18/27=352Mhz */
    CCM_ANALOG->PFD_528=reg; /* 设置 PLL2_PFD0~3 */

    //配置PLL3 4路PFD
    /* 3、设置 PLL3(USB1)各个 PFD */
    reg = 0; /* 清零 */
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0X3F3F3F3F); /* 清除原来的设置 */
    reg |= 19<<24; /* PLL3_PFD3=480*18/19=454.74Mhz */
    reg |= 17<<16; /* PLL3_PFD2=480*18/17=508.24Mhz */
    reg |= 16<<8; /* PLL3_PFD1=480*18/16=540Mhz */
    reg |= 12<<0; /* PLL3_PFD0=480*18/12=720Mhz */
    CCM_ANALOG->PFD_480=reg; /* 设置 PLL3_PFD0~3 */

   /* 4、设置 AHB 时钟 最小 6Mhz， 最大 132Mhz */
    CCM->CBCMR &= ~(3 << 18); /* 清除设置*/
    CCM->CBCMR |= (1 << 18); /* pre_periph_clk=PLL2_PFD2=396MHz */
    CCM->CBCDR &= ~(1 << 25); /* periph_clk=pre_periph_clk=396MHz */
    while(CCM->CDHIPR & (1 << 5));/* 等待握手完成 */
 
    /* 修改 AHB_PODF 位的时候需要先禁止 AHB_CLK_ROOT 的输出，但是
    * 我没有找到关闭 AHB_CLK_ROOT 输出的的寄存器，所以就没法设置。
    * 下面设置 AHB_PODF 的代码仅供学习参考不能直接拿来使用！！
    * 内部 boot rom 将 AHB_PODF 设置为了 3 分频，即使我们不设置 AHB_PODF，
    * AHB_ROOT_CLK 也依旧等于 396/3=132Mhz。
    */
    #if 0

        CCM->CBCDR &= ~(7 << 10);/* CBCDR 的 AHB_PODF 清零 */
        CCM->CBCDR |= 2 << 10; /* AHB_PODF 3 分频，AHB_CLK_ROOT=132MHz */
        while(CCM->CDHIPR & (1 << 1));/* 等待握手完成 */
    #endif

    /* 5、设置 IPG_CLK_ROOT 最小 3Mhz，最大 66Mhz */
    CCM->CBCDR &= ~(3 << 8); /* CBCDR 的 IPG_PODF 清零 */
    CCM->CBCDR |= 1 << 8; /* IPG_PODF 2 分频，IPG_CLK_ROOT=66MHz */

    /* 6、设置 PERCLK_CLK_ROOT 时钟 */
    CCM->CSCMR1 &= ~(1 << 6); /* PERCLK_CLK_ROOT 时钟源为 IPG */
    CCM->CSCMR1 &= ~(7 << 0); /* PERCLK_PODF 位清零，即 1 分频 */

}