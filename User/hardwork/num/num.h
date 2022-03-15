#ifndef __NUM_H__
#define __NUM_H__

#include "sys.h"

#define DIO PEout(4)	//串行数据输入
#define RCLK PEout(5)	//锁存控制信号(上升沿有效)
#define SCLK PCout(4)	//时钟脉冲信号(上升沿有效)

void datain(unsigned char data);
void dataout(void);
void sentdata(unsigned char data,unsigned char wel);
void GPIO_init(void);
void QR_show(void); 
#endif
