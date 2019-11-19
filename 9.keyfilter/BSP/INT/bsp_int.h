#ifndef __BSP_INT_H

#define __BSP_INT_H
#include "imx6ull.h"

typedef void (*system_irphandler_t)(unsigned int gicciar ,void *param);   //定义一个函数指针


/*中断处理函数结构体*/
typedef struct _sys_irp_handle
{

    system_irphandler_t irqHandler;
    void *userparam;
}sys_irq_handle_t;



void int_init(void);                 /*定义一个中断处理函数*/

void system_register_irqhandler(IRQn_Type irq,system_irphandler_t Irqhander,void *userparam);   /*注册中断处理函数*/

void system_irqtable_init(void);    /*初始化中断处理函数表*/

void system_irqhandler();           /*具体的中断处理函数，IRQ中断会调用此函数*/

void default_irqhandler(unsigned int gicciar,void *userParam); /*默认中断处理函数*/


#endif // !



