/**
  ******************************************************************************
  * @file    LED_BB.c
  * @author  zhangsu
  * @version V1.0
  * @date    2017-08-02
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  */

#include "include.h"
#include "LED_BB.h"
/**
  * @brief  ��ʼ������
  * @param  PB10 �͵�ƽ��
  * @retval ��
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
