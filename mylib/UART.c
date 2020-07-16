#include "UART.h"

USART_InitTypeDef					usartInit;
GPIO_InitTypeDef 					gpioInit;


//--------------------------------TX Config - PB10-------------------------------------//
void TX_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInit);
}

//--------------------------------RX Config - PB11-------------------------------------//
void RX_Config(void){
	//PB11-UART3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_11;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInit);
}
//--------------------------------USART_Config - USART3--------------------------------//
void USART_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	usartInit.USART_BaudRate=9600;
	//khong bat tay
	usartInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	//vua truyen vua nha
	usartInit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usartInit.USART_Parity=USART_Parity_No;
	//1 bit stop
	usartInit.USART_StopBits=USART_StopBits_1;
	usartInit.USART_WordLength= USART_WordLength_8b;
	USART_Init(USART3,&usartInit);
	USART_Cmd(USART3,ENABLE);
}
//--------------------------------Send Char--------------------------------------------//
void USART_PutChar(char c){
    // Cho cho den khi san sang nhan du lieu
	while (!USART_GetFlagStatus(USART3, USART_FLAG_TXE)){};
    // Gui du lieu
  USART_SendData(USART3, c);
	Delay_Ms(10);
}
//--------------------------------Send String------------------------------------------//
void USART_PutString(char *s){
    // 
	while (*s)
  {
		USART_PutChar(*s++);
  }
}
//--------------------------------receive Char--------------------------------------------//
char USART_GetChar(){
    // Cho cho den khi san sang nhan du lieu
	while (!USART_GetFlagStatus(USART3, USART_FLAG_RXNE)){};
    // Doc du lieu nhan duoc
  return USART_ReceiveData(USART3);
}
//--------------------------------Receive String------------------------------------------//
void USART_GetString(char *string){
		char i=0,j=0;
		do{
			*(string+i)=USART_GetChar();
			j=*(string+i);
			USART_PutChar(*(string+i));
			i++;
		}while((1));
}
//Using when maincontroler recevice data from raspberry
void s2f(float *data1,float *data2, char data[100]){
		char *token = strtok(data, ",");
		int t=0;
				//Duyet qua cac 
				while(token !=NULL){					
					t++;
					if(t==1)*data1=atof(token);
					else{*data2=atof(token);t=0;}
					token = strtok(NULL,",");
				}
}
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
	char * token;
	while(1){
			char tm[10];
			One_Wire();
			Delay_Ms(1000);
			if(err==0){	
				DHT11_Read(&temp,&hum,u8Buff);
				USART_PutString("--------------------------------------");
				USART_PutString("\n");
				sprintf(result,"%0.2f,%0.2f",temp,hum);
				USART_PutString(result);
   			USART_PutString("\n");
				s2f(&testHumid,&testTemp,result);
				ledControl(LED1,ON);
				Delay_Ms(100);
				ledControl(LED1,OFF);
				Delay_Ms(100);
			}
	}
}*/

//send data to ras
void send2ras(uint8_t start,uint8_t address,char data[],uint8_t stop){
			USART_PutChar(start);
			Delay_Ms(10);
			USART_PutChar(address);
			Delay_Ms(10);
			USART_PutString(data);
			Delay_Ms(10);
			USART_PutChar(stop);
			Delay_Ms(10);
}
//--------------------------------TX Config - PA2-------------------------------------//
void TX_Config2(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_2;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInit);
}

//--------------------------------RX Config - PA3-------------------------------------//
void RX_Config2(void){
	//PB11-UART3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_3;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInit);
}
//--------------------------------USART_Config - USART2--------------------------------//
void USART2_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	usartInit.USART_BaudRate=9600;
	//khong bat tay
	usartInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	//vua truyen vua nha
	usartInit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	usartInit.USART_Parity=USART_Parity_No;
	//1 bit stop
	usartInit.USART_StopBits=USART_StopBits_1;
	usartInit.USART_WordLength= USART_WordLength_8b;
	USART_Init(USART2,&usartInit);
	USART_Cmd(USART2,ENABLE);
}
//--------------------------------Send Char--------------------------------------------//
void USART2_PutChar(char c){
    // Cho cho den khi san sang nhan du lieu
	while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE)){};
    // Gui du lieu
  USART_SendData(USART2, c);
	Delay_Ms(10);
}
//--------------------------------Send String------------------------------------------//
void USART2_PutString(char *s){
    // 
	while (*s)
  {
		USART2_PutChar(*s++);
  }
}//--------------------------------receive Char--------------------------------------------//
char USART2_GetChar(){
    // Cho cho den khi san sang nhan du lieu
	while (!USART_GetFlagStatus(USART2, USART_FLAG_RXNE)){};
    // Doc du lieu nhan duoc
  return USART_ReceiveData(USART2);
}
