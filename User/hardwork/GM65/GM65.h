#ifndef __USARTS__
#define __USARTS__

#include "sys.h"

//#define rcv_len		8			//�����������ֽ��� 200

//	  	
//char  rcv_buf[8];	//���ջ���,len���ֽ�
//int  rcl_buf[8];
//int  num;					//�������б��	


void uart5_init(int bound);
void USART4_IRQHandler(void);


#endif

