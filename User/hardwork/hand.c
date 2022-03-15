#include "direction.h"
#include "timer.h"
#include "hand.h"
#include "road.h"
#include "bsp_usart.h"
#include "speed.h"
extern int RxBuffer1[5];   //读取的二维码
extern int RxBuffer2[7];   // RxBuffer1[2-3]red，RxBuffer1[4-5]green,RxBuffer1[6-7]blue
int code;

u8 color1[3], color2[3];      //color[0]表示左位置，color[1]表示中位置，color[2]表示右位置   值为123任组，1表示red,2表示green,3表示blue
u8 Qr_up[3],Qr_down[3];
u8 qr_code[3];
extern int pos1;
//brief: 传进参数为二维码获取顺序，二维码抓取数组Qr_up[3],Qr_down[3]，其中【0】表示第一次抓的颜色，以此类推
//第一个抓取的位置放在color1[0]里面依次类推   
//获得的位置不变，主要是二维码
void rank_position (int Qr,uint8_t *qr_code)
{
	if(Qr==123)
	{
		qr_code[0]=1;qr_code[1]=2;qr_code[2]=3;
	}
	if(Qr==132)
	{
		qr_code[0]=1;qr_code[1]=3;qr_code[2]=2;
	}
	if(Qr==213)
	{
		qr_code[0]=2;qr_code[1]=1;qr_code[2]=3;
	}
	if(Qr==231)
	{
		qr_code[0]=2;qr_code[1]=3;qr_code[2]=1;
	}
	if(Qr==312)
	{	
		qr_code[0]=3;qr_code[1]=1;qr_code[2]=2;
	}
	if(Qr==321)
	{
		qr_code[0]=3;qr_code[1]=2;qr_code[2]=1;
	}
}
//brief:排序抓取函数
//解释：扫描二维码收到两组抓取次序，每次传入一组次序。两传入数组都为三个字节，
//color[0]表示左位置，color[1]表示中位置，color[2]表示右位置
//红色表示1，2表示绿色3表示蓝色,
//每抓一次上层 用三次
void rank_catch(uint8_t *qr_code,uint8_t *color,int time,int num)  //time从0开始 ，num从1开始
{
	if(color[0]==qr_code[0+time])
	{
			catch( Left,num);
			printf("left");
	}
	else if(color[1]==qr_code[0+time])
	{
		catch( Middle,num);
			printf("middle");
	}
	else if(color[2]==qr_code[0+time])
	{
		catch( Right,num);
		printf("Right");
	}
	delay_ms(100);
	if(qr_code[0+time]==1)    //第一次从原料区上层放，第二次从下层相当于从粗加工区放
		law_out(1,num);
	if(qr_code[0+time]==2)
		law_out(2,num);
	if(qr_code[0+time]==3)
		law_out(3,num);	
}

void look_qr(void)
{
	pca_setpwm(0,0,50);
	pca_setpwm(1,0,60);
	pca_setpwm(2,0,15);
	pca_setpwm(3,0,70);
//	pca_setpwm(4,0,0);
}
void look_up_position(void)
{
		pca_setpwm(0,0,45);
		pca_setpwm(1,0,45);
		pca_setpwm(2,0,35);
		pca_setpwm(3,0,110);
  	pca_setpwm(4,0,140);
}
//往粗加工区放
void law_grand1(int direc)    
{
	switch(direc)  
	{
		case Left:
		{
			put_left2();
			 break;
		}
		case Middle:
		{ 
			put_zhong2();
			 break;
		}
		case Right:
		{
			 put_right2();
			 break;
		}
	}
}

//往半成品区放
void law_grand2(int direc)    
{
	switch(direc)  
	{
		case Left:
		{
			catch_left3();
			 break;
		}
		case Middle:
		{ 
			catch_zhong3();
			 break;
		}
		case Right:
		{
			 catch_right3();
			 break;
		}
	}
}




