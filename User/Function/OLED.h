/**
  ******************************************************************************
  * @file       OLED.h
  * @author  	Qin xingpeng
  * @date     	2017年8月11日01:49:06
  * @brief     	OLED.h
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef OLED_H
#define OLED_H

#ifdef __cplusplus
extern "C"{
#endif
	
#include "include.h"

#define OLED_GPIO    GPIOB
#define OLED_RCCEN   RCC_APB2Periph_GPIOB
#define OLED_SCL     GPIO_Pin_13   
#define OLED_SDA     GPIO_Pin_15      
#define OLED_RST     GPIO_Pin_12   
#define OLED_DC      GPIO_Pin_11     

#define OLED_D0_OL		GPIO_ResetBits(GPIOB, OLED_SCL)	
#define OLED_D0_OH		GPIO_SetBits(GPIOB, OLED_SCL)  	

#define OLED_D1_OL		GPIO_ResetBits(GPIOB, OLED_SDA)	
#define OLED_D1_OH		GPIO_SetBits(GPIOB, OLED_SDA) 	

#define OLED_RST_OL		GPIO_ResetBits(GPIOA, OLED_RST)	
#define OLED_RST_OH		GPIO_SetBits(GPIOA, OLED_RST) 	

#define OLED_DC_OL		GPIO_ResetBits(GPIOA, OLED_DC)	
#define OLED_DC_OH		GPIO_SetBits(GPIOA, OLED_DC) 	 

void OLED_init(void);
void OLED_Display_Clear(void);
void OLED_Display_Char(u8 x,u8 y,u8 asc);
void OLED_Display_Str(u8 x,u8 y,u8 asc[]);
void OLED_Display_Num(u8 x,u8 y,double Number,u8 N1,u8 N2);

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void OLED_Draw_Signal(uint8_t status);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_Draw_Battery(float Battery_Level);
	
void OLED_Display_Symbol(void);
void OLED_Display_Num2(uint8_t x, uint8_t y, uint16_t num);
void OLED_Display_Str2(u8 x,u8 y,u8 asc[]);

extern uint16_t Signal_Value;  //用于表示信号个数的全局变量

#ifdef __cplusplus
}
#endif

#endif
/******************* (C) COPYRIGHT 2017 Qin xingpeng *****END OF FILE****/
