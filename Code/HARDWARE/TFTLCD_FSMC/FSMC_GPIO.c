#include "stm32f4xx.h"
#include "FSMC.h"

//This FSMC GPIO Config Function is for STM32F407 FSMC_Bank1
/*
FSMC has 4 Bank(FSMC_Bank1~FSMC_Bank4),Every Bank has different Function ,
TFTLCD is similar to SARM,so here using FSMC_Bank1,Every Bank is devided into 4 Areas,
Every Area can Control a SRAM
*/
void FSMC_GPIOConfigInit(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	//CS Line for TFTLCD,GPIOD_Pin7 is multiplexed to FSMC_NE1
	/*
	FSMC_NEx be Enabed ,the FSMC_BankX_Areax is Enabled
	*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;  
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);
	
	//RS Line for TFTLCD,GPIOD_Pin_11 is multiplexed to FSMC_A16
	/*
	FSMC_A0~FSMC_A25 is the Adress Line for All SRAM mounted on FSMC_Bank1,
	FSMC_Bank1 is devided into 4 Areas,FSMC_NE1~FSMC_NE4 is the CS Line to Distinguish Area1 to Area4,
	HADDR[25:0] is the FSMC Internal Register to Control FSMC_A0~FSMC_A25,When FSMC Transmitting 8Bit-Data,
	HADDR[25:0] in response to FSMC_A[25:0],When FSMC Transmitting 16Bit-Data,HADDR[25:1] in response to FSMC_A[24:0]
	Here only FSMC_A16 is used,when FSMC_A16 is Low,the Data to TFTLCD is Command Byte,when FSMC_A16 is High, the Data to 
	TFTLCD is RGB565 Data
	*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;  
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);
	
	//FSMC_NWE,Writting Signal of FSMC
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;  //WR
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);
	
	//FSMC_NOE,Reading Signal of FSMC
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;  //RD
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
	
	//FSMC_D0
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;  //D0
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
	
	//FSMC_D1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;  //D1
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);
	
	//FSMC_D2
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;  //D2
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
	
	//FSMC_D3
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;  //D3
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
	
	//FSMC_D4
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;  //D4
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);
	
	//FSMC_D5
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;  //D5
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
	
	//FSMC_D6
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;  //D6
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
	
	//FSMC_D7
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;  //D7
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
	
	//FSMC_D8
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;  //D8
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
	
	//FSMC_D9
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;  //D9
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
	
	//FSMC_D10
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;  //D10
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
	
	//FSMC_D11
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;  //D11
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
	
	//FSMC_D12
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;  //D12
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);
	
	//FSMC_D13
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;  //D13
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);
	
	//FSMC_D14
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;  //D14
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
	
	//FSMC_D15
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;  //D15
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	
}
