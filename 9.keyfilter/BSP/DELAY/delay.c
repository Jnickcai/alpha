#include "delay.h"


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


void delay_init()
{
    GPT1->CR  = 0;   //清零
    GPT1->CR |= (1<<15);
    while((GPT1->CR >> 15) & 0x01);
    GPT1->CR |=(1<<6);
    GPT1->PR |= (65<<0);
    //GPT1->OCR[0] = 0XFFFFFFFF;
    GPT1->CR |= 1<<0; /* 使能 GPT1 */
}


void delay_us(unsigned int delay_us)
{
    unsigned long new_cnt = 0 , old_cnt = 0;
    unsigned long tcntvalue = 0; /* 走过的总时间 */

    old_cnt = GPT1->CNT;    //CNT寄存器中的值
    while(1)
    {
        new_cnt = GPT1->CNT;      //需要延时的值
        if (new_cnt != old_cnt)
        {
            if(new_cnt > old_cnt)   //无溢出
                tcntvalue += new_cnt - old_cnt;
            else                    //有溢出
                tcntvalue += (0xffffffff - old_cnt) + new_cnt;
            old_cnt = new_cnt;
            if (tcntvalue > delay_us)       //延时时间到
                break;
            
        }
    }

}


void delay_ms(volatile unsigned int n)      //must add volatile ,Prevention of Compiler Optimization 
{
    while(n--)
    {
       delay_us(1000);
    }
}


/*
* @description : 短时间延时函数
* @param - n : 要延时循环次数(空操作循环次数，模式延时)
* @return : 无
*/
void delay_short(volatile unsigned int n)
{
    while(n--){}
}