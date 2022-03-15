#include "pca9685.h"
#include "myiic.h"
#include "delay.h"
#include "math.h"

void pca_write(u8 adrr,u8 data)//��PCAд����,adrrd��ַ,data����
{ 
        IIC_Start();
        
        IIC_Send_Byte(pca_adrr);
        IIC_Wait_Ack();
        
        IIC_Send_Byte(adrr);
        IIC_Wait_Ack();
        
        IIC_Send_Byte(data);
        IIC_Wait_Ack();
        
        IIC_Stop();
}

u8 pca_read(u8 adrr)//��PCA������
{
        u8 data;
        IIC_Start();
        
        IIC_Send_Byte(pca_adrr);
        IIC_Wait_Ack();
        
        IIC_Send_Byte(adrr);
        IIC_Wait_Ack();
        
        IIC_Start();
        
        IIC_Send_Byte(pca_adrr|0x01);
        IIC_Wait_Ack();
        
        data=IIC_Read_Byte(0);
        IIC_Stop();
        
        return data;
}


void pca_setfreq(float freq)//����PWMƵ��
{
                u8 prescale,oldmode,newmode;
                double prescaleval;
                freq *= 0.92; 
                prescaleval = 25000000;
                prescaleval /= 4096;
                prescaleval /= freq;
                prescaleval -= 1;
                prescale =floor(prescaleval + 0.5f);

                oldmode = pca_read(pca_mode1);//pca_mode1 0x0
        
                newmode = (oldmode&0x7F) | 0x10; // sleep  0x0&0x7f=0x0  0x0|0x10=0x10
        
                pca_write(pca_mode1, newmode); // go to sleep  D4sleepд1
        
                pca_write(pca_pre, prescale); // set the prescaler 
								//pca_pre 0xFE�������ڵļĴ��������������Ԥװ��ֵ����
        
                pca_write(pca_mode1, oldmode);//oldmode 0x0,D4д0�˳�sleepģʽ
                delay_ms(2);
        
                pca_write(pca_mode1, oldmode | 0xa1); 
								//0x0|0xa1=10100001 D6ʹ���ڲ�ʱ�ӣ�D5�ڲ���ַ��д���Զ����ӣ�D0��Ӧ0x70ͨ��i2c��ַ
}
void set_all_duoji(u32 pwm1,u32 pwm2 ,u32 pwm3 ,u32 pwm4,u32 pwm5)
{
	pca_setpwm(1, 0, pwm1);
	pca_setpwm(2, 0, pwm2);
	pca_setpwm(3, 0, pwm3);
	pca_setpwm(4, 0, pwm4);
	pca_setpwm(5, 0, pwm5);
}
void set_duoji(u8 num,u8 start_angle, u8 end_angle )
{
	static int j;
		for(j=start_angle;j<end_angle ;j++)//·������Ȼ�����Ȼ����ת90�㣨������˲�䶯����
		{
			pca_setpwm(num,0,j);//��ת90��
			delay_ms(1);
		}	
}

void pca_setpwm(u8 num, u32 on, u32 off)
{
								off=675+10*off;
                pca_write(LED0_ON_L+4*num,on);//
                pca_write(LED0_ON_H+4*num,on>>8);
                pca_write(LED0_OFF_L+4*num,off);
                pca_write(LED0_OFF_H+4*num,off>>8);
}
/*num:���PWM�������0~15��on:PWM��������ֵ0~4096,off:PWM�½�����ֵ0~4096
һ��PWM���ڷֳ�4096�ݣ���0��ʼ+1�������Ƶ�onʱ����Ϊ�ߵ�ƽ������������offʱ
����Ϊ�͵�ƽ��ֱ������4096���¿�ʼ�����Ե�on������0ʱ������ʱ,��on����0ʱ��
off/4096��ֵ����PWM��ռ�ձȡ�*/

/*
        �������ã���ʼ�����������
        ������1.PWMƵ��
                  2.��ʼ������Ƕ�
*/
void PCA_MG9XX_Init(float hz,u8 angle)
{
//      u32 off=0;
        IIC_Init();
        pca_write(pca_mode1,0x0);
        pca_setfreq(hz);//����PWMƵ��
//        off=(u32)(145+angle*2.4);
//        pca_setpwm(0,0,off);pca_setpwm(1,0,off);pca_setpwm(2,0,off);pca_setpwm(3,0,off);
//        pca_setpwm(4,0,off);pca_setpwm(5,0,off);pca_setpwm(6,0,off);pca_setpwm(7,0,off);
//        pca_setpwm(8,0,off);pca_setpwm(9,0,off);pca_setpwm(10,0,off);pca_setpwm(11,0,off);
//        pca_setpwm(12,0,off);pca_setpwm(13,0,off);pca_setpwm(14,0,off);pca_setpwm(15,0,off);
        delay_ms(500);
}

/*
        �������ã����ƶ��ת����
        ������1.����˿ڣ���ѡ0~15��
                  2.��ʼ�Ƕȣ���ѡ0~180��
                  3.�����Ƕȣ���ѡ0~180��
                  4.ģʽѡ��0 ��ʾ����������ʱ������ʱ��Ҫ�ں������������ʱ�������Ҳ��ɵ��٣������������������ֵ��
                                          1 ��ʾ����������ʱ������ʱ����Ҫ�ں������������ʱ�������Ҳ��ɵ��٣������������������ֵ��
                                          2 ��ʾ�ٶȿɵ��������������ʾ�ٶ�ֵ��
                  5.�ٶȣ�������� 0 ������ֵ���� 1 ʱ�ٶ���죬��ֵԽ���ٶ�ԽС��
        ע�����ģʽ 0��1 ���ٶȱ�ģʽ 2 ������ٶȴ�
*/

