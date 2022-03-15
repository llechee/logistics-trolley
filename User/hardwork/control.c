#include "control.h" 
#include "num.h"
#include "sys.h"
#include "hand.h"
#include "bsp_usart5.h"
#include "hand_block.h"
#include "oled.h"
extern int gm65_flag;
extern int demo; 
extern int Qr1,Qr2;
extern u8 Qr_up[3],Qr_down[3];
extern u8 color1[3], color2[3];
extern u8 qr_up_test[3],qr_down_test[3];
extern u8 color1_test[3], color2_test[3];
void move_step()
{
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	while(1)
	{
		delay_ms(10);
		xunji(Front,60);
		if(xunjiD_1==1)
		{
			break;
		}
	}
	
	TIM_CtrlPWMOutputs(TIM1,DISABLE);
}
	
//void Init_all(void)
//{
//	delay_init();
//	Motor_Init();
//	speed_init();
//  road_init( );
//	
//	IIC_Init();//IIC初始化
//  pca_write(pca_mode1,0x0);//写地址
//	pca_setfreq(330);//写舵机频率，模拟电机给50HZ，数字电机330HZ
//	
////	USART_Config();
////	USART2_Init() ;
//	
//	GPIO_init();
//}
//void  main_control_1()
//{	
//	
//	move(Left,2,100,80);
//	move(Front,2,100,80);
//	delay_ms(200);
//	get_qrcode();
//	move(Front,4,100,80);
//	get_position1(); 
//	
//	
//	
//	rank_catch(Qr_up,color1,0,1);
//	rank_catch(Qr_up,color1,1,1);
//	rank_catch(Qr_up,color1,2,1);
//	
//	rough_position(Qr_up);
//	half_position();
//	
////	get_qrcode();                //扫描二维码，扫到之后二维码的数据已经存在 Qr_up[3],Qr_down[3]
////  get_position1();              //获得上层物块的位置，数据储存在pos1中
//}
void  main_control_2()
{	
	  huizhong1();
		delay_ms(1000);
		delay_ms(1000);
		step_walk(Front,100,0.796/2,0);
		delay_ms(100);
	  move(Left,2,110,80);
		delay_ms(100);
		move(Front,1,130,80);
		step_walk(Front,80,0.4,1);
		while(gm65_flag!=1)
		{
		}
			
			OLED_work();
		rank_position( Qr1,Qr_up);
		rank_position( Qr2,Qr_down);
		delay_ms(1000);
		move(Front,3,130,80);
		delay_ms(100);
		move(Front,1,70,80);
		delay_ms(100);
	step_walk(Right,70,0.76,1);
		delay_ms(100);
// 第一次抓取
	rank_catch(Qr_up,color1_test,0,1);
	rank_catch(Qr_up,color1_test,1,1);
	rank_catch(Qr_up,color1_test,2,1);
	move(Left,3,100,80);
	delay_ms(200);
	step_walk(Front,70,0.65,1);
	delay_ms(100);
	huizhong2();
	delay_ms(100);
// 粗加工区
	rough_position(Qr_up);
	move(Back,3,100,80);
	delay_ms(200);
	step_walk(Left_down,80, 1.7,0);
	move(Front,1,110,110);
	move(Front,1,80,80);
	step_walk(Front,70,0.57,0);
//半成品区
	huizhong2();
  half_position(Qr_up);
	delay_ms(200);
	move(Back,2,100,80);
	delay_ms(200);
  step_walk(Right_down,80, 3.4,0);
	delay_ms(200);



//move(Front,3,100,80);
//	delay_ms(200);
//	move(Left,2,100,80);

//	step_walk(Front,60,0.55,1);
//			
//	rank_catch(qr_up_test,color1_test,0,2);
//	rank_catch(qr_up_test,color1_test,1,2);
//	rank_catch(qr_up_test,color1_test,2,2);


//	move(Back,1,100,80);
//	step_walk(Left_down,80, 1.7,0);
//	move(Left,2	,100,80);
//	
//	
//	delay_ms(200);
//	step_walk(Front,70,0.65,1);
//	delay_ms(100);
//	huizhong2();
//	delay_ms(100);
//// 粗加工区
//	rough_position(Qr_up);
//	move(Back,3,100,80);
//	delay_ms(200);
//	step_walk(Left_down,80, 1.7,0);
//	move(Front,1,110,110);
//	move(Front,1,80,80);
//	step_walk(Front,70,0.57,0);
////半成品区
//	huizhong2();
//  half_position(Qr_up);
//	delay_ms(200);
//	move(Back,1,100,80);
//	move(Left,3,100,80);
//	delay_ms(200);












//		move(Left,3,100,80);
//		delay_ms(200);
//		move(Front,1,100,80);
//		delay_ms(200);
//	
//		move(Back,2,100,80);
//		delay_ms(200);
//		move(Left,2,100,80);
//		delay_ms(200);
//		move(Back,4,100,80);
	
//	rank_catch(qr_up_test,color1_test,0,2);
//	rank_catch(qr_up_test,color1_test,1,2);
//	rank_catch(qr_up_test,color1_test,2,2);
	
	
}








