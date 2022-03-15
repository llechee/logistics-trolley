#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>


//´®¿Ú5-UART5
#include <stdio.h>


//´®¿Ú5-UART5
#define rcv_len		7	

//    


void uart5_init(int bound);
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data);

#endif  /* __BSP_USART_H */

