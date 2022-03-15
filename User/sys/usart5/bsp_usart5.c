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
 char rcv_buf[rcv_len];	//���ջ���,len���ֽ�
int  rcl_buf[rcv_len];
				//�������б��	
static void NVIC_Configuration_uart5(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void uart5_init(int bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD), ENABLE);
	
	// �򿪴��������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate =bound;
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
	USART_Init( UART5, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration_uart5();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig( UART5, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd( UART5, ENABLE);	    
}

/* ����һ���ֽ� */
void Usart_SendByte_5(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}



/* ����8λ���ݵ����� */
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
	if(USART_GetITStatus(UART5, USART_IT_RXNE)!= RESET) //���յ�����
		{
	//		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
			rcv =USART_ReceiveData(UART5);	//��ȡ���յ�������
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












