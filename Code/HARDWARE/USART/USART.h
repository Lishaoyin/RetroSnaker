#include "stm32f4xx.h"
#include "delay.h"

#ifndef _USART_H
#define _USART_H



#endif

void USART_ConfigInit(USART_TypeDef* USARTx,u32 BaudRate);
void USART_SendByte(USART_TypeDef* USARTx,u8 Byte);
void USART_SendString(USART_TypeDef* USARTx,u8 *String);

//USARTx_GPIOConfigInit
void USART1_GPIOConfigInit(void);
void USART2_GPIOConfigInit(void);
void USART3_GPIOConfigInit(void);
/*More...*/

//USARTx_NVICConfigInit
void USART1_NVICConfigInit(void);
void USART2_NVICConfigInit(void);
void USART3_NVICConfigInit(void);
/*More...*/

