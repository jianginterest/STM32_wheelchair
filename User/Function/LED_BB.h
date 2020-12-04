#ifndef __LED_BB_H
#define	__LED_BB_H
#ifdef __cplusplus
extern "C"{
#endif
	
#define IN1_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define IN2_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_7)	
#define IN3_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define IN4_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define IN1_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define IN2_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_7)	
#define IN3_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define IN4_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)
	
void GPIO_init(void);
#endif 
