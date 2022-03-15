#ifndef __USARTS__
#define __USARTS__

#include "sys.h"

//#define rcv_len		8			//定义最大接收字节数 200

//	  	
//char  rcv_buf[8];	//接收缓冲,len个字节
//int  rcl_buf[8];
//int  num;					//接收序列标记	


void uart5_init(int bound);
void USART4_IRQHandler(void);


#endif

