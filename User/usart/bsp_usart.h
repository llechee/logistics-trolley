#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>

void get_position1(void);
void get_position2(void);
void get_qrcode(void);
void Openmv_Receive_Qr(int16_t data);
void Openmv_Receive_Data1(int16_t data);
void Openmv_Receive_Data2(int16_t data);

//初始化USART2
void USART2_Init(void);
//初始化USART3
void USART3_Config(void);
void Usart_SendByte_3(USART_TypeDef* pUSARTx, uint8_t data);


//int fputc(int ch, FILE *f);

#endif  /* __BSP_USART_H */

