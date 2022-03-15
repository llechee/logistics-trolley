#include "GM65.h"
#include "bsp_usart.h"
#include "stdlib.h"
#include "stdio.h"
//extern int uart3_receive;
//extern u8 rcvflag;
char  rcv_buf[8];	//接收缓冲,len个字节
int  rcl_buf[8];
int  num;					//接收序列标记	

//扫码/蓝牙接收串口,usart5,TX-B10,RX-B11
void uart5_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//使能UGPIOD时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能UGPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//使能USART5时钟
	//USART3_TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);
   
	//USART3_RX	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART5, &USART_InitStructure);     //初始化串口3
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(UART5, ENABLE);                    //使能串口3 
}
//扫码中断
//void UART5_IRQHandler(void)
//{
//  u8 rcv;
//	u8 num;
//  u8 num1;
//  u8 num2;
//	//char c;
//	//int i;
//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //接收到数据
//	{
//		printf("111");
//		rcv = USART_ReceiveData(UART5);
//		if(rcv == '-')
//		{
//			num = 3;
//		}
//		else
//		{
//			rcv_buf[num] = rcv;
//			num ++;
////		printf("%c",rcv);
//			if(num == 8)
//			{
//				num = 0;
//				
//			}
//		}
//	}

//	num1=rcv_buf[0]+rcv_buf[1]+rcv_buf[2];
//	num2=rcv_buf[4]+rcv_buf[5]+rcv_buf[6];
//	}
//int fgetc(FILE *f)
//{
//		/* 等待串口输入数据 */
//		while (USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);

//		return (int)USART_ReceiveData(UART5);
//}

