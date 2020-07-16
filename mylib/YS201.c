#include "YS201.h"

float LWater=0;
uint32_t timerWaterCount=0;
uint32_t flowrate=0;

float readYs201(void){
	NVIC_DisableIRQ(TIM2_IRQn);
	return flowrate/7.5;
}
void Ys201Deinit(void){
	NVIC_DisableIRQ(TIM2_IRQn);
}
void Ys201Init(void){
	//Disable interup Lin13(PC13)
	NVIC_DisableIRQ(EXTI15_10_IRQn);
}
void ControlPump(uint32_t waterSet,uint32_t waterPump){
	if(waterPump>waterSet){
			//Stoppump
			NVIC_DisableIRQ(TIM2_IRQn);
			//timerWaterCount=0;
			//LWater=0;
		}
	else{
			//pump
		}
}
//char str1[10];
//uint32_t flowrate=0;
//float readYs201(void){
//	return flowrate/7.5;
//}
	/*sprintf(str, "%f", Read_ADC());
			USART_PutString(str);
			USART_PutString("\n");
			Delay_Ms(6000);*/
/*int main(void)
//{	
//	char str[20];
//	TX_Config();
//	RX_Config();
//	USART_Config();
//	LED_init();
//	DELAY_Config();
//	EXTI_Config_TIM2();
//	EXTI_config_13();
//	NVIC_DisableIRQ(EXTI15_10_IRQn);
//	//EXTI_config_1();
//  while (1)
//  {		

//			sprintf(str, "%f", readYs201());
//			USART_PutString(str);
//			USART_PutString(" ---- L/min");
//			USART_PutString("\n");
//			Delay_Ms(6000);
//		}
//}*/
/*
#include <includes.h>
extern uint32_t flowrate;
extern uint32_t timerWaterCount;
extern float LWater;
int main(void)
{	
	ledInit();
	DELAY_Config();
	EXTI_Config_TIM2();
	EXTI_config_13();
	NVIC_DisableIRQ(EXTI15_10_IRQn);
  while (1)
  {							
				ledControl(LED0,ON);
				Delay_Ms(10);
				ledControl(LED1,OFF);
				Delay_Ms(10);
		
		}
}

*/
