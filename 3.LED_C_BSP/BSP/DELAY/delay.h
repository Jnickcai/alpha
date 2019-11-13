#ifndef __DELAY_H

#define __DELAY_H


/*CCM_CCGR regiseter address*/
#define CCM_CCGR0  *((volatile unsigned int*)0X020C4068)
#define CCM_CCGR1  *((volatile unsigned int*)0x020C406C)
#define CCM_CCGR2 *((volatile unsigned int *)0X020C4070)
#define CCM_CCGR3 *((volatile unsigned int *)0X020C4074)
#define CCM_CCGR4 *((volatile unsigned int *)0X020C4078)
#define CCM_CCGR5 *((volatile unsigned int *)0X020C407C)
#define CCM_CCGR6 *((volatile unsigned int *)0X020C4080)


void sys_init(void);

void delay_ms(volatile unsigned int n);


#endif // !__DELAY_H

