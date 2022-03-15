#include "encoder.h"
extern int speed1, speed2, speed3, speed4;

/**********************
编码器
速度读取函数
入口参数：定时器
**********************/
int Read_encoder(int TIMx)
{
	int value_1;
	switch(TIMx)
	{
		case 1:value_1=-(short)TIM_GetCounter(TIM8);TIM_SetCounter(TIM8,0);break;
		case 2:value_1=(short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0);break;
		case 3:value_1=-(short)TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 4:value_1=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;
		default:value_1=0;
	}
	return value_1;
}

	void Get_Motor_Speed(int *speed1,int *speed2, int *speed3,int *speed4)
{  	
	*speed1  = Read_encoder(1);//*1000*200*0.000120830;  
	*speed2  = Read_encoder(2);//*1000*200*0.000120830;
	*speed3 = Read_encoder(3);//*1000*200*0.000120830;  
	*speed4  = Read_encoder(4);//*1000*200*0.000120830;
}

//void Encoder_TIM1_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	TIM_ICInitTypeDef TIM_ICInitStruct;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA8、PA9
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;//|GPIO_Pin_9;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);
//		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
//	GPIO_Init(GPIOE,&GPIO_InitStruct);

//	
//	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period=65535;
//	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
//	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
//	
//	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
//	
//	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
//	TIM_ICInitStruct.TIM_ICFilter=10;
//	TIM_ICInit(TIM1,&TIM_ICInitStruct);
//	
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
//	
//	TIM_SetCounter(TIM1,0);//清零定时器计数值
//	
//	TIM_Cmd(TIM1,ENABLE);//开启定时器
//}
void TIM8_encoder_init(void)
{
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);         
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
	
  TIM_ClearFlag(TIM8, TIM_FLAG_Update);
  TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
 
  TIM_SetCounter(TIM8,0);
  TIM_Cmd(TIM8, ENABLE); 
}
void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA0、PA1
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
	
	TIM_SetCounter(TIM2,0);//清零定时器计数值
	
	TIM_Cmd(TIM2,ENABLE);//开启定时器
}


void Encoder_TIM3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA6、PA7
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
	
	TIM_SetCounter(TIM3,0);//清零定时器计数值
	
	TIM_Cmd(TIM3,ENABLE);//开启定时器
}
void Encoder_TIM4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(TIM4,&TIM_ICInitStruct);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	TIM_SetCounter(TIM4,0);

	TIM_Cmd(TIM4,ENABLE);
}

void TIM8_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
	
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}

