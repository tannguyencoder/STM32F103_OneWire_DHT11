#ifndef __LED_H
#define __LED_H 			   
#include "includes.h"

#define PIN_LED0   GPIO_Pin_8
#define PORT_LED0  GPIOA
#define PIN_LED1 	 GPIO_Pin_2
#define PORT_LED1  GPIOD
enum ledState {OFF=0,ON=1};
enum ledNumber{LED0=0,LED1=1};



void ledInit(void);
void ledControl(enum ledNumber led,enum ledState State);
#endif
