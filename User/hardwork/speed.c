#include "speed.h"
#include "timer.h"
#include "sys.h"
#include "encoder.h"
#include "delay.h"
#include "bsp_usart.h"
#include "ANO_DT.h"
#include "direction.h"
extern int a;
float	KP =24;//900 1.5
float	KI =3;//0.3
float	KD = 0;
float angle_KP=0;
float angle_Ki=0;
float angle_Kd=0;
int dem1,dem2,dem3,dem4;
extern int Position_A,Position_B,Position_C,Position_D;  //四个电机的位置
extern int error;
int		alimit = 7200;		//
//   电机L1   电机R1
//   电机L2   电机R2
//L1 1
#define L1_1  PEout(0)      //AIN2
#define L1_2  PEout(1)      //AIN1
//R1 2
#define R1_1	PEout(2)      //BIN1
#define R1_2	PGout(10)      //BIN2
//R2 3
#define R2_1	 PGout(0)    //AIN2
#define R2_2	 PGout(1)    //AIN1
//L2 4
#define L2_1	 PGout(2)    //BIN1
#define L2_2   PGout(3)     //BIN2

/*
	L1_1=Ain2=PE1 L1_2=Ain1=PE1  1电机朝正方向转   
	L2_1=Bin1 L2_2=Bin2          2电机朝正方向转
	R1_1=Ain1 R1_2=Ain2          3电机朝正方向转
	R2_1=Bin1 R2_1=Bin2          4电机朝正方向转
*/	

int		duty_max = 7000;	
extern int speed1, speed2, speed3, speed4;
extern int setspeed1, setspeed2, setspeed3, setspeed4;

//电机引脚初始化
void Motor_Init(void)
  {
	GPIO_InitTypeDef GPIO_InitStruct; 
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//开启时钟
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//开启时钟
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStruct);	
		
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);	
  }

//初始化pwm输出和测速
void speed_init(void)
{
	TIM1_PWM_Init(7199,0);
	Motor_Init();
	TIM8_encoder_init();
	Encoder_TIM2_Init();
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();	
}
//增量式PI控制器
int Speed_PID (int Encoder,int Target)	//
{
	static int PWM;
	static float e,le,pe;                 //error; last error上一值 ;  preerror上上一值
	e =Target - Encoder;
	PWM+=KP*(e-le)+KI*e+KD*(e-2*le+pe);   
	if(PWM>6000)PWM=6000;
	if(PWM<-6000)PWM=-6000;      
	le=e;
	pe=le;
	return PWM;
}
//位置式PI控制器
int Position_PID(int now_position,int Target)
{
	static int Pwm_out;
	static int error,last_error,error_add;
	error=Target-now_position;
	error_add+=error;
	error_add=error_add>10000?10000:(error_add<(-10000)?(-10000):error_add);
	Pwm_out=KP*error+KI*error_add+KD*(error-last_error);
	last_error=error;
	return Pwm_out;
}
int Position1_PID(int now_position,int Target)
{
	static int Pwm_out;
	static int error,last_error,error_add;
	error=Target-now_position;
	error_add+=error;
	error_add=error_add>10000?10000:(error_add<(-10000)?(-10000):error_add);
	Pwm_out=KP*error+KI*error_add+KD*(error-last_error);
	last_error=error;
	return Pwm_out;
}
int Position2_PID(int now_position,int Target)
{
	static int Pwm_out;
	static int error,last_error,error_add;
	error=Target-now_position;
	error_add+=error;
	error_add=error_add>10000?10000:(error_add<(-10000)?(-10000):error_add);
	Pwm_out=KP*error+KI*error_add+KD*(error-last_error);
	last_error=error;
	return Pwm_out;
}
int Position3_PID(int now_position,int Target)
{
	static int Pwm_out;
	static int error,last_error,error_add;
	error=Target-now_position;
	error_add+=error;
	error_add=error_add>10000?10000:(error_add<(-10000)?(-10000):error_add);
	Pwm_out=KP*error+KI*error_add+KD*(error-last_error);
	last_error=error;
	return Pwm_out;
}
int Position4_PID(int now_position,int Target)
{
	static int Pwm_out;
	static int error,last_error,error_add;
	error=Target-now_position;
	error_add+=error;
	error_add=error_add>10000?10000:(error_add<(-10000)?(-10000):error_add);
	Pwm_out=KP*error+KI*error_add+KD*(error-last_error);
	last_error=error;
	return Pwm_out;
}
int Angle_PID(int yaw,int target_angle,int A_z)
{
		static float Bias,Last_Bias,Incremental,Integral_bias;
	  Bias=target_angle-yaw;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Incremental=angle_KP*Bias+angle_KP/100*Integral_bias+angle_KP*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Incremental;//返回速度偏差
}


