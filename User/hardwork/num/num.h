#ifndef __NUM_H__
#define __NUM_H__

#include "sys.h"

#define DIO PEout(4)	//������������
#define RCLK PEout(5)	//��������ź�(��������Ч)
#define SCLK PCout(4)	//ʱ�������ź�(��������Ч)

void datain(unsigned char data);
void dataout(void);
void sentdata(unsigned char data,unsigned char wel);
void GPIO_init(void);
void QR_show(void); 
#endif
