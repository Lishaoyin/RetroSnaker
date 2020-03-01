#include "stm32f4xx.h"
#include "FSMC.h"
#include "Font_ASCII.h"
#include "delay.h"

#ifndef _TFTLCD_H
#define _TFTLCD_H

#define TFTLCD_BackLight_ON GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define TFTLCD_BackLight_OFF GPIO_ResetBits(GPIOD,GPIO_Pin_12)

/*The Start Address of FSMC_Bank1 is 0x60000000
when HADDR[25:0]=0x60000000,FSMC_A[25:0] All Pin is Low
When Write Command,Pin TFTLCD_RS must be Low
*/
#define TFTLCD_Register_Addr_Pointer 0x60000000
#define TFTLCD_Register_Addr *(volatile u16*)(TFTLCD_Register_Addr_Pointer) //*(volatile u16*) is used to avoid Compiler Optimizing Data Flow

/*TFTLCD is 16Bit-Data,So HADDR[25:1] in response to FSMC_A[24:0],Here connect Pin TFTLCD_RS with FSMC_A16,When Wirte Data,
Pin TFTLCD_RS must be High,this needs HADDR[17]=1,and others Low to make FSMC_A[24:0]=0x010000,So HADDR[25:0]=0x60000000+(0x010000<<1),
That is 0x60020000
*/
#define TFTLCD_Register_Data_Pointer 0x60020000
#define TFTLCD_Register_Data *(volatile u16*)(TFTLCD_Register_Data_Pointer) //*(volatile u16*) is used to avoid Compiler Optimizing Data Flow
	
#define TFTLCD_Model_DefaultID 0x9488
#define TFTLCD_Model_DefaultWidth 319
#define TFTLCD_Model_DefaultHeight 479

#define DisplayMode_V_Default 0x00
#define DisplayMode_V_Reverse 0x01
#define DisplayMode_H_Default 0x02
#define DisplayMode_H_Reverse 0x03

#define RGB888_Convert_RGB565(RGB888) (u16)(((RGB888&0xf80000)>>8)|((RGB888&0x00fc00)>>5)|((RGB888&0x0000f8)>>3))

#define TFTLCD_ReadWriteRGBCmd TFTLCD_Register_Address(0x2c)

#define WindowNum_Max 10

#define ASCII1208 0x01
#define ASCII1608 0x02
#define ASCII2016 0x03
#define ASCII2416 0x04
#define ASCII3216 0x05

#endif

//Parameter of TFTLCD Model
typedef struct
{
	u32 TFTLCD_ID;
	u16 TFTLCD_Width;
	u16 TFTLCD_Height;
} TFTLCD_ModelTypeDef;

//Parameter of Font
typedef struct
{
	const u8* Font_Pointer;               //Pointer of Font List Array
	u8 Font_Width;
	u8 Font_Height;
} TFTLCD_FontTypeDef;

//The Structure is for TFTLCD Displaying Font
typedef struct
{
	TFTLCD_FontTypeDef* TFTLCD_Font;      //Pointer of TFTLCD Font Structure
	u32 Font_Color;
} TFTLCD_FontConfigTypeDef;

//Parameter of Window
typedef struct
{
	u16 X_Start[WindowNum_Max];
	u16 Y_Start[WindowNum_Max];
	u16 X_End[WindowNum_Max];
	u16 Y_End[WindowNum_Max];
	u16 X_Base[WindowNum_Max];
	u16 Y_Base[WindowNum_Max];
	u32 WindowColor[WindowNum_Max];
} TFTLCD_WindowTypeDef;

//ASCII Font
extern TFTLCD_FontTypeDef ASCII_1208;
extern TFTLCD_FontTypeDef ASCII_1608;
extern TFTLCD_FontTypeDef ASCII_2016;
extern TFTLCD_FontTypeDef ASCII_2416;
extern TFTLCD_FontTypeDef ASCII_3216;

//Function Declaration
void TFTLCD_GPIOConfigInit(void);
void TFTLCD_Reset(void);
void TFTLCD_Register_Address(u8 Address);
void TFTLCD_Register_WriteIn(u16 Data);
u32 TFTLCD_Register_ReadOut(void);
void TFTLCD_WriteRGB565(u16 RGB565);
void TFTLCD_WriteRGB888(u32 RGB888);
void TFTLCD_Init(void);
void TFTLCD_DisplayModeConfig(u8 DisplayMode);
void TFTLCD_SetCoords(u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End);
void TFTLCD_FillArea(u32 RGB888,u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End);
void TFTLCD_WindowInit(void);
void TFTLCD_SetWindow(u8 WindowNum,u32 RGB888,u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End);
void TFTLCD_ClearScreen(u32 RGB888);
void TFTLCD_DrawPoint(u32 RGB888,u8 Point_Size,u16 X,u16 Y);
void TFTLCD_FontDisplayConfig(u8 Font,u32 FontColor);
void TFTLCD_DisplayWord(u8 WindowNum,u8 Word);
void TFTLCD_DisplayString(u8 WindowNum,u8* String);
void TFTLCD_CursorTwink(u8 WindowNum,u8* CursorString,u16 delay_nms);
