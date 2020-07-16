#ifndef __RS485_H
#define __RS485_H 			   

#include "stm32f10x.h"
#include "UART.h"
//Define START, STOP
#define START           0xF1
#define STOP            0xF2
//Define Function
#define OK              0xE1
#define NOTOK           0xE2
#define REQUEST         0xE3
//Define Address
#define ADDRESS_CLIMATE 0x40
#define ADDRESS_MIX     0x50
#define ADDRESS_MASTER  0x60
#define ADDRESS_RASP    0x70



#endif