void step_walk(int direc,int velocity, float DS,int track)//前进后退两圈为37.68mm,斜上四圈为37.68mm    188.4mm  一圈脉冲斜着走
{
	static int circle;
	 Position_A=0,Position_B=0,Position_C=0,Position_D=0;
	error=0;
	circle=0;
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	switch(direc)
	{
		case Front:{
					while(1)
					{
						delay_ms(10);
						if(track==0)
							motor_work( velocity, velocity, velocity, velocity);	
						else
							xunji(Front, velocity);
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*2*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Back:{
					while(1)
					{
						delay_ms(10);
						motor_work( -velocity, -velocity,- velocity, -velocity);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*2*1543)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Right:{
					while(1)
					{
						delay_ms(10);
						if(track==0)
							motor_work( velocity, -velocity,-velocity, velocity);	
						else
							xunji(Right, velocity);						
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*2*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Left:{
					while(1)
					{
						delay_ms(10);
						motor_work( -velocity, velocity,velocity, -velocity);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*2*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Left_up:{
					while(1)
					{
						delay_ms(10);
						motor_work( 0,velocity,velocity,0);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/2>DS*2*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		
		case Right_up:{
					while(1)
					{
						delay_ms(10);
						motor_work( velocity,0,0, velocity);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/2>2*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Left_down:{                     //逆时针转向
			
					while(1)
					{
						delay_ms(10);
						motor_work(-velocity,velocity,-velocity, velocity);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
		case Right_down:{                     //1.7是转90度   顺时针转向
					while(1)
					{
						delay_ms(10);
						motor_work( velocity,-velocity,velocity, -velocity);		
						Position_A=GFP_abs(dem1),Position_B=GFP_abs(dem2),Position_C=GFP_abs(dem3),Position_D=GFP_abs(dem4);
						circle=circle+Position_A+Position_B+Position_C+Position_D;
						if(circle/4>DS*1540)
						{
							TIM_CtrlPWMOutputs(TIM1,DISABLE);
							break;
						}
					}
				}break;
	}
}
void motor_work(int target1,int target2,int target3,int target4)
{
//			int dem1,dem2,dem3,dem4;
			dem1=Read_encoder(1);			dem2=Read_encoder(2);			dem3=Read_encoder(3);				dem4=Read_encoder(4);
		  speed1=(dem1*100*60)/1560;   //rad/s *100 rad/min
			speed2=(dem2*100*60)/1560; 
			speed3=(dem3*100*60)/1560; 
			speed4=(dem4*100*60)/1560;
			setspeed1=Position3_PID(speed1,target1);	
			setspeed2=Position4_PID(speed2,target2);	
			setspeed3=Position_PID(speed3,target3);	
			setspeed4=Position2_PID(speed4,target4);	
			speed_control(setspeed1,setspeed2,setspeed3,setspeed4);
			
}
void speed_control(int duty1, int duty2, int duty3, int duty4)
{
	if(duty1 > duty_max)	duty1 = duty_max;
	if(duty1 < -duty_max)	duty1 = -duty_max;
	if(duty2 > duty_max)	duty2 = duty_max;
	if(duty2 < -duty_max)	duty2 = -duty_max;
	if(duty3 > duty_max)	duty3 = duty_max;
	if(duty3 < -duty_max)	duty3 = -duty_max;
	if(duty4 > duty_max)	duty4 = duty_max;
	if(duty4 < -duty_max)	duty4 = -duty_max;
	//////////////////////////////////////////	
	if(duty1 > 0)
	{
		TIM_SetCompare1(TIM1,duty1);
		 L1_1=1; L1_2=0;
	}
	if(duty1 < 0)
	{
		TIM_SetCompare1(TIM1,-duty1);
		L1_1=0; L1_2=1;
	}
	/////////////////////////////////
	if(duty2 > 0)
	{
		TIM_SetCompare2(TIM1,duty2);
		R1_1=1;  R1_2=0;
	}
	if(duty2 < 0)
	{
		TIM_SetCompare2(TIM1,-duty2);
		R1_1=0;  R1_2=1;
	}
	/////////////////////////////////
	if(duty3 > 0)
	{
		TIM_SetCompare3(TIM1,duty3);
		R2_1=1;  R2_2=0;
	}
	if(duty3 < 0)
	{
		TIM_SetCompare3(TIM1,-duty3);
		R2_1=0;  R2_2=1;
	}
	/////////////////////////////////
	if(duty4 > 0)
	{
		TIM_SetCompare4(TIM1,duty4);
		L2_1=0;  L2_2=1;
	}
	if(duty4 < 0)
	{
		TIM_SetCompare4(TIM1,-duty4);
		L2_1=1;  L2_2=0;
	}
}

int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

