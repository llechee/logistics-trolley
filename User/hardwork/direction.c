#include "direction.h"
#include "speed.h"
#include "math.h"
extern int speed1, speed2, speed3, speed4;
extern int setspeed1, setspeed2, setspeed3, setspeed4;
extern int setspeed;
extern int sgspeed;
extern int target_speed;

/*
	轮子1	      轮子2——L
								
	轮子4——L	   轮子3
	
*/

void pingyi(int direc,  int setspeed)
{
	int lv, rv;
	
	switch(direc)
	{
		case Front:
		{
			lv = setspeed;
			rv = setspeed;
			break;
		}
		case Back:
		{
			lv = -setspeed;
			rv = -setspeed;
			break;
		}
		case Left:
		{
			lv = setspeed;
			rv = -setspeed;
			break;
		}
		case Right:
		{
			lv = -setspeed;
			rv = setspeed;
			break;
		}
		default:
		{
			lv = 0;
			rv = 0;
			break;
		}
	}
	setspeed2 = lv;
	setspeed4 = rv;
	setspeed1 = rv;
	setspeed3 = lv;
	speed_control(setspeed1, setspeed2, setspeed3, setspeed4);
}
void xuanzhuan(int fangxiang, int math_speed)    //向右是顺时针
{
	int spd = math_speed;
	if(fangxiang == Right)
	{
		spd = -spd;
	}
	setspeed1 = -spd;
	setspeed4 = spd;
	setspeed2 = spd;
	setspeed3 = -spd;
	speed_control( setspeed1, setspeed2, setspeed3, setspeed4);
}
//void turn(int fangxiang)
//{
//	int wide = 170;	//左右两轮中心距
//	int R = 150;	//转弯半径
//	int lv, rv;
//	if(fangxiang == Right)
//		R = -R;
//	lv = (R - wide/2)/R*setspeed;
//	rv = (R + wide/2)/R*setspeed;
//	setspeed1 = lv;
//	setspeed4 = lv;
//	setspeed2 = rv;
//	setspeed3 = rv;
//	speed_control( setspeed1, setspeed2, setspeed3, setspeed4);
//}











