/**
  ******************************************************************************
  * @file       Delay.c
  * @author  	Qin xingpeng
  * @version 	V1.0
  * @date     	2017年7月27日16:12:08
  * @brief     	配置SysTick进行延时功能
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "include.h"

static u16  fac_us=0;
static u16  fac_ms=0;

/**
 * @brief   Systick延时功能初始化，默认选择72
 * @param  	None
 * @retval	None
 */
void Delay_init(void){
	SysTick->CTRL&=0xfffffffb;
	fac_us=72/8;		    
	fac_ms=(u16)fac_us*1000;
}	

/**
 * @brief   Systick延时功能，延时单位ms
 * @param  	需要延时的时间，最大值1864
 * @retval	None
 */
void Delay_ms(u16 nms){	 		  	  
	u32 temp;	
	if(nms>1800) nms=1800;	
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;           
	do{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));   
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;         	    
} 

/**
 * @brief   Systick延时功能，延时单位us
 * @param  	需要延时的时间，最大值1864
 * @retval	None
 */
void Delay_us(u32 nus){		
	u32 temp;	    	 
	if(nus>1800) nus=1800;
	SysTick->LOAD=nus*fac_us;   		 
	SysTick->VAL=0x00;       
	SysTick->CTRL=0x01 ;     	 
	do{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); 
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;        
}

/******************* (C) COPYRIGHT 2017 Qin xingpeng *****END OF FILE****/