//往货架上放  1表示从原料区往货架上方  2表示从粗加工区往货架上放   从下层抓取放货架重复了
void law_out(int direc,int time)    
{
	switch(direc)  //
	{
		case 1:
		{
			if(time==1)
				catch_down11();
			else
				catch_down1();
			 break;
		}
		case 2:
		{
			if(time==1)
			  catch_down22();
			else
				catch_down2();
			 break;
		}
		case 3:
		{
			if(time==1)
				catch_down33();
			else
				catch_down3();
			 break;
		}
	}
}
//抓取上层和抓下层动作
int catch(int direc,int time) 
{
	switch(direc)  //
	{
		case Left:
		{
			if(time==1)
				 catch_left1();
			else
				catch_left_down1();		 
	//		catch_left_up();
			break;
		}
		case Middle:
		{
			if(time==1)
			  catch_zhong1();
			else
				catch_zhong_down1();
//			catch_zhong_up();
			break;
		}
		case Right:
		{
			if(time==1)
				catch_right1();
			else
				catch_right_down1();
//			catch_right_up();
			break;
		}
	}
	return 0;
}

//从货架上抓取  1表示红色 以及红色货架的位置
void clamp (int direc)   
{
	switch(direc)  
	{
		case 1:
		{
			put_down1();
			 break;
		}
		case 2:
		{
			put_down2();
			 break;
		}
		case 3:
		{
			put_down3();
			break;
		}
	}
}






void huizhong1()   //第一次抓
{
		pca_setpwm(0,0,50);
		pca_setpwm(1,0,60);
	  pca_setpwm(2,0,70);			
	 	pca_setpwm(3,0,110);
}

void huizhong2()   //第2
{
	pca_setpwm(0,0,140);
	pca_setpwm(1,0,60);
	pca_setpwm(2,0,70);			
	pca_setpwm(3,0,110);
}

void huizhong3()  //第2
{
		pca_setpwm(0,0,225);
		pca_setpwm(1,0,60);
		pca_setpwm(2,0,70);			
		pca_setpwm(3,0,110);
}
void start()
{
		pca_setpwm(0,0,50);
		pca_setpwm(1,0,80);
	  pca_setpwm(2,0,30);		
	 	pca_setpwm(3,0,80);
  	pca_setpwm(4,0,140);
}

void guodu()
{
	static int i;
	for(i=0;i<30;i++)
	{
		pca_setpwm(0,0,145-31.5*i);
	}
}

//      抓第一层

void  catch_left1()
{
	static int i,k;
	pca_setpwm(4,0,30);	
	for( i=0;i<30;i++)  
		{
			pca_setpwm(0,0,50+i);	
			if(i<20)
				delay_ms(5);
			if(i>20)
				delay_ms(12);
			
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+2.65*i);
			pca_setpwm(2,0,70+i);
			pca_setpwm(3,0,110-0.3*i);
			if(i<10)
				delay_ms(12);
			if(i>10)
				delay_ms(25);			
		}
			delay_ms(400);
		pca_setpwm(4,0,125);
		delay_ms(400);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,113-2.65*k);
			pca_setpwm(2,0,90-k);
			pca_setpwm(3,0,101+0.3*i);
			if(k<10)
				delay_ms(12);
			if(k>10)
				delay_ms(22);			
		}
	for( i=0;i<37;i++)  
		{
			pca_setpwm(0,0,87-i);
			if(i<20)
				delay_ms(8);
			if(i>20)
				delay_ms(15);		
		}
}


void  catch_zhong1()
{
	static int i,k;
	
		pca_setpwm(4,0,30);
		for( i=0;i<45;i++)  
		{		
//			pca_setpwm(0,0,130-3.6*i);
			pca_setpwm(0,0,50);
			pca_setpwm(1,0,60+0.73*i);
			pca_setpwm(2,0,70);
			pca_setpwm(3,0,110-0.2*i);
			delay_ms(9);
		}
		delay_ms(300);
		pca_setpwm(4,0,125);
		delay_ms(300);
		for( k=0;k<45;k++)
		{
//			pca_setpwm(0,0,50+3.6*k);
			pca_setpwm(0,0,50);
			pca_setpwm(1,0,93-0.73*k);
			pca_setpwm(2,0,70);
			pca_setpwm(3,0,101+0.2*i);
			delay_ms(6);			
		}
}
void  catch_right1()
{
	static int i,k;
	pca_setpwm(4,0,30);	
	for( i=0;i<27;i++)  
		{
			pca_setpwm(0,0,50-i);
			if(i<20)
				delay_ms(8);
			if(i>20)
				delay_ms(15);
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+2.65*i);
			pca_setpwm(2,0,70+i);
			pca_setpwm(3,0,110-0.45*i);
			delay_ms(20);			
		}
			delay_ms(500);
		pca_setpwm(4,0,125);
		delay_ms(300);
		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,113-2.65*k);
			pca_setpwm(2,0,90-k);
			pca_setpwm(3,0,101+0.45*i);
			delay_ms(20);			
		}
	for( i=0;i<27;i++)  
		{
			pca_setpwm(0,0,23+i);
			if(i<20)
				delay_ms(8);
			if(i>20)
				delay_ms(20);
				
		}
}













