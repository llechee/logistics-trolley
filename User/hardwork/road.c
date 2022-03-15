#include "direction.h" 
#include "speed.h"
#include "road.h"
#include "math.h"
#include "sys.h"
#include "delay.h"
#include "num.h"
extern int setspeed1, setspeed2, setspeed3, setspeed4;
extern int speed1, speed2, speed3, speed4;
extern u8 flag;
extern int error;
extern int speed;
 void road_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//PD
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入	
	//PF
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_14;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	//PG
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_9|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	//PB
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PD
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void move(int direc, u8 step_num,int norspeed,int lastpeed )
{
	static int i = 0,j=0;
	static int step = 0;
	static u8 ans = 0; //上一次的状态
  static  int set;
	u8 sign, aim, mark = 0;
	error=0;
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	i=0;
	j=0;
	while(1)
	{		
		if(i<500)
			i=i+1;		
		delay_ms(10);           //每10msPID运算一次，否则电机会失控
		if(j==0)	
		{
			set= norspeed;
		}
			switch(direc)
			{
				case Front:
				{
					aim = step_num;
					sign =xunjiD_4;
					xunji(Front,set);
					if(step==step_num-1)       //边沿检测系统，如果快达到目的地，急速减速减小惯性误差
					{
						if(xunjiD_1==1)
						{
							set=30;
							j=1;
						}
					}
					break;
				}
//////////////////////////////////////
				case Back:
				{
					aim = step_num;
					sign =xunjiB_4;
					xunji(Back,set);
					if(step==step_num-1)     
					{
						if(xunjiB_7==1)
							set=30;
								j=1;
					}					
					break;
				}
//////////////////////////////////////
				case Left:
				{
					aim = step_num;
					sign = xunjiA_4;
					xunji(Left,set);
					if(step==step_num-1)    
					{
						if(xunjiA_1==1)
						{
							set=30;
							j=1;
						}
					}
					break;
				}
//////////////////////////////////////
				case Right:
				{
					aim =step_num;
					sign = xunjiA_4;
					xunji(Right,set);
					if(step==step_num-1)    
					{
						if(xunjiA_7==1)
							set=30;
								j=1;
					}
					break;
				}
			}
///////////////////
///////////////////
			if(sign == 1 && ans ==0)
			{
				if(i>40)
					step += 1;
				if(step == aim)
					mark = 1;
			}
	
				ans = sign;
		if(mark == 1)
		{
			ans = untouch;
			step = 0;	
			TIM_CtrlPWMOutputs(TIM1,DISABLE);
			break;
		}
	}
}
/*
//       1 2 3 4 5 6 7

				1							1
				2							2
				3							3
				4							4
				5							5
				6							6
				7							7
//          1 2 3 4
*/
void xunji(int direc,int speed)
{ 
	switch(direc)
	{
		case Front:
			if((xunjiA_3==1&&xunjiA_4==0)||(xunjiA_3==1))//||(xunjiC_3==1&&xunjiA_3==1)                   //101 顺时针
				error=-15;
			if((xunjiA_5==1&&xunjiA_4==0)||(xunjiA_5==1))//(xunjiC_2==1&&xunjiA_5==1)
				error=15;
			if(xunjiA_1==1||xunjiA_2==1)
				error=-25;
			if(xunjiA_6==1||xunjiA_7==1)
				error=25;
			if(xunjiA_3==0&&xunjiA_4==1&&xunjiA_5==0)
				error=0;
			motor_work(speed+error, speed-error, speed+error, speed-error);break;			
		case Back:
			if((xunjiC_3==1&&xunjiA_4==1)||(xunjiC_3==1&&xunjiA_3==1))                //顺时针
				error=15;
			if((xunjiC_2==1&&xunjiA_4==1)||(xunjiC_2==1&&xunjiA_5==1))                //逆时针
				error=-15;
			if(xunjiC_2==0&&xunjiC_3==0)
				error=0;
/*        大转弯     */	
			if(xunjiC_4==1)																																						//顺时针
				error=25;
			if(xunjiC_1==1)																																						//逆时针
				error=-25;
			motor_work(-speed-error,-speed+error,-speed-error,-speed+error);break;    

			
/*       1 2 3 4 5 6 7
				1							1
				2							2
				3							3
				4							4
				5							5
				6							6
				7							7
          1 2 3 4
*/
		case Right:
			if((xunjiB_5==1&&xunjiB_4==0)||(xunjiD_4==1&&xunjiB_5==1)||(xunjiB_5==1&&xunjiD_3==1))    //逆时钟偏
				error=15;
			if((xunjiB_4==0&&xunjiB_3==1)||(xunjiD_4==1&&xunjiB_3==1)||(xunjiD_5==1&&xunjiB_3==1))     //顺时钟偏
				error=-15;
			if(xunjiB_6==1||xunjiD_2==1)
				error=25;
			if(xunjiB_2==1||xunjiD_6==1)
				error=-25;
			if(xunjiB_3==0&&xunjiB_4==1&&xunjiB_5==0)
				error=0;
			motor_work( speed+error,-speed-error,-speed+error,speed-error);break;
		case Left:
			if((xunjiD_5==1&&xunjiD_4==0)||(xunjiD_5==1&&xunjiB_4==0)||(xunjiD_5==1))//&&xunjiB_3==1))    //顺
				error=15;
			if((xunjiD_3==1&&xunjiD_4==0)||(xunjiD_3==1&&xunjiB_4==0)||(xunjiD_3==1))//&&xunjiB_5==1))     //逆
				error=-15;
			if(xunjiD_6==1||xunjiD_7==1)
				error=25;
			if(xunjiD_2==1||xunjiD_1==1)
				error=-25;
			
			
//			if(xunjiD_6==1||(xunjiB_2==1&&xunjiD_2==0)||xunjiD_7==1)
//				error=25;
//			if(xunjiD_2==1||(xunjiB_6==1&&xunjiD_6==0)||xunjiD_1==1)
//				error=-25;
			if(xunjiD_3==0&&xunjiD_4==1&&xunjiD_5==0)
				error=0;
			if((xunjiD_3==0&&xunjiD_4==1)||(xunjiD_5==0&&xunjiD_4==1))
				 error=0;
			motor_work(-speed-error, speed+error,speed-error, -speed+error); break;
	}
}
/*       1 2 3 4 5 6 7

				1							1
				2							2
				3							3
				4							4
				5							5
				6							6
				7							7
           1  2  3  4
*/
void Adjusting_posture(void)
{
		TIM_CtrlPWMOutputs(TIM1,ENABLE);
	while(1)
	{
			
		if((xunjiA_3==1&&xunjiC_4==1)||(xunjiA_3==1&&xunjiC_3==1))      //前后
			xuanzhuan(Left,1500);
		if((xunjiA_5==1&&xunjiC_2==1)||(xunjiA_5==1&&xunjiC_1==1))      //前后
			xuanzhuan(Right,1500);
		if((xunjiA_5==1&&xunjiC_3==1)||(xunjiA_6==1&&xunjiC_4==1)||(xunjiA_5==1&&xunjiC_4==1))
			pingyi(Right,2000);
		if((xunjiA_3==1&&xunjiC_2==1)||(xunjiA_2==1&&xunjiC_1==1))
			pingyi(Left,2000);
		
		
		if((xunjiB_3==1&&xunjiD_3==1))
			pingyi(Front,1500);
		if((xunjiB_2==1&&xunjiD_2==1)||(xunjiB_1==1&&xunjiD_1==1))
			pingyi(Front,2000);
		if((xunjiB_5==1&&xunjiD_5==1))
			pingyi(Back,1500);
		if((xunjiB_6==1&&xunjiD_6==1)||(xunjiB_7==1&&xunjiD_7==1))
			pingyi(Back,2000);
		if((xunjiB_3==1&&xunjiD_5==1))      
			xuanzhuan(Left,2000);
		if((xunjiB_5==1&&xunjiD_3==1))      
			xuanzhuan(Right,2000);
		
//		if(xunji2==1&&xunji5==1)
//			pingyi(Right,1500);
//		if(xunji3==1&&xunji8==1)
//			pingyi(Front,1500);
//		if(xunji4==1&&xunji7==1)
//			pingyi(Back,1500);
//		if((xunji1==1&&xunji2==0&&xunji5==0&&xunji6==0)||(xunji1==0&&xunji2==0&&xunji5==1&&xunji6==0))
//			xuanzhuan(Left,2000);
//		if((xunji1==0&&xunji2==1&&xunji5==0&&xunji6==0)||(xunji1==0&&xunji2==0&&xunji5==0&&xunji6==1))
//			xuanzhuan(Right,2000);
//		if((xunji1==1&&xunji5==1)||(xunji3==1&&xunji7==1))
//			xuanzhuan(Left,2500);
//		if((xunji2==1&&xunji6==1)||(xunji4==1&&xunji8==1))
//			xuanzhuan(Right,2500);
//		
		if(xunjiA_4==1&&xunjiB_4==1&&xunjiD_4==1)
		{
			TIM_CtrlPWMOutputs(TIM1,DISABLE);
			break;
		}
//		
	}
}

	//	if((xunjiA_3==0&&xunjiA_4==1&&xunjiA_5==0)&&(xunjiB_3==0&&xunjiB_4==1&&xunjiB_5==0)&&(xunjiC_1==0&&xunjiC_2==0&&xunjiC_3==0&&xunjiC_4==0)&&(xunjiD_3==0&&xunjiD_4==1&&xunjiD_5==0))
	//	{


