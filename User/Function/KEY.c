/**
  ******************************************************************************
  * @file    KEY.c
  * @author  zhangsu
  * @version V1.0
  * @date    2017-08-02
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  */
#include "include.h"
#include "KEY.h"

/**
  * @brief  ��������
  * @param  ��
  * @retval ��
  */
void KEY_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��·�Ѿ�����
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14| GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��·�Ѿ�����
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
