#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "sys.h" 
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
int Read_encoder(int TIMx);
void TIM8_encoder_init(void);
void Encoder_TIM2_Init(void);
void Encoder_TIM3_Init(void);
void Encoder_TIM4_Init(void);
void Get_Motor_Speed(int *speed1,int *speed2, int *speed3,int *speed4);
#endif


