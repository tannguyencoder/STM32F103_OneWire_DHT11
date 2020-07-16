#ifndef __ONEWIRE_H
#define __ONEWIRE_H 			   

#include "includes.h"

void control_signal(void);
void respond_signal(void);
void ready_signal(void);
void read_data(uint8_t index);
void check_sum(void);
void One_Wire(void);
void One_wireInit(void);

#endif
