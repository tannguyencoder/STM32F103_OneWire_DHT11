#include "ONEWIRE.h"
//--------------ONEWire using for DHT11-----------------------//
uint16_t u16Tim;
uint8_t u8Buff[5];
uint8_t i;
uint8_t err=0;
GPIO_InitTypeDef 		oneInit;
//----------------OneWireConfig-----------------------------//

void control_signal(void){
		//tin hieu keo xuong 0 20ms va day len cao
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_Ms(30);//>18ms l? oke
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
		// Kiem tra keo len muc cao hay la do timeout xay ra
		TIM_SetCounter(TIM3,0);
		while(TIM_GetCounter(TIM3)<10){
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){ 
								break;
						}
				}
		//do gia tri bo dem cua timer2
		u16Tim =TIM_GetCounter(TIM3);
		//TIm out >10 la error
		// Nghia la no ko len muc 1 nen error
		if(u16Tim >=10){ 
				err=1;
		}
		
		//=> Dang High
}
void respond_signal(void){
		//wait PB12=0 trong 5 ->45 micro s
		TIM_SetCounter(TIM3,0);
		while(TIM_GetCounter(TIM3)<45){
						if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){ 
						break;
						}
				}
		u16Tim =TIM_GetCounter(TIM3);
		// No khong co xuong thap => error
		if((u16Tim >=45)||(u16Tim <=5)){ 
			err=1;
		}
		//-> dang low
}
void ready_signal(void){
	//wait xung low : 70-90 mico s
	//wait xung high: 75-95 micro s
	//wait chan PB12 len cao
	TIM_SetCounter(TIM3,0);
	//KT xem trong 90 mms do co len high chua
	while(TIM_GetCounter(TIM2)<90){
					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){ 
					break;
					}
			}
	u16Tim =TIM_GetCounter(TIM3);
	// No khong co xuong thap => error
	if((u16Tim >=90)||(u16Tim <=70)){ 
			err=1;
	}
	//->dang high
	
	//wait chan PB12 xuong thap 
	TIM_SetCounter(TIM3,0);
	//Kiem tra trong 95mms co xuong low chua
	while(TIM_GetCounter(TIM3)<95){
					if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){ 
					break;
					}
			}
	u16Tim =TIM_GetCounter(TIM3);
	// No khong co xuong thap => error
	if((u16Tim >=95)||(u16Tim <=75)){ 
			err=1;
	}
	//->dang low
	//done check
}
void read_data(uint8_t index){
		for (i = 0; i < 8; ++i) {
			//wait bit 0 (45-65msm)
			//Neu 1(45-80) =>bit1
			//Neu 0 (10-45) => bit0
			/* cho chan PB12 len cao */
			TIM_SetCounter(TIM3, 0);
			while (TIM_GetCounter(TIM3) < 65) {
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM3);
			if ((u16Tim >= 65) || (u16Tim <= 45)) {
				err=1;
			}
			
			/* cho chan PB12 xuong thap */
			TIM_SetCounter(TIM3, 0);
			while (TIM_GetCounter(TIM3) < 80) {
				if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
					break;
				}
			}
			u16Tim = TIM_GetCounter(TIM3);
			if ((u16Tim >= 80) || (u16Tim <= 10)) {
				err=1;
			}
			u8Buff[index] <<= 1;
			if (u16Tim > 45) {
				/* nhan duoc bit 1 */
				u8Buff[index] |= 1;
			} else {
				/* nhan duoc bit 0 */
				u8Buff[index] &= ~1;
			}
		}
}
void check_sum(void){
		if (u8Buff[4] !=(u8Buff[0]+u8Buff[1]+u8Buff[2]+u8Buff[3])){err=1;}
}

void One_Wire(void){
		err=0;
		uint8_t c;
		control_signal();
		respond_signal();
		ready_signal();
		for(c=0;c<5;c++){
			read_data(c);
		}
		check_sum();
}
void One_wireInit(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		oneInit.GPIO_Mode = GPIO_Mode_Out_OD;
		oneInit.GPIO_Pin = GPIO_Pin_12;
		oneInit.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &oneInit);	
}

/*
#include <includes.h>
#include <stdio.h>
extern uint8_t u8Buff[5];
extern uint8_t err;
int main(void){
	DELAY_Config();
	RX_Config();
	USART_Config();
	TX_Config();
	ledInit();
	One_wireInit();
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while(1){
			One_Wire();
			Delay_Ms(1000);
			if(err==0){	
				USART_SendData(USART3,0xFE);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};
				Delay_Ms(50);
				USART_SendData(USART3,u8Buff[0]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};
				Delay_Ms(50);
				USART_SendData(USART3,u8Buff[1]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};
				Delay_Ms(50);
				USART_SendData(USART3,u8Buff[2]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};
				Delay_Ms(50);
				USART_SendData(USART3,u8Buff[3]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};		
				ledControl(LED1,ON);
				Delay_Ms(100);
				ledControl(LED1,OFF);
				Delay_Ms(100);
			}
	}
}
*/