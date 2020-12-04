/**
  ******************************************************************************
  * @file       Usart.c
  * @author  	Yufan Jiang
  * @version 	V1.0
  * @date     	2020年
  * @brief     	配置板载串口功能
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "include.h"
 
/**
 * @brief   初始化串口1 端口为 TX PB6   RX PB70,波特率115200,并打开串口中断
			中断服务函数位于 stm32f10x_it.c 
 * @param  	None
 * @retval	None
 */
void Usart_init(void){
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/*. 串口时钟使能,串口是挂载在 APB2 下面的外设*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE); //使能重映射

	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

/**
 * @brief   重映射串口到Printf来使用串口发送功能
 * @param  	None
 * @retval	None
 */

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE{
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}
  return ch;
}

/******************* (C) COPYRIGHT 2020 Yufan Jiang *****END OF FILE****/
