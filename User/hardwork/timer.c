#include "timer.h"

////*************��ʱ��3 PWM��ʼ��**********************
////***************************************************
//A6,A7,B0,B1 ��·
//void TIM3_PWM_Init_1(u16 arr,u16 psc)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����
//	  
//   //���ø�����Ϊ�����������,���TIM3 ��PWM���岨��	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM_CH1&2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //TIM_CH3&4
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
// 
//   //��ʼ��TIM3
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//	//��ʼ��TIM3 Channel PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//	
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC3
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4

//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
//}

//******* ******��ʱ��8 PWM��ʼ��**********************
//***************************************************
//void TIM8_PWM_Init(u16 arr,u16 psc)
//{  
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    TIM_OCInitTypeDef  TIM_OCInitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// ʹ�ܶ�ʱ��8ʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  ////ʹ��GPIO����
//	
//		//���ø�����Ϊ�����������,���TIM8��PWM���岨��	
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//		//��ʼ��TIM8
//    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ//
//    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ////TIM���ϼ���ģʽ
//    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////�Ƚ����ʹ��
//    TIM_OCInitStructure.TIM_Pulse = 0; //
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; ////�������:TIM����Ƚϼ��Ը�
//		
//		
//    TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
//		TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
//		TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
//		TIM_OC4Init(TIM8, &TIM_OCInitStructure); 

//    TIM_CtrlPWMOutputs(TIM8,ENABLE);  //
//    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  // 
//		TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
//		TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  // 
//		TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
//    TIM_ARRPreloadConfig(TIM8, ENABLE); //
//    TIM_Cmd(TIM8, ENABLE);  //
//}
void TIM1_PWM_Init(u16 arr,u16 psc)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// ʹ�ܶ�ʱ��8ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  ////ʹ��GPIO����
	
		//���ø�����Ϊ�����������,���TIM8��PWM���岨��	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//��ʼ��TIM8
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ//
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ////TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; ////�������:TIM����Ƚϼ��Ը�
		
		
    TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
		TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
		TIM_OC3Init(TIM1, &TIM_OCInitStructure); 
		TIM_OC4Init(TIM1, &TIM_OCInitStructure); 

    TIM_CtrlPWMOutputs(TIM1,ENABLE);  //
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  // 
		TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  // 
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE); //
    TIM_Cmd(TIM1, ENABLE);  //
}



