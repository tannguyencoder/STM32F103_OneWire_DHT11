#ifndef __YS201_H
#define __YS201_H 			   
#include "includes.h"
//2s for readYs201.
extern uint32_t flowrate;

float readYs201(void);
void Ys201Deinit(void);
void Ys201Init(void);
#endif