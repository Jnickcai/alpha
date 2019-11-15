#ifndef __BSP_GPIO_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define __BSP_GPIO_H

typedef enum gpio_pin_level
{
    gpio_pin_level_hight    =   1u,
    gpio_pin_level_low      =   0u,
}gpio_pin_level_t;

typedef enum gpio_pin_direction
{
    gpio_pin_input  =   0u,
    gpio_pin_output =   1u,
}gpio_pin_direction_t;

/*描述中断触发类型*/

typedef enum _gpio_intrrupt_mode
{
    Kgpio_nointmode          = 0u,  //无中断
    kgpio_IntLowLevel        = 1u,  //低电平触发
    kgpio_IntHighLevel       = 2u,  //高电平触发
    kgpio_IntRiseingEdge     = 3u,  //上升沿触发
    kgpio_IntfailEgde        = 4u,  //下降沿触发
    kgpio_IntRiseingFailEgde = 5u   //上升沿下降沿触发
}gpio_interrupt_mode_t;

/*GPIO 配置结构体*/
typedef struct gpio_pin_config
{
    gpio_pin_direction_t direction;             //gpio引脚的方向 输入or输出
    gpio_pin_level_t     output_logic;          //如果是输出的话，默认输出电平
    gpio_interrupt_mode_t int_mode;             //中断类型
}gpio_pin_config_t;



void gpio_init(GPIO_Type *GPIO,int pin,gpio_pin_config_t *config);      //初始化GPIO
int gpio_read_pin(GPIO_Type *GPIO,int pin);                 //读取GPIO电平
void gpio_writte_pin(GPIO_Type *GPIO,int pin,gpio_pin_level_t value);   //设置GPIO引脚输出电平
void gpio_enable(GPIO_Type *base,unsigned int pin);         /*使能指定IO中断*/
void gpio_disable(GPIO_Type *base,unsigned int pin);        /*失能指定IO中断*/
void gpio_clearintflags(GPIO_Type *base,unsigned int pin);  /*清除中断标志位*/


#endif //__BSP_GPIO_H