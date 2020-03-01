#include "USART.h"
#include "DFC.h"
//Config and Init USARTx
void USART_ConfigInit(USART_TypeDef* USARTx,u32 BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	//STM32F4xx USARTx RCC_Clock
	if(USARTx==USART1) 
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		USART1_GPIOConfigInit();
		USART1_NVICConfigInit();
	}
	else if(USARTx==USART2) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		USART2_GPIOConfigInit();
		USART2_NVICConfigInit();
	}
	else if(USARTx==USART3) 
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		USART3_GPIOConfigInit();
		USART3_NVICConfigInit();
	}
  /*More...*/
	
	//USARTx Config
	USART_InitStructure.USART_BaudRate=BaudRate;
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;
  USART_InitStructure.USART_StopBits=USART_StopBits_1;
  USART_InitStructure.USART_Parity=USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_Init(USARTx,&USART_InitStructure);
	
	//Interrupt Config
	USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);     //Enable USART RXNE Interrupt
	//USART_ITConfig(USARTx,USART_IT_TC,ENABLE);     //Enable USART TC Interrupt
	
	USART_Cmd(USARTx,ENABLE);

}

//USART Send one Byte
void USART_SendByte(USART_TypeDef* USARTx,u8 Byte)
{
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);     //Wait for the previous Byte Sent complete
	USART_SendData(USARTx,Byte);
	delay_us(10);      //Wait for last Byte Sent complete
}

//USART Send String,no need to know how many Bytes,But it CAN ONLY Send String
void USART_SendString(USART_TypeDef* USARTx,u8 *String)
{
	while(*String!=0)  //The Vale of the last element is 0(not '0')
	{
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
		USART_SendData(USARTx,*String);
		String++;
	}
	delay_us(10);      //Wait for last Byte Sent complete
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		DFC_DataStore(USART_ReceiveData(USART2));
	}
}
