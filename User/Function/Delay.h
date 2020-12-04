/**
  ******************************************************************************
  * @file       Delay,h
  * @author  	Qin xingpeng
  * @version 	V1.0
  * @date     	2017��7��27��16:15:47
  * @brief     	��ʱ�������ýӿ�
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef DELAY_H
#define	DELAY_H

#ifdef __cplusplus
extern "C"{
#endif
	
#include "include.h"
	
void Delay_init(void);
void Delay_ms(u16 nms);
void Delay_us(u32 nus);
	
	
#endif

/******************* (C) COPYRIGHT 2017 Qin xingpeng *****END OF FILE****/
