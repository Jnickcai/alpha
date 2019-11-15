#include "bsp_int.h"
static unsigned int irq_Nesting ;

/*中断处理函数表*/
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];



/*初始化中断处理函数表*/
void system_irqtable_init(void)
{
    unsigned int i = 0;
    irq_Nesting = 0;
    for (i = 0; i < NUMBER_OF_INT_VECTORS ; i++)
    {
        irqTable[i].irqHandler = default_irqhandler;
        irqTable[i].userparam  = NULL;
    }
}

/*注册中断处理函数*/
void system_register_irqhandler(IRQn_Type irq,system_irphandler_t Irqhander,void *userparam)
{
    irqTable[irq].irqHandler = Irqhander;
    irqTable[irq].userparam  = userparam;
}


/*中断初始化函数*/
void int_init(void)
{
    GIC_Init();
    system_irqtable_init();
    /*中断向量偏移*/
  
}

 /*具体的中断处理函数，IRQ中断会调用此函数*/
void system_irqhandler(unsigned int gicciar)
{
    /*检查中断ID*/
    uint32_t intNum = gicciar & 0x3ff;
    if (intNum >NUMBER_OF_INT_VECTORS)
    {
        return;
    }
    irq_Nesting ++ ;//中断套嵌加一
    /*根据中断ID，读取中断处理函数，然后执行*/
    irqTable[intNum].irqHandler(intNum,irqTable[intNum].userparam);
    irq_Nesting -- ;//中断套嵌减一
}

/*默认中断处理函数*/
void default_irqhandler(unsigned int gicciar,void *userParam)
{

    while(1);
}