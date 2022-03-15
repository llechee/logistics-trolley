#include "ANO_DT.h"
#include "bsp_usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
	
u8 senddate[50];	


void Send_User(u16 data1, u16 data2, u16 data3,u16 data4,u16 data5)	
{
	u8 _cnt=0; u8 i;
		u8 sc= 0;	
	u8 ac= 0;
	
	senddate[_cnt++]=0xAA;
	senddate[_cnt++]=0xFF;
	senddate[_cnt++]=0xF1;
	senddate[_cnt++]=10;
 
	senddate[_cnt++]=BYTE0(data1);
	senddate[_cnt++]=BYTE1(data1);
	
	senddate[_cnt++]=BYTE0(data2);
	senddate[_cnt++]=BYTE1(data2);
	
	senddate[_cnt++]=BYTE0(data3);
	senddate[_cnt++]=BYTE1(data3);
	
	senddate[_cnt++]=BYTE0(data4);
	senddate[_cnt++]=BYTE1(data4);
	
	senddate[_cnt++]=BYTE0(data5);
	senddate[_cnt++]=BYTE1(data5);
 
	for(i=0;i<senddate[3]+4;i++)
	{
		sc +=senddate[i];
		ac +=sc;
	}
	senddate[_cnt++]=sc;
	senddate[_cnt++]=ac;
//	Usart_SendArray(USART3,senddate,_cnt);
}


//void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num)
//{
//	uint8_t i;
//	for( i=0; i<num; i++ )
//  {
//		Usart_SendByte(pUSARTx, array[i]);
//	}
//	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );
//}

