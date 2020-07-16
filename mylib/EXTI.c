#include "EXTI.h"
GPIO_InitTypeDef 					GPIO_InitStructure;	//GPIO struct
EXTI_InitTypeDef 					EXTI_InitStructure; // EXTI struct
NVIC_InitTypeDef 					NVIC_InitStructure; // NVIC struct 

//--------------------------------Timer interupts--------------------------------------//
void EXTI_Config_TIM2(void){
	TIM_TimeBaseInitTypeDef timInit; //Khai bao truong Timer
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
	timInit.TIM_Prescaler = 7200-1; //He so chia la 7200
	timInit.TIM_Period=10000-1;
	timInit.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &timInit);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//clear update flag
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//enable update interrupt
	TIM_Cmd(TIM2,ENABLE);// khoi dong 
	//vectorngat
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//--------------------------------External interrupt PC13 YS201------------------------------//
void EXTI_config_13(void)	{
		//cap clock cho ngat ngoai va ngoai vi
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		/* mapping */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
		/* Clear the the EXTI line interrupt pending bit */
		EXTI_ClearITPendingBit(EXTI_Line13);
		/*EXTI line Configuration */
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line13;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		/*NVIC Configuration*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//uu ti�n hon
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
//--------------------------------External interrupt PC3 TEST-------------------------------//
void EXTI_config_3(void){
		//cap clock cho ngat ngoai va ngoai vi
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		/* mapping */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
		/* Clear the the EXTI line interrupt pending bit */
		EXTI_ClearITPendingBit(EXTI_Line3);
		/*EXTI line Configuration */
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		/*NVIC Configuration*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
//--------------------------------External interrupt PC1 TEST-------------------------------//
void EXTI_config_1(void){
	//cap clock cho ngat ngoai va ngoai vi
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		/* mapping */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
		/* Clear the the EXTI line interrupt pending bit */
		EXTI_ClearITPendingBit(EXTI_Line1);
		/*EXTI line Configuration */
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line1;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		/*NVIC Configuration*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
