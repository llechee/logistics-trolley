#include "bsp_usart.h"
#include "delay.h"
unsigned int state = 0;	
unsigned int state1 = 0;	
unsigned int state_qr = 0;	
//接受二维码和位置标志位
unsigned int get_qr_flag =0;	
unsigned int get_position1_flag =0;	
unsigned int get_position2_flag =0;
unsigned int Rec_time =0;
//接受函数使用
	int Rx_Qr[7];  
	int RxBuffer1[5];
	int RxCounter1=0;//接受颜色
	int RxCounter2=0;//接受二维码
//校准抓取使用	
	int pos1,pos2;  
	int Qr1,Qr2;
extern u8 Qr_up[3],Qr_down[3];
extern u8 color1[3], color2[3];   

//*************************************************************************************
//接收二维码
//*************************************************************************************
void Openmv_Receive_Qr(int16_t data)
{

	if(state_qr==0&&data==0x2C)
	{
		state_qr=1;
		Rx_Qr[RxCounter2++]=data;
	}
	else if(state_qr==1&&data==18)
	{
		state_qr=2;
		Rx_Qr[RxCounter2++]=data;
	}
	else if(state_qr==2)
	{
		Rx_Qr[RxCounter2++]=data;
		if(data == 0x5B)
		{	
			state_qr=3;
		}
	}
	else if(state_qr==3)		//state == 3 
	{
        	if(Rx_Qr[RxCounter2-1] == 0x5B)
        	{
            state_qr = 0;
					  Qr1= Rx_Qr[3]<<8|Rx_Qr[2];
						Qr2= Rx_Qr[5]<<8|Rx_Qr[4];						
						rank_position( Qr1,Qr_up);
						rank_position( Qr2,Qr_down);
						printf("第一次搬运%d,第二次搬运%d",Qr1,Qr2);
						printf("\n");
						get_qr_flag =1;
        	}
        	else   //wrong thing
        	{
            	state_qr = 0;
				     RxCounter2=0;
        	}
	}    
	else	//wrong thing
	{
		state_qr = 0;
		RxCounter2=0;
	}
}
//*************************************************************************************
//接收位置
//*************************************************************************************
void Openmv_Receive_Data1(int16_t data)
{
	if(state==0&&data==0x2C)
	{
		state=1;
		RxBuffer1[RxCounter1++]=data;
	}
	else if(state==1&&data==18)
	{
		state=2;
		RxBuffer1[RxCounter1++]=data;
	}
	else if(state==2)
	{
		RxBuffer1[RxCounter1++]=data;
		if(RxCounter1>5||data == 0x5B) state=3;	//the last of char is openmv[19]
	}
	else if(state==3)		//state == 3 
	{
        	if(RxBuffer1[RxCounter1-1] == 0x5B)
        	{
            state = 0;
					  pos1= RxBuffer1[3]<<8 | RxBuffer1[2];
						color1[0]= pos1/100;color1[1]= (pos1%100)/10,color1[2]= pos1%10;;
						printf("球的位置是%d",pos1);
						printf("\n");
						if(pos1>0)
							get_position1_flag=1;
        	}
        	else   //wrong thing
        	{
            	state = 0;
				     RxCounter1=0;
        	}
	}    
	else	//wrong thing
	{
		state = 0;
		RxCounter1=0;
	}
}
//*************************************************************************************
void Openmv_Receive_Data2(int16_t data)
{
	if(state1==0&&data==0x2C)
	{
		state1=1;
		RxBuffer1[RxCounter1++]=data;
	}
	else if(state1==1&&data==18)
	{
		state1=2;
		RxBuffer1[RxCounter1++]=data;
	}
	else if(state1==2)
	{
		RxBuffer1[RxCounter1++]=data;
		if(RxCounter1>5||data == 0x5B) state1=3;	//the last of char is openmv[19]
	}
	else if(state1==3)		//state == 3 
	{
        	if(RxBuffer1[RxCounter1-1] == 0x5B)
        	{
            state1= 0;
					  pos2= RxBuffer1[3]<<8 | RxBuffer1[2];
						color2[0]= pos2/100;color2[1]= (pos2%100)/10,color2[2]= pos2%10;;
						printf("球的位置是%d",pos2);
						printf("\n");
	//					if(pos2>0)
							get_position2_flag=1;
        	}
        	else   //wrong thing
        	{
            	state1 = 0;
				     RxCounter1=0;
        	}
	}    
	else	//wrong thing
	{
		state1= 0;
		RxCounter1=0;
	}
}
//*************************************************************************************
void get_qrcode()
{
	USART_SendData(USART2,1);  
	while(get_qr_flag!=1);
	Rec_time =1;                 //结束第一次二维码读取，接受上层坐标标志位
	USART_SendData(USART2,3);    //让openmv离开扫描二维码部分
}
void get_position1()     //获得上面位置性息
{
	USART_SendData(USART2,4);   
	while(get_position1_flag!=1); 
	USART_SendData(USART2,3);  //让openmv离开第一次扫描位置部分
	Rec_time =2;  
}
void get_position2()   ////获得下面位置信息
{
	USART_SendData(USART2,4);   
	while(get_position2_flag!=1); 
	USART_SendData(USART2,3);  //让openmv离开第一次扫描位置部分
}

//*************************************************************************************
//*************************************************************************************
//用于单片机与OPENMV端通信，采用USART2
//*************************************************************************************
//*************************************************************************************

void USART2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	USART_DeInit(USART2);  
	 //USART2_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
 
	 //USART2_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
 
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	 
	USART_Init(USART2, &USART_InitStructure); 


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);                    

}


////*************************************************************************************
////*************************************************************************************
////用于单片机与pc端通信，采用USART3
////*************************************************************************************
////*************************************************************************************



static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOB), ENABLE);
	
	// 打开串口外设的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = 115200;
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
	USART_Init(USART3, &USART_InitStructure);
	// 串口中断优先级配置
	NVIC_Configuration();
	// 使能串口接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	// 使能串口
	USART_Cmd(USART3, ENABLE);	    
}

/* 发送一个字节 */
void Usart_SendByte_3(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}
void USART3_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(USART3);
    USART_SendData(USART3,ucTemp);    
	}	 
}



///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART3, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}








