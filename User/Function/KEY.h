#ifndef _KEY_H
#define	_KEY_H
#ifdef __cplusplus
extern "C"{
#endif

#define KEY1_DOWN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0
#define KEY2_DOWN  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)==0
#define KEY3_DOWN  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)==0
#define KEY1_UP  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1
#define KEY2_UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)==1
#define KEY3_UP  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)==1
void KEY_init(void);
#endif 
