#include "stm32f4xx.h"
#include "delay.h"
#include "USART.h"
#include "DFC.h"
#include "ESP8266_AT.h"
#include "Snake.h"
int main(void)
{
	ESP8266_InitTypeDef ESP8266_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	delay_init(168);
	
	USART_ConfigInit(USART2,115200);
	
	DFC_Init();
	
	TFTLCD_Init();
	TFTLCD_DisplayModeConfig(DisplayMode_V_Default);
	TFTLCD_FontDisplayConfig(ASCII3216,0xffffff);
	
	RetroSnaker_Init();
	
	ESP8266_InitStructure.ESP8266_Mode=Mode_SAP;
	ESP8266_InitStructure.ESP8266_SSID="Lishaoyin";
	ESP8266_InitStructure.ESP8266_Password="123456789";
	ESP8266_InitStructure.ESP8266_SAPChannel=6;
	ESP8266_InitStructure.ESP8266_SAPEcn=4;
	ESP8266_InitStructure.ESP8266_MutiConnectCmd=ENABLE;
	ESP8266_InitStructure.ESP8266_CIPServerCmd=ENABLE;
	ESP8266_InitStructure.ESP8266_ServerPort="333";
	ESP8266_Init(&ESP8266_InitStructure);
	
	while(1)
	{
		if(DFC_DataCapture("Start/Stop")) Snake_Cmd(Cmd_Start_Stop);
		if(DFC_DataCapture("Reset")) Snake_Cmd(Cmd_Restart);
		if(DFC_DataCapture("TurnRight")) Snake_Turn(DIR_R);
		else if(DFC_DataCapture("TurnDown")) Snake_Turn(DIR_D);
		else if(DFC_DataCapture("TurnLeft")) Snake_Turn(DIR_L);
		else if(DFC_DataCapture("TurnUp")) Snake_Turn(DIR_U);
		Snake_Move();
		
	}
}
