#include "stm32f10x.h" 
//#include "hand_block.h"
#include "GM65.h"
#include "bsp_usart.h"
#include "speed.h"
#include "timer.h"
#include "road.h"
#include "direction.h"
#include "num.h"
#include "oled.h"
#include "delay.h"
#include "exti.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "ANO_DT.h"
#include "BasicTim.h"
#include "encoder.h"
#include "pca9685.h"
#include "myiic.h"
#include "hand.h"
#include "bsp_usart5.h"
#include "hand_block.h"
unsigned int data[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};		//段
unsigned int wei[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};					//位
int speed1, speed2, speed3, speed4;               //四个电机的速度
int setspeed1, setspeed2, setspeed3, setspeed4;   //四个电机的目标速度
int Position_A,Position_B,Position_C,Position_D;  //四个电机的位置
int target_speed;  
//int targetA, targetB, targetC, targetD;//电机目标速度
int speed;
int flag,time;
int num_res ,error;
float Pitch,Roll,Yaw;
extern int dem1,dem2,dem3,dem4;
extern unsigned int Rec_time ;
extern int get_qr_flag ;
extern unsigned int get_position1_flag ;	
extern unsigned int get_position2_flag;
extern int Qr1,Qr2;
extern u8 Qr_up[3],Qr_down[3];
extern u8 color1[3], color2[3];
int i;
int gm65_flag=0;

u8 qr_up_test[3]={3,2,1},qr_down_test[3];
u8 color1_test[3]={2,1,3}, color2_test[3];

