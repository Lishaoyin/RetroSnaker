#include "stm32f4xx.h"
#include "FSMC.h"

void FSMC_ConfigInit(void)
{
	FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTimingInitStructure;	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;	
	
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);	//ENABLE FSMC RCC Clock
	
	//FSMC_Timming Config
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime      = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime       = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime         = 0x03;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision           = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency           = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode            = FSMC_AccessMode_A;	       //FSMC_Mode_A

	FSMC_NORSRAMInitStructure.FSMC_Bank 				               = FSMC_Bank1_NORSRAM1;	     //FSMC_Bank1_Area1		
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux 	           = FSMC_DataAddressMux_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType 		             = FSMC_MemoryType_SRAM;			
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth 	           = FSMC_MemoryDataWidth_16b;		
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode 	           = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity          = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait	           = FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode 			             = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive            = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation 	           = FSMC_WriteOperation_Enable;					
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal 		             = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode		             = FSMC_ExtendedMode_Enable; 	
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst 		             = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct           = &FSMC_NORSRAMTimingInitStructure;  

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);              //Init FSMC
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);              //ENABLE FSMC
	
}
