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

void delay_ms(volatile unsigned int n)      //must add volatile ,Prevention of Compiler Optimization 
{
    while(n--)
    {
       volatile unsigned int i = 0x7ff;
        while(i--);
    }
}