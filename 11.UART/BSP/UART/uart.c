#include "uart.h"
#include "bsp_gpio.h"

//初始化uart1波特率为115200；
void usrt1_init(void)
{
   Uart_Io_init() ;//初始化IO
   Uart_Disable(UART1);//关闭串口
   Uart_Restar(UART1); //复位串口


   /*配置UART1*/
   UART1->UCR1 =0;
   UART1 -> UCR1 &= ~(1 << 14);  //关闭波特率自动检测

   /*配置UART1的数据位，停止位，奇偶校验位*/
   UART1-> UCR2 = 0;
   UART1-> UCR2 |=(1<<1) | (1 << 2) | (1 << 5) | (1 << 14);

   UART1-> UCR3 |=(1<<2);

    /* 设置波特率
    * 波特率计算公式:Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
    * 如果要设置波特率为 115200，那么可以使用如下参数:
    * Ref Freq = 80M 也就是寄存器 UFCR 的 bit9:7=101, 表示 1 分频
    * UBMR = 3124
    * UBIR = 71
    * 因此波特率= 80000000/(16 * (3124+1)/(71+1))
    * = 80000000/(16 * 3125/72)
    * = (80000000*72) / (16*3125)
    * = 115200
    */
    UART1->UFCR = 5<<7; /* ref freq 等于 ipg_clk/1=80Mhz */
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

    /*使能串口1*/
    Uart_Enable(UART1);
}

/*关闭UART*/
void Uart_Disable(UART_Type *base)
{
    base->UCR1 &= ~ (1 << 0);
}

/*打开UART*/
void Uart_Enable(UART_Type *base)
{
    base->UCR1 |= (1 << 0);
}


/*复位UART*/
void Uart_Restar(UART_Type *base)
{
    base->UCR2 &= ~(1 << 0);
    while ((base->UCR2 & 0x1) == 0);
}



/*URT1 的IO初始化*/
void Uart_Io_init(void)
{
    {
        IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
        IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0); //复用功能设置

        IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0);
        IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0); //设置电气属
    }
}



/*通过UART 发送一个字符*/

void Uart_Send_char (unsigned char c)
{
    while(((UART1->USR2 >> 3) & 0x01) == 0);
    UART1->UTXD = c;
}

/*通过UART 接收数据*/
unsigned char Uart_Get_char (void)
{
    while(((UART1->USR2) & 0x01) == 0); /*等待有效数据可以读取*/
    return UART1 -> URXD;
}

/*通过串口发送一串字符*/
void Uart_Send_String(char *string)
{
    while(*string)
    {
        Uart_Send_char(*string);
        string ++;
    }
}