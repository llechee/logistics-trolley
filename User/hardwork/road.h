#ifndef __ROAD__
#define __ROAD__

#include "sys.h"
#define touch	1	   //触发,  黑线
#define untouch	0	//未触发,白线
#define  all         //xunjiA_3==1&&xunjiA_4&&xunjiA_5
//前
#define xunjiA_7	  PBin(14)
#define xunjiA_6	  PAin(15)
#define xunjiA_5	  PBin(15)
#define xunjiA_4	  PFin(1)
#define xunjiA_3	  PFin(3)
#define xunjiA_2	  PFin(5)
#define xunjiA_1	  PFin(15)
//右
#define xunjiB_4	PFin(6)
#define xunjiB_3	PFin(7)
#define xunjiB_2	PGin(11)
#define xunjiB_1	PFin(11)
#define xunjiB_5	PCin(8)
#define xunjiB_6	PCin(9)
#define xunjiB_7	PCin(10)

//后

#define xunjiC_1	PGin(14)
#define xunjiC_2	PGin(13)
#define xunjiC_3	PGin(6)
#define xunjiC_4	PGin(7)

//左
#define xunjiD_1	PGin(4)
#define xunjiD_2	PDin(11)
#define xunjiD_3	PGin(5)
#define xunjiD_4  PFin(0)
#define xunjiD_5  PGin(2)
#define xunjiD_6	PFin(4)
#define xunjiD_7	PFin(14)

void Adjusting_posture(void);
void pingyi(int direc, int setspeed);
void move_time(int direc, int ms);
void move(int direc, u8 step_num,int norspeed,int lastpeed);
void xunji(int direc,int speed);
void road_init(void);
void stop(int ms);




#endif
