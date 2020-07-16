#include "LED.h"

GPIO_InitTypeDef 		led;

//--------------------------------Config Led -PA8-PD2-------------------------------------//
void ledInit(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		led.GPIO_Mode = GPIO_Mode_Out_PP;
		led.GPIO_Pin = PIN_LED0;
		led.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(PORT_LED0, &led);	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		led.GPIO_Mode = GPIO_Mode_Out_PP;
		led.GPIO_Pin = PIN_LED1;
		led.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(PORT_LED1, &led);	
}

void ledControl(enum ledNumber led,enum ledState State){
	if(led ==LED0){
		if(State==ON) GPIO_SetBits(PORT_LED1,PIN_LED1);
		else GPIO_ResetBits(PORT_LED0,PIN_LED0);
	}
	else{
		if(State==ON) GPIO_SetBits(PORT_LED1,PIN_LED1);
		else GPIO_ResetBits(PORT_LED1,PIN_LED1);
	}
	
}
