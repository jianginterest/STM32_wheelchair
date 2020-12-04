/**
  ******************************************************************************
  * @file    LED_BB.c
  * @author  zhangsu
  * @version V1.0
  * @date    2017-08-02
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  */

#include "include.h"
#include "LED_BB.h"
/**
  * @brief  初始化函数
  * @param  PB10 低电平亮
  * @retval 无
  */

void GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}