int main(void)
{
	delay_init();
	Motor_Init();
	speed_init();
  road_init( );
	
  IIC_Init();//IIC初始化	··
  pca_write(pca_mode1,0x0);//写地址
	pca_setfreq(330);//写舵机频率，模拟电机给50HZ，数字电机330HZ
  USART3_Config();
	
	uart5_init(9600);
	USART2_Init() ;
	GPIO_init();
	pca_setpwm(4,0,130);
	delay_ms(1000);

	delay_ms(1000);
	
	OLED_Init();
catch_zhong3();
//		 huizhong2();
//	put_down3();
// catch_left2();
//	delay_ms(100);

	
//	while(gm65_flag!=1)
//	{
//	}
//	printf("22");
//	OLED_work();//oled显示调用

	
//	
//	 huizhong1();
//	rank_catch(qr_up_test,color1_test,0,1);
//	catch_left1();
////	 catch_zhong1();
//  catch_down33();
	

//	 catch_right1();
//catch_right_down1();
//	rough_position(qr_up_test);
//	USART_SendData(USART2,1);
//pca_setpwm(4,0,115);
//	while(1)
//	{
//	}
//			clamp (1);
//			law_grand1(Right);
// rank_lay(qr_up_test);
//		main_control_2();
 // rank_lay_higher(qr_up_test);
			//delay_ms(1000);
//	move_step();
//		delay_ms(1000);
// put_down2();
//	
//	main_control_1();
//	move(Front,1,50,80 );
//		delay_ms(1000);
//	while(gm65_flag!=1)
//		delay_ms(1000);
//	if(Qr1==132)
//	{
//		move(Left,2,80,80 );
//	}
//	printf()
//	get_qrcode();
//	Rec_time =2;
//	get_position2();
//	printf("%d",Qr_down[1]);
//	printf("%d",color2[1]);
	
//	while(gm65_flag!=1);
//	printf("%d",Qr1);
//	printf("+");
//	printf("%d",Qr2);
		
//	xunji(FR,int speed)
//	delay_ms(1000);
//	move(Left,2,80,80 );
//	Adjusting_posture(); 
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
	
//	while(1)
//	{
//		
//		if(xunjiA_7==1)
//		{
//			
//		}
//	}
	
//	move(Front,6,130,100 );
//		delay_ms(1000);
//	move(Right,1,130,100 );
//	delay_ms(1000);
//	move(Left,3,130,100 );
//	  delay_ms(1000);
//		move(Front,1,130,100 );
//		delay_ms(1000);
//		move(Back,2,130,100 );
//				delay_ms(1000);
//		move(Left,2,130,100 );
//		delay_ms(1000);
//	move(Front,1,130,100 );
//		delay_ms(1000);
//			move(Right,5,130,100 );
//	Adjusting_posture(); 
//	
//	USART_SendData(USART3,'6');
//	catch(Right,1);
// law_out(3,1);

//	rank_catch(Qr_down,color2,1,0);
//while(1)
//{
//	 printf("%d",Qr1);
////	 lay_down_r_2();
//		delay_ms(10000);
//	 lay_down2();
//		printf("%d",Qr1);
//		motor_work(-100,100,100,-100);
//		printf("%d",dem1);
//		Send_User(dem1,speed1, 0,0,0)	;
//		xunji(Front,100);
//		xuanzhuan(Right, 2000);
//		pingyi(Left,2000);
//}	







//		start();
//		delay_ms(1000);
//		delay_ms(1000);
//	step_walk(Left_up,50,0.85 );

//	step_walk(Right,60,4,1 );
//		delay_ms(1000);
//		get_qrcode();
//	while(1)
//	{
//		 QR_show();
//	}



//		step_walk(Back,50,0.43 );
//		move(Left,3,60,50 );
//	first_catch_from_grand();
//	catch_zhong2();
//	 first_catch_from_grand();
//		step_walk(Left,50,0.35 );
//	step_walk(Front,50,0.5 );
//	  first_lay_out();
//	step_walk(Left,50,0.45 );
//	step_walk(Front,50,0.6 );
//	//move(Left,2,80,50 );
//	move(Front,1,80,50 );
	
//		 look_up_position();


//	 start();
//		delay_ms(1000);
//		delay_ms(1000);
//	step_walk(Left_up,50,0.85 );
//		step_walk(Front,60,2.28/2 );
//		delay_ms(1000);
	//	get_qrcode();
//		delay_ms(1000);
//		move(Front,1,100,50 );

//		delay_ms(1000);
//		step_walk(Left,60,0.2);
//		move(Left,1,80,60 );
//		delay_ms(1000);
//		step_walk(Front,60,0.4);
//		move(Front,2,100,60 );
//		 look_up_position();
//		delay_ms(1000);
////		get_position1();
//		delay_ms(1000);
//		step_walk(Right,60,0.75 );
//		delay_ms(1000);
//		step_walk(Back,20,0.1 );
//	  rank_catch(Qr_up,color1,0);
//		rank_catch(Qr_up,color1,1);
//		rank_catch(Qr_up,color1,2);
//    move(Left,2,80,50 );
////		   delay_ms(1000);
//			 step_walk(Front,50,0.2 );
//	 move(Front,1,80,50 );
//	    delay_ms(1000);
//	 step_walk(Left,50,0.35 );
//	 step_walk(Front,50,0.5 );
//   delay_ms(1000);
//	  first_lay_out();
//   delay_ms(1000);
//	 first_catch_from_grand();
//		step_walk(Back,50,0.43 );
//		move(Left,3,60,50 );
//    delay_ms(1000);
//		step_walk(Back,50,0.38 );
//		step_walk(Left,50,0.6 );
//     second_lay_out();
//		step_walk(Back,50,0.38 );
//		delay_ms(1000);
//		step_walk(Right,50,0.6 ); 
//		move(Back,4,80,50 );
		
		



//		move(Left,6,60,50 );


//	catch_left_up();
//	delay_ms(1000);
//	law_out(1);
//	get_qrcode();
//	while(1)
//	{
//		QR_show();
//	}
//	step_walk(Left_up,50,0.85 );
//	delay_ms(1000);
//	move(Front,2,80,50 );
//	delay_ms(1000);
//	move(Left,2,80,50 );
//	delay_ms(1000);
//	move(Front,3,80,50 );
//	delay_ms(1000);
//	step_walk(Right,50,1.38/2 );

//	look_qr();
//	look_up_position();
	//	pca_setpwm(0,0,45+90);
//		pca_setpwm(1,0,45);
//		pca_setpwm(2,0,35);
//		pca_setpwm(3,0,110);
//		delay_ms(1000);
//		delay_ms(1000);
//	step_walk(Left_up,50,0.85 );
//	  delay_ms(1000);
	
//	get_qrcode();
//	printf("%d",Qr_up[0]);
//	printf("%d",Qr_up[1]);
//	printf("%d",Qr_up[2]);

//	USART_SendData(USART2,1);
//	while(1)
//	{
//		if(get_qr_flag==4)
//		{
//		   delay_ms(100);
//			 break;
//		}
//		delay_ms(100);
//		printf("666");
//	}

//		while(get_qr_flag!=4);
//		printf("11");
//		Rec_time =1;
//		USART_SendData(USART2,3);
//		delay_ms(100);
//		get_position1();      
		
	
//	  rank_catch(Qr_up,color1,0);
//    rank_catch(Qr_up,color1,1);
//		rank_catch(Qr_up,color1,2);
//		for( i=0;i<3;i++)
//		{
//			printf("%d",Qr_up[i]);
//		}
//		while(1);
//		}
//	
//	printf("%d",Rec_time);
//	USART_SendData(USART2,2);
//	}
//	get_qr();
//		move(Front, 1,50,50);
//	delay_ms(1000);
//	move(Left, 3,50,50);
////		step_walk(Left,50,0.796 );
////	delay_ms(1000);
//		delay_ms(1000);
//	move(Front, 4,50,50);
//		delay_ms(1000);
//  move(Right, 2,50,50);
//	step_walk(Left_up,50,0.85 );
//	delay_ms(100);
//	step_walk(Front,60,1.54 );
//	delay_ms(100);
//	step_walk(Left,50,0.796 );
//	delay_ms(100);
//	step_walk(Front,60,1.592 );
//	delay_ms(100);
//	step_walk(Right,50,0.796 );
//	delay_ms(100);
//	step_walk(Front,60,1.592 );
//	delay_ms(100);
//	step_walk(Left,50,0.796*3*2 );
//	delay_ms(10000);
//	step_walk(Left,50,0.796*2 );
//	delay_ms(100);
//	step_walk(Back,50,0.796*2 );
//  	move(Right, 2,100,50 );
//	delay_ms(1000);
//	move(Left, 1,50,50 );
//	Adjusting_posture();
//	    IIC_Init();//IIC初始化
//      pca_write(pca_mode1,0x0);//写地址
//			pca_setfreq(330);//写舵机频率，模拟电机给50HZ，数字电机330HZ
//			while(1)
//			{
				/*数值计算步骤：
				脉冲时间0.5ms-2.5ms(占空比5%-12.5%),频率330HZ（周期3.03ms），分辨率4096      //2704
				0°，0.5/3.03*4096=675
				90°，1.5/3.03*4096=2017
				180°，2.5/3.03*4096=3379
				*/
//				delay_ms(1000);
//	while(1)
//	{
//		huizhong();
//		delay_ms(1000);
//		  catch_down();
		

//		pca_setpwm(0,0,50);
//		pca_setpwm(1,0,60);
//		pca_setpwm(2,0,70);
//		pca_setpwm(3,0,170);
//		delay_ms(100);
//		pca_setpwm(0,0,0);

//				for(j=50;j<230;j++)//0路舵机，先回正，然后旋转90°（回正是瞬间动作）
//				{
//					pca_setpwm(0,0,j);//旋转90°
//					delay_ms(30);//从0°到180°增长时缓慢增长，易于看到效果
//				}
//	}
////	BASIC_TIM_Init();
//	LED_GPIO_Config();
	

	
	
//	
//	while(1)
//  {

//			if(xunjiA_5==1)
//			{
//				delay_ms(10);
//				motor_work(0,50,50,50);
//				
//			}
//	}
//			time = 0;
//			LED1_TOGGLE; 
//			Send_User(dem1,dem2,dem3,dem4,speed3);		
//		}	
//			delay_ms(1000);
//		printf("111");
//			xunji(Right,70);
//		move(Front, 1,80,80 );	
//		motor_work(-100,100,100,-100);
	

}

 

