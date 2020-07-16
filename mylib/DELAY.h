#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f10x.h"

void DELAY_Config(void);
void Delay1Ms(void);
void Delay_Ms(uint32_t T_ms);
void delay_us(uint32_t delay);

#endif
