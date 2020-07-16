#ifndef __UART_H
#define __UART_H 			   
#include "includes.h"

//----------------UARTConfig-----------------------------//
void TX_Config(void);
void RX_Config(void);
void USART_Config(void);
char USART_GetChar(void);
void USART_GetString(char *string);
void USART_PutChar(char c);
void USART_PutString(char *s);
void TX_Config2(void);
void RX_Config2(void);
void USART2_Config(void);
void USART2_PutChar(char c);
void USART2_PutString(char *s);
char USART2_GetChar(void);
char *USART2_GetString(void);
void s2f(float *data1,float *data2, char data[100]);

void send2ras(uint8_t start,uint8_t address,char data[],uint8_t stop);
#endif
