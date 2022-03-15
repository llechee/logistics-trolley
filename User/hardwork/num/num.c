#include "num.h"
#include "delay.h"
extern u8 Qr_up[3],Qr_down[3];
extern int Qr1,Qr2;
int data1,data2,data3,data4,data5,data6;
extern unsigned int data[10];		//段
extern unsigned int wei[8];					//位
void GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_4;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);		//1
	GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);		//0，拉低便于产生上升沿
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
}
void datain(unsigned char data)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		SCLK=0;
		if(data & 0x80)		//保留
		DIO=1;
		else
		DIO=0;
		
		data<<=1;
		SCLK=1;
	}
}
/*输出*/
void dataout(void)
{
	RCLK=0;
	RCLK=1;
}
void sentdata(unsigned char data,unsigned char wel)
{
	
	datain(data);
	datain(wel);	
	dataout();
}
void QR_show(void)
{
	
	data1=Qr1/100;
	data2=(Qr1%100)/10;
	data3=Qr1%10;
	
	data4=Qr2/100;
	data5=(Qr2%100)/10;
	data6=Qr2%10;
	
//		delay_ms(1);
		sentdata(data[data1],wei[0]);
//		delay_ms(1);
		sentdata(data[data2],wei[1]);
//		delay_ms(1);
		sentdata(data [data3],wei[2]);
//		delay_ms(1);
		sentdata(data [data4],wei[5]);
//		delay_ms(1);
		sentdata(data [data5],wei[6]);
//		delay_ms(1);
		sentdata(data [data6],wei[7]);
	

}



