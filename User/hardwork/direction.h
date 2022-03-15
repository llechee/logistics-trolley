#ifndef __DIRECTION__
#define __DIRECTION__


#define Left	1
#define Right	-1

#define Middle	0


//#define  shu_n  88;
//#define  ni  89;
#define Front	2
#define Back	-2
#define Left_up  3
#define Right_up 4
#define Left_down -3
#define Right_down -4
#define Pi	3.14159265

void xuanzhuan(int fangxiang, int speed);
void walk(int direc, int speed);
void turn(int fangxiang);



#endif
