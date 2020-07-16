#include "DHT11.h"

void DHT11_Read(float *temp,float *hum, uint8_t data[5]){
		*hum= (float)data[0]+(float)data[1]/((data[1]>100)?1000:((data[1]>10)?100:10));
		*temp=(float)data[2]+(float)data[3]/((data[3]>100)?1000:((data[3]>10)?100:10));
}
/*
#include <includes.h>
#include <stdio.h>
extern uint8_t u8Buff[5];
uint8_t data[5]={60,12,28,30,100};
extern uint8_t err;
float temp,hum;
uint8_t a,b,c,d,e;
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
			if(err==0){	
				a=u8Buff[0];
				b=u8Buff[1];
				c=u8Buff[2];
				d=u8Buff[3];
				e=u8Buff[4];
				DHT11_Read(&temp,&hum,u8Buff);
				ledControl(LED1,ON);
				Delay_Ms(100);
				ledControl(LED1,OFF);
				Delay_Ms(100);
			}
	}
}
*/