void  catch_down11()
{
	static int i,j;
	pca_setpwm(0,0,50);
	pca_setpwm(1,0,60);
	pca_setpwm(2,0,70);			
	pca_setpwm(3,0,110);
	pca_setpwm(4,0,125);
		for( i=0;i<20;i++)  
		{
		 pca_setpwm(0,0,40-2*i);	 
			delay_ms(15);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+j);	
		pca_setpwm(2,0,65+j);			
	 	pca_setpwm(3,0,110+4.95*j);	 
		if(j<15)
			delay_ms(15);
		if(j>15)
			delay_ms(20);
			
		}	

		delay_ms(820);
		pca_setpwm(4,0,30);
		delay_ms(800);
//			for( j=0;j<20;j++)  
//		{
//		pca_setpwm(2,0,90-j);			
//	 	pca_setpwm(3,0,215-0.75*j);	 
//			delay_ms(30);
//		}
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,80-j);
		pca_setpwm(2,0,85-j);
	 	pca_setpwm(3,0,194-4.95*j);	 
			delay_ms(30);
		}	
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,10+2*i);	 
			delay_ms(15);
		}	
		
}



void  catch_down22()
{
	
	static int i,j;
	pca_setpwm(4,0,125);
		for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,50+4.8*i);	 
			delay_ms(15);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+0.5*j);
	  pca_setpwm(2,0,70+6.5*j);			
	 	pca_setpwm(3,0,110-5.5*j);	 
			delay_ms(30);
		}	
		delay_ms(800);
		pca_setpwm(4,0,30);
		delay_ms(800);
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,70-0.5*j);
	  pca_setpwm(2,0,200-6.5*j);			
	 	pca_setpwm(3,0,0+5.5*j);
		if(j<15)
			delay_ms(30);
		if(j>15)
			delay_ms(40);		
		}	
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,140-4.5*i);	 
		if(i<15)
			delay_ms(23);
		if(i>15)
			delay_ms(55);
		}	
			
}
void  catch_down33()
{
	static int i,j;
	pca_setpwm(4,0,130);
		for( i=0;i<25;i++)  
		{
		pca_setpwm(0,0,50+2.2*i);	 
			delay_ms(15);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+0.5*j);
	  pca_setpwm(2,0,70+6.5*j);			
	 	pca_setpwm(3,0,110-5.2*j);	 
		if(j<15)
			delay_ms(20);
		if(j>15)
			delay_ms(30);
		}	
		delay_ms(800);
		pca_setpwm(4,0,30);
		delay_ms(800);
//		for( j=0;j<20;j++)  
//		{
//		pca_setpwm(1,0,70-0.5*j);
//	  pca_setpwm(2,0,200-6.5*j);			
//	 	pca_setpwm(3,0,0+5.5*j);	 
//		if(j<15)
//			delay_ms(35);
//		if(j>15)
//			delay_ms(50);
//		}	
//		for( i=0;i<25;i++)  
//		{
//			pca_setpwm(0,0,100-2*i);	 
//			delay_ms(15);
//		}	
}




//      粗加工区


