#include "include.h"
static void TIM2_GPIO_Config(void) //1,2,3,4tunnel
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//fuyongshizhong
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}



static void TIM2_Mode_Config(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
 	
 
  TIM_TimeBaseStructure.TIM_Period = 999;      
  TIM_TimeBaseStructure.TIM_Prescaler = 71;	    
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;//   pid占空比	   
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;	//0   
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	/********************************left*************************************/
	
	
	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;//       pid占空比	
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;//0	
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);	
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);			

	/********************************right*************************************/
	
	
	
  TIM_Cmd(TIM2, ENABLE);                   
}


void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}



/********************************反转将通道一二或三四交换占空比*************************************/
	

