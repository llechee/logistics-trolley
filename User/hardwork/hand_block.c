#include "direction.h"
#include "timer.h"
#include "hand.h"
#include "road.h"
#include "bsp_usart.h"
#include "hand_block.h"
extern u8 color1[3], color2[3];      //color[0]表示左位置，color[1]表示中位置，color[2]表示右位置   值为123任组，1表示red,2表示green,3表示blue
extern u8 Qr_up[3],Qr_down[3];
extern u8 qr_code[3];
extern int pos1;

extern u8 qr_up_test[3],qr_down_test[3];
extern u8 color1_test[3], color2_test[3];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*      粗加工区动作     */

//按照QR1，QR2顺序来放
void rank_lay(uint8_t *qr_code,int y)
{
		if(qr_code[0+y]==1)
		{
			clamp (1);
			law_grand1(Middle);
		}
		if(qr_code[0+y]==2)
		{
			clamp (2);
		  law_grand1(Right);
		}
		if(qr_code[0+y]==3)
		{
			clamp (3);
		  law_grand1(Left);
		}
		delay_ms(10);
}

//在粗加工区往回抓，放到货架上
void catch_return(uint8_t *qr_code,int m)
{
		if(qr_code[0+m]==1)
		{
			catch_zhong2();
			catch_down1();
		}

		if(qr_code[0+m]==2)
		{
			catch_right2();
			catch_down2();
		}
		if(qr_code[0+m]==3)
		{
			catch_left2();
			catch_down3();
		}
}
void rough_position(uint8_t *qr_code)
{
	rank_lay(qr_code,0);
	rank_lay(qr_code,1);
	rank_lay(qr_code,2);
	
	catch_return(qr_code,0);
	catch_return(qr_code,1);
	catch_return(qr_code,2);
				

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*      半成品区动作    */
void  rank_lay_higher(uint8_t *qr_code,int p)
{
		if(qr_code[0+p]==1)
		{
			clamp (1);
			catch_zhong3();
		}
		if(qr_code[0+p]==2)
		{
			clamp (2);
			catch_right3();
		}
		if(qr_code[0+p]==3)
		{
			clamp (3);
			catch_left3();
		}
	
}
void half_position(uint8_t *qr_code)
{
	rank_lay_higher(qr_code,0);
	rank_lay_higher(qr_code,1);
	rank_lay_higher(qr_code,2);
	
}
