#ifndef __HAND__
#define __HAND__

#include "sys.h" 
#define   r 1;
#define   g 2;
#define   b 3;
#define dead	10
void rank_position(int pos,uint8_t *qr_code);
void look_up_position(void);
int catch(int dirc,int time);
void look_position(void);
void banyun(void);
void look_qr(void);
void catch_guizhong(void);
void start(void);
void huizhong1(void);
void huizhong2(void);
void huizhong3(void);


///////////////ģ�黯����///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rough_position(uint8_t *qr_code);

void half_position(uint8_t *qr_code);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//brief:����ץȡ����   ץ�²��ץ�²�
void rank_catch(uint8_t *qr_code,uint8_t *color,int time,int num);

//ץȡ�ϲ��ץ�²㶯��
int catch(int direc,int time);

//    1��ʾ��ԭ�����������Ϸ�  2��ʾ�Ӵּӹ����������Ϸ�
void law_out(int direc,int time) ;

//���ּӹ�����
void law_grand1(int direc);

void law_grand2(int direc);

//�ӻ�����ץȡ  1��ʾ��ɫ �Լ���ɫ���ܵ�λ��
void clamp (int direc);





/* ����ֺ���*/

//ץȡ�ϲ��ץ�²㶯��
int catch(int direc,int time);

//ץ�²�
void  catch_right_down1(void);
void  catch_left_down1(void);
void  catch_zhong_down1(void);

//�ӵ���ץ
void  catch_right2(void);
void  catch_left2(void);
void  catch_zhong2(void);

//�����Ϸ�
void  put_right2(void);
void  put_left2(void);
void  put_zhong2(void);

//��̨���Ϸ�
void  catch_right3(void);
void  catch_left3(void);
void  catch_zhong3(void);

//�ּӹ����ӻ�����ץ����
void  put_down1(void);
void  put_down2(void);
void  put_down3(void);

//�ּӹ������������Ϸ�
void  catch_down1(void);
void  catch_down2(void);
void  catch_down3(void);

//��ԭ�����������Ϸ�
void  catch_down11(void);
void  catch_down22(void);
void  catch_down33(void);

//ץ�ϲ�
void  catch_right1(void);
void  catch_left1(void);
void  catch_zhong1(void);





#endif
