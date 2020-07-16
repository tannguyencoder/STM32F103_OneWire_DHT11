#ifndef __DHT11_H
#define __DHT11_H 			   
#include "stm32f10x.h"
#include "UART.h"
#include "ONEWIRE.h"
void DHT11_Read(float *temp,float *hum, uint8_t data[5]);
#endif