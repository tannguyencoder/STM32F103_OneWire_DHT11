#include "RS485.h"
uint8_t data1[100];
GPIO_InitTypeDef 	gpioControl;

void initGPIO_Control(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioControl.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioControl.GPIO_Pin = GPIO_Pin_10;
	gpioControl.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioControl);
}

void Receive_Enable(void){
    GPIO_ResetBits(GPIOA,GPIO_Pin_10);
}

void Send_Enable(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_10);
}
int Check_Address(uint8_t dt_addr,uint8_t addr){
    if(dt_addr ==addr) return 1;
    else return -1;
}
void Send_Data8(uint8_t data){
    USART_SendData(USART3,data);
    while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};
	Delay_Ms(5);
}
/*-------------------MASTER---------------------*/
//using for CLIMATE and MIX
void RequestData(uint8_t dt_addr,uint8_t function){
    uint8_t fram[4]={START,dt_addr,function,STOP};
    Send_Enable();
    USART_PutString(fram);
    Receive_Enable();
}
//using for raspberry
/*
#include <includes.h>
extern uint8_t u8Buff[5];
extern uint8_t err;
float temp,hum;
float testHumid,testTemp;
char result[11];
int main(void){
	DELAY_Config();
	RX_Config();
	USART_Config();
	TX_Config();
	ledInit();
	One_wireInit();
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while(1){
			Delay_Ms(1000);
			One_Wire();
			if(err==0){	
				DHT11_Read(&temp,&hum,u8Buff);
				sprintf(result,"%0.2f,%0.2f",temp,hum);
				send2ras(0xFE,0xF1,result,0XF0);
				ledControl(LED1,ON);
				Delay_Ms(10);
				ledControl(LED1,OFF);
				Delay_Ms(10);
			}
	}
}
*/