#include "bsp_gpio.h"


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

int gpio_read_pin(GPIO_Type *GPIO,int pin)
{
    return (GPIO->DR &= 1<<pin)>>pin;       
}

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