#ifndef __CONTROL__
#define __CONTROL__
#include "stm32f10x.h"  
#include "bsp_usart.h"
#include "speed.h"
#include "timer.h"
#include "road.h"
#include "direction.h"
void move_step(void);
void Init_all(void);
void  main_control_1(void);
void  main_control_2(void);
#endif


