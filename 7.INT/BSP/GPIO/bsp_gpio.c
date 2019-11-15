#include "bsp_gpio.h"


/*
* @description : 初始化GPIO pin引脚 。
* @param – GPIO : 要初始化的 GPIO 组。
* @param - pin : 要初始化的 GPIO 脚号。
* @param - config : PIn引脚方向（input or output）  默认电平。
* @return : 无
*/

void gpio_init(GPIO_Type *GPIO,int pin,gpio_pin_config_t *config)
{
    if (config->direction == gpio_pin_input)
    {
        GPIO->GDIR &= ~(1<<pin);  
    } 
    else
    {
        GPIO->GDIR |= 1<<pin;  /*设置为输出 */
        gpio_writte_pin(GPIO,pin,config->output_logic);
    }  
}


/*
* @description : 读取指定 GPIO 的电平值 。
* @param – GPIO : 要读取的 GPIO 组。
* @param - pin : 要读取的 GPIO 脚号。
* @return : 无
*/
int gpio_read_pin(GPIO_Type *GPIO,int pin)
{
    return ((GPIO->DR & (1<<pin))>>pin);       
}


/*
* @description : 设置 GPIO 的电平值 。
* @param – GPIO : 要设置的 GPIO 组。
* @param - pin : 要设置的 GPIO 脚号。
* @param - value : 要设置的电平。       gpio_pin_level_hight    =   1u,  
                                        gpio_pin_level_low      =   0u,
* @return : 无
*/
void gpio_writte_pin(GPIO_Type *GPIO,int pin,gpio_pin_level_t value)
{
    if (value == gpio_pin_level_hight )
    {
        GPIO->DR |= (0x01 << pin);  /*设置输出为高*/
    }
    else
    {
        GPIO->DR &= ~(0x01 << pin);/* 设置输出为低电平 */
    }
    
        
}

/*使能指定IO中断*/

void gpio_enable(GPIO_Type *base,unsigned int pin)
{
    base->IMR |=(1 << pin);
}


/*失能指定IO中断*/

void gpio_disable(GPIO_Type *base,unsigned int pin)
{
    base->IMR &=~(1 << pin);
}

/*清除中断标志位*/
void gpio_clearintflags(GPIO_Type *base,unsigned int pin)
{
    base->ISR |= (1 << pin);
}

/*GPIO中断初始化函数*/
void gpio_intconfig(GPIO_Type *base,unsigned int pin,gpio_interrupt_mode_t pin_int_mode)
{
    volatile uint32_t *icr;
    uint32_t icrShift;

    icrShift = pin;
    base -> EDGE_SEL &= ~(1 << pin);

    if (pin < 16)
    {
        icr = &(base -> ICR1);
    }
    else
    {
        icr = &(base -> ICR2);
        icrShift -=16;
    }
    switch (pin_int_mode)
    {
        case kgpio_IntLowLevel :
            icr &= ~
        break;

        default:
        break;
    }
    
}
