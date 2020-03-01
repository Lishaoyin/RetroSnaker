#include "stm32f4xx.h"
#include "TFTLCD.h"
#include "delay.h"
#include "RNG.h"

#ifndef _SNAKE_H
#define _SNAKE_H

#define X 0
#define Y 1

//Screen Size
#define ScreenWidth 320
#define ScreenHeight 480

//File and Frame
#define FileWidth 310
#define FileHeight 470
#define FileColor 0x00
#define FrameColor 0xff0000

//Length and Thickness
#define SnakeLength_Max 100
#define SnakeThickness 9
#define Snake_MoveStep 1

//Snake Body and Head
#define SnakeColor_Body 0x004050
#define SnakeColor_Head 0xfff000

//Snake Moving Direction
#define DIR_R 0x00
#define DIR_D 0x01
#define DIR_L 0x02
#define DIR_U 0x03  

//Basic Display
#define Snake_DisplayReset TFTLCD_ClearScreen(FileColor)
#define Snake_FillSection(X_Start,Y_Start,X_End,Y_End) TFTLCD_FillArea(SnakeColor_Body,X_Start,Y_Start,X_End,Y_End)
#define Snake_FillArea(RGB888,X_Start,Y_Start,X_End,Y_End) TFTLCD_FillArea(RGB888,X_Start,Y_Start,X_End,Y_End)
#define Snake_SetWindow(RGB888,X_Start,Y_Start,X_End,Y_End) TFTLCD_SetWindow(0,RGB888,X_Start,Y_Start,X_End,Y_End)
#define Snake_DisplayString(String) TFTLCD_DisplayString(0,String)
#define Snake_SetCoords(X_Start,Y_Start,X_End,Y_End) TFTLCD_SetCoords(X_Start,Y_Start,X_End,Y_End)
#define Snake_WriteRGB888(RGB888) TFTLCD_WriteRGB888(RGB888)
#define Snake_WriteRGBCmd TFTLCD_ReadWriteRGBCmd

#define Cmd_Start_Stop 0x00
#define Cmd_Restart 0x01

#define Head (SNAKE.LocatPoint_Num-1)
#define Tail 0

#define Frog_RandomInit RNG_Init()
#define FrogColor 0x00ff00
#define FrogNum_Max 30

#define LocatFrog_X RNG_GetRandomNum((ScreenWidth-FileWidth)/2+SnakeThickness/2+1,(ScreenWidth+FileWidth)/2-SnakeThickness/2-1)
#define LocatFrog_Y RNG_GetRandomNum((ScreenHeight-FileHeight)/2+SnakeThickness/2+1,(ScreenHeight+FileHeight)/2-SnakeThickness/2-1)

#endif

typedef struct
{
	u8 FrogNum;
	u8 LocatPoint_Num;
	u16 LocatPoint[2][SnakeLength_Max];
	u16 LocatFrog[2][FrogNum_Max];
	u8 DIR_Head;
	u8 DIR_Tail;
	u8 StartCmd;
	u8 DeathFlag;
} Snake_TypeDef;

extern const u32 FrogShape[81];

void Snake_DisplayFrame(void);
void RetroSnaker_Init(void);
void Snake_Cmd(u8 Cmd);
void Snake_DisplaySection(u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End);
void Snake_Turn(u8 Dir);
void Snake_HeadMove(void);
void Snake_TailMove(void);
void Snake_Move(void);
void Snake_EatFrog(void);
void Snake_HuntFrog(void);
void Snake_FrogInit(void);
void Snake_CheckStatus(void);



