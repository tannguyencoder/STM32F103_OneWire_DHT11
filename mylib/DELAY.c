#include "DELAY.h"

TIM_TimeBaseInitTypeDef 	timerInit;

//--------------------------------Delay-Config -TIMER3-------------------------------------//
void DELAY_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	timerInit.TIM_CounterMode= TIM_CounterMode_Up;
	timerInit.TIM_Period=0xffff; // mac dinh
	//tao la timer 1/10^6 s
	timerInit.TIM_Prescaler=72-1;
	//cau hinh timer
	TIM_TimeBaseInit(TIM3,&timerInit);
	TIM_Cmd(TIM3,ENABLE);
}
//--------------------------------Function Delay 1ms--------------------------------------//
void Delay1Ms(void){
	TIM_SetCounter(TIM3,0);
	while (TIM_GetCounter(TIM3)<1000){}
}
//--------------------------------Function Delay N ms-------------------------------------//
void Delay_Ms(uint32_t T_ms){
	while(T_ms)
	{
		Delay1Ms();
		--T_ms;
	}
}
//--------------------------------Function Delay N us-------------------------------------//
void delay_us(uint32_t delay){
	TIM_SetCounter(TIM3,0);
	while (TIM_GetCounter(TIM3)<delay){}
}