void put_down1(void)  //从货架上抓
{
	
	static int i,j;
pca_setpwm(0,0,140);
pca_setpwm(1,0,60);
pca_setpwm(2,0,70);			
pca_setpwm(3,0,110);
pca_setpwm(4,0,60);
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,130-6.5*i);	 
			delay_ms(15);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+j);	
		pca_setpwm(2,0,65+j);			
	 	pca_setpwm(3,0,110+5.25*j);	 
			delay_ms(25);
		}	
		for( j=0;j<20;j++)  
		{	
		pca_setpwm(2,0,90-j);			
	 	pca_setpwm(3,0,215-0.95*j);	 
			delay_ms(20);
		}	
		delay_ms(200);
		pca_setpwm(4,0,135);
		delay_ms(200);
			for( j=0;j<20;j++)  
		{	
		pca_setpwm(2,0,70+j);			
	 	pca_setpwm(3,0,196+0.95*j);	 
			delay_ms(10);

		
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,80-j);
		pca_setpwm(2,0,90-1.25*j);
	 	pca_setpwm(3,0,215-6*j);	 
			delay_ms(30);
			
		}	
		for( i=0;i<60;i++)  
		{
		pca_setpwm(0,0,0+2*i);	 
			delay_ms(5);
		}	
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,120+i);	 

			if(i<15)
			delay_ms(10);
		if(i>15)
			delay_ms(25);
			
		}		
		
}
void  put_down2(void)
{
	static int j;
		pca_setpwm(0,0,140);
	pca_setpwm(4,0,70);
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+1.3*j);
	  pca_setpwm(2,0,70+7.5*j);			
	 	pca_setpwm(3,0,110-4.8*j);	 

		if(j<15)
			delay_ms(25);
		if(j>15)
			delay_ms(40);
		
		}	
		delay_ms(400);
		pca_setpwm(4,0,135);
		delay_ms(400);
		
			for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,70);
	  pca_setpwm(2,0,200-0.75*j);			
	 	pca_setpwm(3,0,5-0.25*j); 
			delay_ms(10);
		}
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,70-0.5*j);
	  pca_setpwm(2,0,185-5.8*j);			
	 	pca_setpwm(3,0,0+5.25*j);	 
		if(j<15)
			delay_ms(30);
		if(j>15)
			delay_ms(45);
		
		}	
	pca_setpwm(0,0,140);
			
}

void  put_down3(void)
{
	static int i,j;
	pca_setpwm(4,0,60);
		for( i=0;i<40;i++)  
		{
		pca_setpwm(0,0,140-i);	 
			delay_ms(8);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+0.5*j);
	  pca_setpwm(2,0,70+6.8*j);			
	 	pca_setpwm(3,0,110-5*j);	 
			delay_ms(20);
		if(j<15)
			delay_ms(10);
		if(j>15)
			delay_ms(22);
		}	
		delay_ms(300);
		pca_setpwm(4,0,135);
		delay_ms(300);
				for( j=0;j<20;j++)  
		{

	  pca_setpwm(2,0,200-0.75*j);			
	 	pca_setpwm(3,0,12-0.5*j);	 
		if(j<15)
			delay_ms(12);
		if(j>15)
			delay_ms(20);
	
		}
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,70-0.5*j);
	  pca_setpwm(2,0,185-5.75*j);			
	 	pca_setpwm(3,0,3+5.5*j);	 
		if(j<15)
			delay_ms(12);
		if(j>15)
			delay_ms(22);

		}	
		for( i=0;i<40;i++)  
		{
		pca_setpwm(0,0,100+i);	 
			delay_ms(15);
		}	
}


