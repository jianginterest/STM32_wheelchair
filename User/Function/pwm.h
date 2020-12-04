#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H
#ifdef __cplusplus
extern "C"{
#endif
#include "include.h"

void TIM2_PWM_Init(void);
void straight(u16 duty1,u16 duty2);
void left(u16 duty3,u16 duty4);
void right(u16 duty5,u16 duty6);
#endif 
