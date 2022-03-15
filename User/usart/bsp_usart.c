#include "bsp_usart.h"
#include "delay.h"
unsigned int state = 0;	
unsigned int state1 = 0;	
unsigned int state_qr = 0;	
//���ܶ�ά���λ�ñ�־λ
unsigned int get_qr_flag =0;	
unsigned int get_position1_flag =0;	
unsigned int get_position2_flag =0;
unsigned int Rec_time =0;
//���ܺ���ʹ��
	int Rx_Qr[7];  
	int RxBuffer1[5];
	int RxCounter1=0;//������ɫ
	int RxCounter2=0;//���ܶ�ά��
//У׼ץȡʹ��	
	int pos1,pos2;  
	int Qr1,Qr2;
extern u8 Qr_up[3],Qr_down[3];
extern u8 color1[3], color2[3];   

//*************************************************************************************
//���ն�ά��
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
						printf("��һ�ΰ���%d,�ڶ��ΰ���%d",Qr1,Qr2);
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
//����λ��
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
						printf("���λ����%d",pos1);
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
						printf("���λ����%d",pos2);
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
	Rec_time =1;                 //������һ�ζ�ά���ȡ�������ϲ������־λ
	USART_SendData(USART2,3);    //��openmv�뿪ɨ���ά�벿��
}
void get_position1()     //�������λ����Ϣ
{
	USART_SendData(USART2,4);   
	while(get_position1_flag!=1); 
	USART_SendData(USART2,3);  //��openmv�뿪��һ��ɨ��λ�ò���
	Rec_time =2;  
}
void get_position2()   ////�������λ����Ϣ
{
	USART_SendData(USART2,4);   
	while(get_position2_flag!=1); 
	USART_SendData(USART2,3);  //��openmv�뿪��һ��ɨ��λ�ò���
}

//*************************************************************************************
//*************************************************************************************
//���ڵ�Ƭ����OPENMV��ͨ�ţ�����USART2
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
////���ڵ�Ƭ����pc��ͨ�ţ�����USART3
////*************************************************************************************
////*************************************************************************************



static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOB), ENABLE);
	
	// �򿪴��������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 115200;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART3, &USART_InitStructure);
	// �����ж����ȼ�����
	NVIC_Configuration();
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	// ʹ�ܴ���
	USART_Cmd(USART3, ENABLE);	    
}

/* ����һ���ֽ� */
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



///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART3, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}








