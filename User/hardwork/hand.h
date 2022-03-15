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


///////////////模块化函数///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rough_position(uint8_t *qr_code);

void half_position(uint8_t *qr_code);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//brief:排序抓取函数   抓下层和抓下层
void rank_catch(uint8_t *qr_code,uint8_t *color,int time,int num);

//抓取上层和抓下层动作
int catch(int direc,int time);

//    1表示从原料区往货架上方  2表示从粗加工区往货架上放
void law_out(int direc,int time) ;

//往粗加工区放
void law_grand1(int direc);

void law_grand2(int direc);

//从货架上抓取  1表示红色 以及红色货架的位置
void clamp (int direc);





/* 步骤分函数*/

//抓取上层和抓下层动作
int catch(int direc,int time);

//抓下层
void  catch_right_down1(void);
void  catch_left_down1(void);
void  catch_zhong_down1(void);

//从地上抓
void  catch_right2(void);
void  catch_left2(void);
void  catch_zhong2(void);

//往地上放
void  put_right2(void);
void  put_left2(void);
void  put_zhong2(void);

//往台子上放
void  catch_right3(void);
void  catch_left3(void);
void  catch_zhong3(void);

//粗加工区从货架上抓起来
void  put_down1(void);
void  put_down2(void);
void  put_down3(void);

//粗加工区从往货架上放
void  catch_down1(void);
void  catch_down2(void);
void  catch_down3(void);

//从原料区往货架上放
void  catch_down11(void);
void  catch_down22(void);
void  catch_down33(void);

//抓上层
void  catch_right1(void);
void  catch_left1(void);
void  catch_zhong1(void);





#endif