void  put_zhong2()
{
	static int i,k;

		for( i=0;i<45;i++)  
		{		
					pca_setpwm(4,0,135);
			pca_setpwm(0,0,140);
			pca_setpwm(1,0,60+1.89*i);
			pca_setpwm(2,0,70-0.33*i);
			pca_setpwm(3,0,110-1.33*i);
			if(i<30)
				delay_ms(10);
		  if(i>30)
				delay_ms(25);
				
		}
		delay_ms(400);
		pca_setpwm(4,0,30);
		delay_ms(400);
		for( k=0;k<45;k++)
		{
			pca_setpwm(0,0,140);
			pca_setpwm(1,0,145-1.89*k);
			pca_setpwm(2,0,55+0.33*k);
			pca_setpwm(3,0,50+1.33*k);

		  if(k>38)
				delay_ms(10);		
		}
}
void  put_right2()
{
	static int i,k;
	pca_setpwm(4,0,145);	
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,140-i);
				delay_ms(6);
		}
			for( i=0;i<26;i++)  
		{
			pca_setpwm(0,0,120-0.5*i);
			delay_ms(15);			
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+5*i);
			pca_setpwm(2,0,70+0.5*i);
			pca_setpwm(3,0,110-3*i);
			if(i<15)
				delay_ms(30);
		  if(i>15)
				delay_ms(50);			
		}
			delay_ms(400);
		pca_setpwm(4,0,30);
		delay_ms(400);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,160-5*k);
			pca_setpwm(2,0,80-0.5*k);
			pca_setpwm(3,0,50+3*k);
			delay_ms(12);			
		}
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,107+i);
			delay_ms(10);			
		}
		for( i=0;i<26;i++)  
		{
			pca_setpwm(0,0,127+0.5*i);
			delay_ms(15);			
		}
}
void  put_left2()
{
	static int i,k;
	pca_setpwm(4,0,135);	
	for( i=0;i<23;i++)  
		{
			pca_setpwm(0,0,140+i);
			delay_ms(10);			
		}
		for( i=0;i<16;i++)  
		{
			pca_setpwm(0,0,164+0.5*i);
			delay_ms(20);			
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+5*i);
			pca_setpwm(2,0,70+0.5*i);
			pca_setpwm(3,0,110-3*i);
			if(i<10)
				delay_ms(25);
		  if(i>10)
				delay_ms(40);			
		}
			delay_ms(400);
		pca_setpwm(4,0,30);
		delay_ms(300);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,160-5*k);
			pca_setpwm(2,0,80-0.5*k);
			pca_setpwm(3,0,50+3*k);
			delay_ms(15);			
		}
	for( i=0;i<23;i++)  
		{
			pca_setpwm(0,0,171-i);
			delay_ms(10);			
		}
		for( i=0;i<16;i++)  
		{
			pca_setpwm(0,0,148-0.5*i);
			delay_ms(15);			
		}
}




void  catch_right2()
{
	static int i,k;
	pca_setpwm(4,0,30);	
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,140-i);
			delay_ms(15);			
		}
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,120-0.5*i);
			delay_ms(15);	
			
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+5*i);
			pca_setpwm(2,0,70+0.5*i);
			pca_setpwm(3,0,110-3*i);
	
			if(i<15)
				delay_ms(20);
		  if(i>15)
				delay_ms(35);				
		}
			delay_ms(300);
		pca_setpwm(4,0,135);
		delay_ms(300);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,160-5*k);
			pca_setpwm(2,0,80-0.5*k);
			pca_setpwm(3,0,50+3*k);
			if(k<15)
				delay_ms(10);
		  if(k>15)
				delay_ms(20);		
		}
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,110+i);
			delay_ms(10);			
		}
		for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,130+0.5*i);
			delay_ms(15);			
		}
}

void  catch_zhong2()
{
	static int i,k;
	
		pca_setpwm(4,0,30);
		for( i=0;i<45;i++)  
		{		
			pca_setpwm(0,0,140);
			pca_setpwm(1,0,60+1.89*i);
			pca_setpwm(2,0,70-0.33*i);
			pca_setpwm(3,0,110-1.33*i);
			delay_ms(10);
		}
		delay_ms(200);
		pca_setpwm(4,0,135);
		delay_ms(200);
		for( k=0;k<45;k++)
		{
//			pca_setpwm(0,0,50+3.6*k);
			pca_setpwm(0,0,140);
			pca_setpwm(1,0,145-1.89*k);
			pca_setpwm(2,0,55+0.33*k);
			pca_setpwm(3,0,50+1.33*i);
			delay_ms(10);			
		}
}

void  catch_left2()
{
	static int i,k;
	pca_setpwm(4,0,30);	
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,140+i);
			delay_ms(10);			
		}
		for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,160+0.5*i);
			delay_ms(15);			
		}
		
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+5*i);
			pca_setpwm(2,0,70+0.5*i);
			pca_setpwm(3,0,110-3*i);
			if(i<15)
				delay_ms(20);
		  if(i>15)
				delay_ms(35);				
		}
			delay_ms(300);
		pca_setpwm(4,0,135);
		delay_ms(300);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,160-5*k);
			pca_setpwm(2,0,80-0.5*k);
			pca_setpwm(3,0,50+3*k);
			delay_ms(20);			
		}
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,170-i);
			delay_ms(10);			
		}
			for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,150-0.5*i);
			delay_ms(15);			
		}
}















