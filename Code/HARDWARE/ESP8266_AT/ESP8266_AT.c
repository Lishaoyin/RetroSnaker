#include "stm32f4xx.h"
#include "ESP8266_AT.h"
#include "USART.h"
#include "delay.h"

//ESP8266 Send CRLF
void ESP8266_SendEnter(void)
{
	ESP8266_SendByte(0x0d);
	ESP8266_SendByte(0x0a);
}

void ESP8266_RST(void)
{
	ESP8266_SendString("AT+RST");
	ESP8266_SendEnter();
	delay_ms(500);   //Wait for ESP8266 Returning Data Complete
}

//ESP8266 ConfigMode Mode_STA/Mode_SAP/Mode_STA_SAP
void ESP8266_ModeConfig(u8 Mode)
{
	if(Mode==Mode_STA) ESP8266_SendString("AT+CWMODE=1");
	else if(Mode==Mode_SAP) ESP8266_SendString("AT+CWMODE=2");
	else if(Mode==Mode_STA_SAP) ESP8266_SendString("AT+CWMODE=3");
	ESP8266_SendEnter();
	delay_ms(500);   //Wait for ESP8266 Returning Data Complete
	ESP8266_RST();
}

//When ESP8266 Set Station Mode(Mode_STA),Connect Server's Wifi  "AT+CWJAP="SSID","PassWord""
void ESP8266_STAWifiConnect(u8 *SSID,u8 *PassWord)
{
	ESP8266_SendString("AT+CWJAP=");
	ESP8266_SendByte('"');
	ESP8266_SendString(SSID);
	ESP8266_SendByte('"');
	ESP8266_SendByte(',');
	ESP8266_SendByte('"');
	ESP8266_SendString(PassWord);
	ESP8266_SendByte('"');
	ESP8266_SendEnter();
	delay_ms(500);  //Wait for ESP8266 Returning Data Complete
}

//When ESP8266 Set Station Mode(Mode_STA),Connect Server's IP  "AT+CIPSTART="TCP","IP",Port"
void ESP8266_STAServerConnect(u8 *ServerIP,u8 *Port)
{
	ESP8266_SendString("AT+CIPSTART=");
	ESP8266_SendByte('"');
	ESP8266_SendString("TCP");
	ESP8266_SendByte('"');
	ESP8266_SendByte(',');
	ESP8266_SendByte('"');
	ESP8266_SendString(ServerIP);
	ESP8266_SendByte('"');
	ESP8266_SendByte(',');
	ESP8266_SendString(Port);
	ESP8266_SendEnter();
	delay_ms(500);  //Wait for ESP8266 Returning Data Complete
}

//"AT+CIPMUX=1/0"
void ESP8266_MultiConnectCmd(FunctionalState NewState)
{
	if(NewState==ENABLE) ESP8266_SendString("AT+CIPMUX=1");
	else if(NewState==DISABLE) ESP8266_SendString("AT+CIPMUX=0");
	ESP8266_SendEnter();
	delay_ms(500);  //Wait for ESP8266 Returning Data Complete
}

//When ESP8266 Set Server Mode(Mode_SAP),Config ESP8266 Wifi   "AT+CWSAP="SSID","PassWord",Chl,Ecn"
void ESP8266_SAPWifiConfig(u8 *SSID,u8 *PassWord,u8 Chl,u8 Ecn)
{
	ESP8266_SendString("AT+CWSAP=");
	ESP8266_SendByte('"');
	ESP8266_SendString(SSID);
	ESP8266_SendByte('"');
	ESP8266_SendByte(',');
	ESP8266_SendByte('"');
	ESP8266_SendString(PassWord);
	ESP8266_SendByte('"');
	ESP8266_SendByte(',');
	ESP8266_SendByte(Chl+0x30);
	ESP8266_SendByte(',');
	ESP8266_SendByte(Ecn+0x30);
	ESP8266_SendEnter();
	delay_ms(500);  //Wait for ESP8266 Returning Data Complete
}

//When ESP8266 Set Server Mode(Mode_SAP),Config ESP8266 IP "AT+CIPSERVER=1/0,Port"
void ESP8266_SAPServerConfig(FunctionalState NewState,u8 *Port)
{
	if(NewState==ENABLE) 
	{
		ESP8266_SendString("AT+CIPSERVER=1,");
		ESP8266_SendString(Port);
	}
	else if(NewState==DISABLE) ESP8266_SendString("AT+CIPSERVER=0");
	ESP8266_SendEnter();
	delay_ms(500);  //Wait for ESP8266 Returning Data Complete
}
/*
//ESP8266 Send Data to Station "AT+CIPSEND=Station(0-5),DataLength"
void ESP8266_SAPSendData(u8 Station,u32 DataLength,u8 *Data)
{
	ESP8266_SendString("AT+CIPSEND=");
	ESP8266_SendByte(Station+0x30);  //Transform to ASCII
	ESP8266_SendByte(',');
	ESP8266_SendByte(DataLength+0x30);   //Transform to ASCII
	ESP8266_SendEnter();
	delay_us(10);
	ESP8266_SendBytes(DataLength,Data);
}
*/
/*
//ESP8266 Send Data to Server "AT+CIPSEND=DataLength"
void ESP8266_STASendData(u32 DataLength,u8 *Data)
{
	ESP8266_SendString("AT+CIPSEND=");
	ESP8266_SendByte(DataLength+0x30);
	ESP8266_SendEnter();
	delay_us(10);
	ESP8266_SendBytes(DataLength,Data);
}
*/
//Use Structure Config ESP8266
void ESP8266_Init(ESP8266_InitTypeDef *ESP8266_InitStruct)
{
	ESP8266_ModeConfig(ESP8266_InitStruct->ESP8266_Mode);
	if(ESP8266_InitStruct->ESP8266_Mode==Mode_STA)
	{
		ESP8266_STAWifiConnect(ESP8266_InitStruct->ESP8266_SSID,ESP8266_InitStruct->ESP8266_Password);
		ESP8266_MultiConnectCmd(ESP8266_InitStruct->ESP8266_MutiConnectCmd);
		ESP8266_STAServerConnect(ESP8266_InitStruct->ESP8266_ServerIP,ESP8266_InitStruct->ESP8266_ServerPort);
	}
	else if(ESP8266_InitStruct->ESP8266_Mode==Mode_SAP)
	{
		ESP8266_SAPWifiConfig(ESP8266_InitStruct->ESP8266_SSID,ESP8266_InitStruct->ESP8266_Password,ESP8266_InitStruct->ESP8266_SAPChannel,ESP8266_InitStruct->ESP8266_SAPEcn);
		ESP8266_MultiConnectCmd(ESP8266_InitStruct->ESP8266_MutiConnectCmd);
		ESP8266_SAPServerConfig(ESP8266_InitStruct->ESP8266_CIPServerCmd,ESP8266_InitStruct->ESP8266_ServerPort);
	}
	delay_ms(50);  //Wait for ESP8266 Returning Data Complete
}
