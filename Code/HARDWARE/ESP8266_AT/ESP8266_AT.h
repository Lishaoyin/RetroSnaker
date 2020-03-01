#include "stm32f4xx.h"



#ifndef _ESP8266_AT_H
#define _ESP8266_AT_H

#define USART_ESP8266 USART2
#define ESP8266_SendByte(Data) USART_SendByte(USART_ESP8266,Data)
#define ESP8266_SendBytes(DataLength,Data) USART_SendBytes(USART_ESP8266,DataLength,Data)
#define ESP8266_SendString(Data) USART_SendString(USART_ESP8266,Data)
#define ESP8266_Cmd(NewState) USART_Cmd(USART_ESP8266,NewState)
#define ESP8266_StringCompare(String) USART_DataStreamCompare(String)

#define Mode_STA 0x01
#define Mode_SAP 0x02
#define Mode_STA_SAP 0x03

#endif

typedef struct
{
	u8 ESP8266_Mode;
	FunctionalState ESP8266_MutiConnectCmd;
	u8 *ESP8266_SSID;
	u8 *ESP8266_Password;
	u8 ESP8266_SAPChannel;
	u8 ESP8266_SAPEcn;
	FunctionalState ESP8266_CIPServerCmd;
	u8 *ESP8266_ServerIP;
	u8 *ESP8266_ServerPort;
} ESP8266_InitTypeDef;


void ESP8266_SendEnter(void);
void ESP8266_RST(void);
void ESP8266_ModeConfig(u8 Mode);
void ESP8266_STAWifiConnect(u8 *SSID,u8 *PassWord);
void ESP8266_STAServerConnect(u8 *ServerIP,u8 *Port);
void ESP8266_MultiConnectCmd(FunctionalState NewState);
void ESP8266_SAPWifiConfig(u8*SSID,u8 *PassWord,u8 Chl,u8 Ecn);
void ESP8266_SAPServerConfig(FunctionalState NewState,u8 *Port);
void ESP8266_SAPSendData(u8 Station,u32 DataLength,u8 *Data);
void ESP8266_STASendData(u32 DataLength,u8 *Data);
void ESP8266_Init(ESP8266_InitTypeDef *ESP8266_InitStruct);