void  catch_down1()
{
	
	static int i,j;
	pca_setpwm(0,0,140);
	pca_setpwm(1,0,60);
	pca_setpwm(2,0,70);			
	pca_setpwm(3,0,110);
	pca_setpwm(4,0,145);
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,140-7*i);	 
			if(i<15)
				delay_ms(8);
		  if(i>15)
				delay_ms(18);	
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+j);	
		pca_setpwm(2,0,65+j);			
	 	pca_setpwm(3,0,110+5.1*j);	 

			if(j<15)
				delay_ms(13);
		  if(j>15)
				delay_ms(20);	
		}	

		delay_ms(400);
		pca_setpwm(4,0,30);
		delay_ms(400);

		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,80-j);
		pca_setpwm(2,0,85-j);
	 	pca_setpwm(3,0,200-5.25*j);	 
		if(i<15)
				delay_ms(18);
		if(i>15)
				delay_ms(25);	
		}	
		for( i=0;i<60;i++)  
		{
		pca_setpwm(0,0,0+2*i);	 
			delay_ms(5);
		}	
		for( i=0;i<20;i++)  
		{
		pca_setpwm(0,0,120+i);	 
			if(i<15)
				delay_ms(12);
		  if(i>15)
				delay_ms(18);	
		}	
		
}	


void  catch_down2()
{
	static int j;
		pca_setpwm(0,0,140);
	pca_setpwm(4,0,135);
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+j);
	  pca_setpwm(2,0,70+6.8*j);			
	 	pca_setpwm(3,0,110-5.3*j);	 
			if(j<15)
				delay_ms(17);
		  if(j>15)
				delay_ms(28);	
		}	
		delay_ms(500);
		pca_setpwm(4,0,50);
		delay_ms(400);
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,80-j);
	  pca_setpwm(2,0,206-6.8*j);			
	 	pca_setpwm(3,0,4+5.3*j);	 
			if(j<15)
				delay_ms(15);
		  if(j>15)
				delay_ms(25);	
		}	
	pca_setpwm(0,0,140);
			
}
void  catch_down3()
{
	static int i,j;
	pca_setpwm(4,0,135);
		for( i=0;i<38;i++)  
		{
		pca_setpwm(0,0,140-i);	 
			delay_ms(5);
		}	
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,60+0.5*j);
	  pca_setpwm(2,0,70+6.4*j);			
	 	pca_setpwm(3,0,110-5.5*j);	 
			if(j<15)
				delay_ms(18);
		  if(j>15)
				delay_ms(25);
		}	
		delay_ms(500);
		pca_setpwm(4,0,30);
		delay_ms(500);
		for( j=0;j<20;j++)  
		{
		pca_setpwm(1,0,70-0.5*j);
	  pca_setpwm(2,0,198-6.4*j);			
	 	pca_setpwm(3,0,0+5.5*j);	 
			if(j<15)
				delay_ms(15);
		  if(j>15)
				delay_ms(25);	
		}	
		for( i=0;i<38;i++)  
		{
		pca_setpwm(0,0,102+i);	 
			delay_ms(15);
		}	
}	






//半成品区
void  catch_zhong3()
{
	static int i,k;
	
		pca_setpwm(4,0,145);
		for( i=0;i<45;i++)  
		{		
		pca_setpwm(0,0,140);
			pca_setpwm(1,0,60+1.66*i);
			pca_setpwm(2,0,68);
			pca_setpwm(3,0,110-1.11*i);
			if(i<35)
				delay_ms(8);
		  if(i>35)
				delay_ms(25);	
		}
		delay_ms(200);
		pca_setpwm(4,0,60);
		delay_ms(200);
		for( k=0;k<45;k++)
		{
			pca_setpwm(0,0,140);
			pca_setpwm(1,0,145-1.89*k);
			pca_setpwm(2,0,68);

			pca_setpwm(3,0,60+1.11*k);
			delay_ms(8);			
		}
}

void  catch_right3()
{
	static int i,k;
	pca_setpwm(4,0,115);	
for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,140-i);
			delay_ms(10);			
		}
		for( i=0;i<24;i++)  
		{
			pca_setpwm(0,0,120-0.4*i);
			delay_ms(20);			
		}
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+4.5*i);
			pca_setpwm(2,0,70+i);
			pca_setpwm(3,0,110-2*i);
			if(i<35)
				delay_ms(8);
		  if(i>35)
				delay_ms(25);			
		}
			delay_ms(1000);
		pca_setpwm(4,0,30);
		delay_ms(1000);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,150-4.5*k);
			pca_setpwm(2,0,90-k);
			pca_setpwm(3,0,70+2*k);
			delay_ms(30);			
		}
	for( i=0;i<28;i++)  
		{
			pca_setpwm(0,0,112+i);
			delay_ms(15);			
		}
		for( i=1;i<21;i++)  
		{
			pca_setpwm(0,0,112+i);
			delay_ms(15);			
		}
				for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,132+0.4*i);
			delay_ms(30);			
		}
}



