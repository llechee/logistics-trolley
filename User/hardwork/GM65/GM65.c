#include "GM65.h"
#include "bsp_usart.h"
#include "stdlib.h"
#include "stdio.h"
//extern int uart3_receive;
//extern u8 rcvflag;
char  rcv_buf[8];	//���ջ���,len���ֽ�
int  rcl_buf[8];
int  num;					//�������б��	

//ɨ��/�������մ���,usart5,TX-B10,RX-B11
void uart5_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��UGPIODʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��UGPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��USART5ʱ��
	//USART3_TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
   
	//USART3_RX	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure);     //��ʼ������3
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���3 
}
//ɨ���ж�
//void UART5_IRQHandler(void)
//{
//  u8 rcv;
//	u8 num;
//  u8 num1;
//  u8 num2;
//	//char c;
//	//int i;
//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //���յ�����
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
//		/* �ȴ������������� */
//		while (USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);

//		return (int)USART_ReceiveData(UART5);
//}

