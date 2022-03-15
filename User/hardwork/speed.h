#ifndef __SPEED__
#define __SPEED__
#include "sys.h"
#define one_pluse    (13*30*4)   //电机转动一圈的脉冲
//   电机L1   电机R1
//   电机L2   电机R2
//L1 1
#define L1_1  PEout(0)      //AIN2
#define L1_2  PEout(1)      //AIN1
//R1 2
#define R1_1	PEout(2)      //BIN1
#define R1_2	PGout(10)      //BIN2
//R2 3
#define R2_1	 PGout(0)    //AIN2
#define R2_2	 PGout(1)    //AIN1
//L2 4
#define L2_1	 PGout(2)    //BIN1
#define L2_2   PGout(3)     //BIN2
int Position3_PID(int now_position,int Target);
int Position2_PID(int now_position,int Target);
int Position1_PID(int now_position,int Target);
int Position4_PID(int now_position,int Target);
void step_walk(int direc,int velocity ,float DS ,int track );
void Motor_Init(void);
void speed_control(int duty1, int duty2, int duty3, int duty4);
int Speed_PID (int nowspeed,int setspeed);       //速度环
int Position_PID(int now_position,int Target);
int Angle_PID(int yaw,int target_angle,int A_z); //角度环 返回速度偏差
void speed_init(void);
void motor_work(int targetA,int targetB,int targetC,int targetD);
int GFP_abs(int p);


#endif