void  catch_left3()
{
	static int i,k;
	pca_setpwm(4,0,115);	
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,140+i);
			delay_ms(15);			
		}
			for( i=0;i<14;i++)  
		{
			pca_setpwm(0,0,160+0.5*i);
			delay_ms(25);			
		}
	for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+4.5*i);
			pca_setpwm(2,0,70+i);
			pca_setpwm(3,0,110-2*i);
			delay_ms(30);			
		}
			delay_ms(1000);
		pca_setpwm(4,0,30);
		delay_ms(1000);		
		for( k=0;k<20;k++)
		{

			pca_setpwm(1,0,150-4.5*k);
			pca_setpwm(2,0,90-k);
			pca_setpwm(3,0,70+2*k);
			delay_ms(30);			
		}
	for( i=0;i<20;i++)  
		{
			pca_setpwm(0,0,167-i);
			delay_ms(15);			
		}
		for( i=0;i<14;i++)  
		{
			pca_setpwm(0,0,147-0.5*i);
			delay_ms(25);			
		}
}









//抓下层
void  catch_left_down1()
{
	static int i;
	
//		pca_setpwm(4,0,30);
//	  pca_setpwm(0,0,140);
//		for( i=0;i<20;i++)  
//		{	
//			pca_setpwm(0,0,140);
//			pca_setpwm(1,0,60-0.5*i);
//			pca_setpwm(2,0,70-2.25*i);			
//			delay_ms(20);
//		}
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(1,0,50+i);
//		
//			delay_ms(20);
//		}
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(0,0,140+1.4*i);
//		
//			delay_ms(20);
//		}
//		delay_ms(200);

//		
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,70+4.5*i);
//			pca_setpwm(2,0,25+3.9*i);	
//		
//			delay_ms(30);
//		}
//		
//		delay_ms(200);
//				for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(3,0,65+0.4*i);	
//		
//			delay_ms(30);
//		}
//		delay_ms(200);
//				for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,115+4.5*i);
//			pca_setpwm(2,0,61+3.9*i);	
//	
//			delay_ms(40);
//		}
		huizhong2();
		pca_setpwm(4,0,30);
			step_walk(Back,60,0.3,0);	
			delay_ms(3000);	
		for( i=0;i<25;i++)  
		{
			pca_setpwm(0,0,140+i);
			delay_ms(15);			
		}
	for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+4.25*i);
			pca_setpwm(2,0,70+0.4*i);
			pca_setpwm(3,0,110-2.15*i);
			delay_ms(30);			
		}
			step_walk(Front,60,0.41,0);
					delay_ms(1000);
		pca_setpwm(4,0,115);
		delay_ms(1000);	

			step_walk(Back,60,0.41,0);	
			for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,145-4.25*i);
			pca_setpwm(2,0,78-0.4*i);
			pca_setpwm(3,0,65+2.25*i);
			delay_ms(30);			
		}
				for( i=0;i<25;i++)  
		{
			pca_setpwm(0,0,165-i);
			delay_ms(15);			
		}
		step_walk(Front,60,0.31,0);
//		//
//		delay_ms(1000);
//		pca_setpwm(4,0,135);
//		delay_ms(1000);
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,157-0.7*i);	
//	    pca_setpwm(2,0,100-2.2*i);
//			pca_setpwm(3,0,73-4.3*i);
//			delay_ms(40);
//		}	
//		delay_ms(500);
//		for( i=0;i<50;i++)  
//		{		
//			pca_setpwm(0,0,168+i);
//			delay_ms(20);
//			
//		}	
//		delay_ms(500);
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,150-9*i);	
//	    pca_setpwm(2,0,88-1.8*i);
//			pca_setpwm(3,0,30+7*i);
//			delay_ms(40);
//		}	
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(0,0,218-3.9*i);
//		
//			delay_ms(40);
//		}
	}


