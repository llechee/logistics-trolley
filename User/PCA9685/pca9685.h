#ifndef __PCA9685_H
#define __PCA9685_H
#include "myiic.h"

#define PCA9685_SUBADR1 0x2 
#define PCA9685_SUBADR2 0x3 
#define PCA9685_SUBADR3 0x4 
#define pca_adrr 0x80
//#define pca_adrr 0x40
#define pca_mode1 0x0 
#define pca_pre 0xFE //�������ڵļĴ���
#define LED0_ON_L 0x6 //��0·
#define LED0_ON_H 0x7 
#define LED0_OFF_L 0x8 
#define LED0_OFF_H 0x9 
#define ALLLED_ON_L 0xFA 
#define ALLLED_ON_H 0xFB 
#define ALLLED_OFF_L 0xFC 
#define ALLLED_OFF_H 0xFD 
void set_duoji(u8 num,u8 start_angle, u8 end_angle );
void set_all_duoji(u32 pwm1,u32 pwm2 ,u32 pwm3 ,u32 pwm4,u32 pwm5);
void pca_write(u8 adrr,u8 data);
u8 pca_read(u8 adrr);
void pca_setfreq(float freq);
void pca_setpwm(u8 num, u32 on, u32 off);
void PCA_MG9XX_Init(float hz,u8 angle);//����1
/*����1��2�������ﲢû���õ����˳�������ǰ�˵Ļ����Ͻ����޸ĵģ�����������ʵ�ֵĹ��ܴ�����
�ܹ�ʵ��ֱ�Ӹ��ǶȲ����ﵽ��ת�̶��Ƕȵ�Ŀ�ģ����Ǿ��幫ʽ�Ҳ�֪���Ӻδ������ģ�
�����Ҿ�ֱ��ͨ������offֵ�ķ�ʽ�޸���ת�Ƕ�*/



#endif

