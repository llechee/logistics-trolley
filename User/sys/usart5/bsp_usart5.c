#include "bsp_usart5.h"
#include "GM65.h"
#include "bsp_usart.h"
#include "stdlib.h"
#include "stdio.h"
#include "num.h"
extern int gm65_flag;
extern int Qr1,Qr2;
char rcv;
int  num=0;	
 char rcv_buf[rcv_len];	//接收缓冲,len个字节
int  rcl_buf[rcv_len];
				//接收序列标记	
static void NVIC_Configuration_uart5(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void uart5_init(int bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD), ENABLE);
	
	// 打开串口外设的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate =bound;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init( UART5, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration_uart5();
	
	// 使能串口接收中断
	USART_ITConfig( UART5, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd( UART5, ENABLE);	    
}

/* 发送一个字节 */
void Usart_SendByte_5(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}



/* 发送8位数据的数组 */
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num)
{
	uint8_t i;
	for( i=0; i<num; i++ )
  {
		Usart_SendByte_5(pUSARTx, array[i]);
	}
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );
}

int zhuanhuan(char c)
{
	if(c=='1')
		return 1;
	else if(c=='2')
		return 2;
	else if(c=='3')
		return 3;
	else
		return 0;
}


//void UART5_IRQHandler(void)
//{
//  uint8_t ucTemp;
//	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)
//	{	
//		ucTemp = USART_ReceiveData(UART5);
//    USART_SendData(UART5,ucTemp);    
//	}	 
//}

void UART5_IRQHandler(void)
{
	u8 rcv;
	static u8 num=0;
	int i;
	//	printf("324");
	if(USART_GetITStatus(UART5, USART_IT_RXNE)!= RESET) //接收到数据
		{
	//		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
			rcv =USART_ReceiveData(UART5);	//读取接收到的数据
			if(rcv != '1'&&rcv != '2'&&rcv != '3')
			{	
					num=3;
			}
			else 
			{
				rcv_buf[num]=rcv;
				num++;
			}
		for(i=0;i<6;i++)
		{
			rcl_buf[i]=rcv_buf[i]-'0';
		}
		if(num==6)
		{
			gm65_flag=1;
			
		}
		
	//		rcl_buf[i]=zhuanhuan(rcv_buf[i]);
			
		//		rcl_buf[i]=(int)(rcv_buf[i]);
	//		rcl_buf[i]=rcv_buf[i]-'0';
			Qr1=rcl_buf[0]*100+rcl_buf[1]*10+rcl_buf[2];
			Qr2=rcl_buf[3]*100+rcl_buf[4]*10+rcl_buf[5];
//			printf("%c",rcv);
			
		//	printf("%d",Qr1);
			
		}
}