void  catch_zhong_down1()
{
	static int i;


		pca_setpwm(4,0,30);
	  pca_setpwm(0,0,140);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60-0.5*i);
			pca_setpwm(2,0,70-2.25*i);			
			delay_ms(20);
		}
		delay_ms(200);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,50+i);
			pca_setpwm(3,0,110-i);			
			delay_ms(20);
		}
		delay_ms(200);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,70+3.75*i);
			pca_setpwm(2,0,25+2.75*i);	
			pca_setpwm(3,0,90-1.1*i);			
			delay_ms(20);
		}
		
		delay_ms(1000);
		pca_setpwm(4,0,125);
		delay_ms(1000);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,145-3.75*i);
			pca_setpwm(2,0,80-2.75*i);	
			pca_setpwm(3,0,60+2*i);			
			delay_ms(20);
		}
		delay_ms(200);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,70-2*i);
			pca_setpwm(2,0,25-0.75*i);	
					
			delay_ms(20);
		}
		delay_ms(200);
		for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,30+1.5*i);
			pca_setpwm(2,0,10+3*i);	
			pca_setpwm(3,0,100+0.5*i);		
			delay_ms(20);
		}
		
}

void  catch_right_down1()
{
	static int i;
	
		pca_setpwm(4,0,30);
//	  pca_setpwm(0,0,140);
//		for( i=0;i<20;i++)  
//		{	
//			pca_setpwm(0,0,140);
//			pca_setpwm(1,0,60-0.5*i);
//			pca_setpwm(2,0,70-2.25*i);			
//			delay_ms(10);
//		}
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(1,0,50+i);
//		
//			delay_ms(30);
//		}
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(0,0,140-1.4*i);
//		
//			delay_ms(30);
//		}
//		delay_ms(200);

//		
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,70+4.5*i);
//			pca_setpwm(2,0,25+3.9*i);	
//		
//			delay_ms(40);
//		}
//		
//		delay_ms(100);
//				for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(3,0,65+0.4*i);	
//		
//			delay_ms(40);
//		}
//		delay_ms(200);
//				for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,115+4.5*i);
//			pca_setpwm(2,0,61+3.9*i);	
//	
//			delay_ms(40);
//		}
//		
//		delay_ms(1000);
//		pca_setpwm(4,0,125);
//		delay_ms(1000);
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,157-0.7*i);	
//	    pca_setpwm(2,0,100-2.2*i);
//			pca_setpwm(3,0,73-4.3*i);
//			delay_ms(40);
//		}	
//		delay_ms(200);
//		for( i=0;i<50;i++)  
//		{		
//			pca_setpwm(0,0,112-i);
//			delay_ms(20);
//			
//		}	
//		delay_ms(200);
//		for( i=0;i<10;i++)  
//		{		
//			pca_setpwm(1,0,150-9*i);	
//	    pca_setpwm(2,0,88-1.8*i);
//			pca_setpwm(3,0,30+7*i);
//			delay_ms(30);
//		}	
//		delay_ms(200);
//		for( i=0;i<20;i++)  
//		{		
//			pca_setpwm(0,0,62+3.9*i);
//		
//			delay_ms(30);
//		}

		huizhong2();
		pca_setpwm(4,0,30);
			step_walk(Back,60,0.3,0);	
			delay_ms(3000);	
		for( i=0;i<28;i++)  
		{
			pca_setpwm(0,0,140-i);
			delay_ms(15);			
		}
	for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,60+4.25*i);
			pca_setpwm(2,0,70+0.4*i);
			pca_setpwm(3,0,110-2.15*i);
			delay_ms(30);			
		}
		delay_ms(1000);
			step_walk(Front,60,0.41,0);
		delay_ms(1000);
		pca_setpwm(4,0,115);
		delay_ms(1000);	

			step_walk(Back,60,0.41,0);	
		delay_ms(1000);
			for( i=0;i<20;i++)  
		{		
			pca_setpwm(1,0,145-4.25*i);
			pca_setpwm(2,0,78-0.4*i);
			pca_setpwm(3,0,65+2.15*i);
			delay_ms(30);			
		}
				for( i=0;i<28;i++)  
		{
			pca_setpwm(0,0,112+i);
			delay_ms(15);			
		}
		step_walk(Front,60,0.31,0);
	}





















































