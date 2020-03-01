#include "TFTLCD.h"

/*
  USER Manual:
  NO.1 TFTLCD_Init();->This Function includes TFTLCD_GPIOConfigInit(),FSMC_GPIOConfigInit(),FSMC_ConfigInit();
	NO.2 TFTLCD_DisplayModeConfig(DisplayMode_V_Default/DisplayMode_V_Reverse/DisplayMode_H_Default/DisplayMode_H_Reverse);
	NO.3 TFTLCD_ClearScreen(ScreenColor);
	NO.4 TFTLCD_FontDisplayConfig(FontType,FontColor);->Choose Font and Font Color
	NO.5 TFTLCD_SetCoords(X_Start,Y_Start,X_End,Y_End);->Set Coords of Next Display Text 
or use TFTLCD_SetWindow(WindowNum,Color,X_Start,Y_Start,X_End,Y_End);->Display On Window
	NO.6 You can use TFTLCD_DisplayWord(WindowNum,Word) to Display a Word,or use TFTLCD_DisplayString(WindowNum,String) to Display String,
or use TFTLCD_DrawPoint(Color,PointSize,X,Y) to Draw a Point,or use TFTLCD_CursorTwink(CursorString,TwinkTime) to Display Twinkle Cursor
...
*/

/*Global Variable Defination*/
//Font Parameter
TFTLCD_FontTypeDef ASCII_1208=
{
	Font_ASCII_1208,
	8,
	12,
};
TFTLCD_FontTypeDef ASCII_1608=
{
	Font_ASCII_1608,
	8,
	16,
};
TFTLCD_FontTypeDef ASCII_2016=
{
	Font_ASCII_2016,
	16,
	20,
};
TFTLCD_FontTypeDef ASCII_2416=
{
	Font_ASCII_2416,
	16,
	24,
};
TFTLCD_FontTypeDef ASCII_3216=
{
	Font_ASCII_3216,
	16,
	32,
};

//Default ASCII Font Config
TFTLCD_FontConfigTypeDef TFTLCD_FontConfig=
{
	&ASCII_1608,
	0x00ffffff,
};

//Default TFTLCD_Model_Parameter
TFTLCD_ModelTypeDef TFTLCD_Model=
{
	TFTLCD_Model_DefaultID,       //ID
	TFTLCD_Model_DefaultWidth,    //Width
	TFTLCD_Model_DefaultHeight,   //Height
};

TFTLCD_WindowTypeDef WindowX;
/*Global Variable Defination*/










/*Basic Function Defination*/
//Addressing Register In TFTLCD
void TFTLCD_Register_Address(u8 Address)
{
	TFTLCD_Register_Addr=Address;  
}

//Write Primary Data to TFTLCD_Register
void TFTLCD_Register_WriteIn(u16 Data)
{
	TFTLCD_Register_Data=Data;
}

//Read Data from TFTLCD_Register
u32 TFTLCD_Register_ReadOut(void)
{
	return TFTLCD_Register_Data;
}

void TFTLCD_WriteRGB565(u16 RGB565)
{
	TFTLCD_Register_Data=RGB565;
}

//Transform RGB888 to RGB565
void TFTLCD_WriteRGB888(u32 RGB888)
{
	TFTLCD_Register_Data=RGB888_Convert_RGB565(RGB888);
}

//Init TFTLCD
void TFTLCD_Init(void)
{
	FSMC_GPIOConfigInit();
	TFTLCD_GPIOConfigInit();
	FSMC_ConfigInit();
	
	TFTLCD_Reset();

	TFTLCD_Register_Address(0xe0);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(0x03);
	TFTLCD_Register_WriteIn(0x0c);
	TFTLCD_Register_WriteIn(0x09);
	TFTLCD_Register_WriteIn(0x17);
	TFTLCD_Register_WriteIn(0x09);
	TFTLCD_Register_WriteIn(0x3e);
	TFTLCD_Register_WriteIn(0x89);
	TFTLCD_Register_WriteIn(0x49);
	TFTLCD_Register_WriteIn(0x08);
	TFTLCD_Register_WriteIn(0x0d);
	TFTLCD_Register_WriteIn(0x0a);
	TFTLCD_Register_WriteIn(0x13);
	TFTLCD_Register_WriteIn(0x15);
	TFTLCD_Register_WriteIn(0x0f);
	
	TFTLCD_Register_Address(0xe1);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(0x11);
	TFTLCD_Register_WriteIn(0x15);
	TFTLCD_Register_WriteIn(0x03);
	TFTLCD_Register_WriteIn(0x0f);
	TFTLCD_Register_WriteIn(0x05);
	TFTLCD_Register_WriteIn(0x2d);
	TFTLCD_Register_WriteIn(0x34);
	TFTLCD_Register_WriteIn(0x41);
	TFTLCD_Register_WriteIn(0x02);
	TFTLCD_Register_WriteIn(0x0b);
	TFTLCD_Register_WriteIn(0x0a);
	TFTLCD_Register_WriteIn(0x33);
	TFTLCD_Register_WriteIn(0x37);
	TFTLCD_Register_WriteIn(0x0f);
	
	TFTLCD_Register_Address(0xc0);
	TFTLCD_Register_WriteIn(0x17);
	TFTLCD_Register_WriteIn(0x15);
	
	TFTLCD_Register_Address(0xc1);
	TFTLCD_Register_WriteIn(0x41);
	
	TFTLCD_Register_Address(0xc5);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(0x12);
	TFTLCD_Register_WriteIn(0x80);
	
	TFTLCD_Register_Address(0x36);
	TFTLCD_Register_WriteIn(0x48);
	
	TFTLCD_Register_Address(0x3a);
	TFTLCD_Register_WriteIn(0x55);
	
	TFTLCD_Register_Address(0xb0);
	TFTLCD_Register_WriteIn(0x00);
	
	TFTLCD_Register_Address(0xb1);
	TFTLCD_Register_WriteIn(0xa0);
	
	TFTLCD_Register_Address(0xb4);
	TFTLCD_Register_WriteIn(0x02);
	
	TFTLCD_Register_Address(0xb6);
	TFTLCD_Register_WriteIn(0x02);
	TFTLCD_Register_WriteIn(0x02);
	
	TFTLCD_Register_Address(0xe9);
	TFTLCD_Register_WriteIn(0x00);
	
	TFTLCD_Register_Address(0xf7);
	TFTLCD_Register_WriteIn(0xa9);
	TFTLCD_Register_WriteIn(0x51);
	TFTLCD_Register_WriteIn(0x2c);
	TFTLCD_Register_WriteIn(0x82);
	
	TFTLCD_Register_Address(0x11);    //Sleep Out
	delay_ms(120);
	TFTLCD_Register_Address(0x29);    //Display On
	
	TFTLCD_BackLight_ON;
	TFTLCD_WindowInit();
}

//Choose Display Mode
void TFTLCD_DisplayModeConfig(u8 DisplayMode)
{
	//Vertical Mode
/* ________
	|        |
	|        |
	| TFTLCD |
	|   __   |
	|___  ___|
*/
	if(DisplayMode==DisplayMode_V_Default)
	{
		TFTLCD_Register_Address(0x36);       //Addressing Scan Mode Register of TFTLCD
		TFTLCD_Register_WriteIn(0x48);       //Scan Direction,Left to Right,Up to Down
		TFTLCD_Model.TFTLCD_Width=TFTLCD_Model_DefaultWidth;
		TFTLCD_Model.TFTLCD_Height=TFTLCD_Model_DefaultHeight;
	}
/* ___  ___ 
	|   __   |
	|        |
	| TFTLCD |
	|        |
	|________|
*/
	else if(DisplayMode==DisplayMode_V_Reverse)
	{
		TFTLCD_Register_Address(0x36);       //Addressing Scan Mode Register of TFTLCD
		TFTLCD_Register_WriteIn(0x88);       //Scan Direction,Left to Right,Up to Down
		TFTLCD_Model.TFTLCD_Width=TFTLCD_Model_DefaultWidth;
		TFTLCD_Model.TFTLCD_Height=TFTLCD_Model_DefaultHeight;
	}
	
	//Horizontal Mode
/* __________
	|          |
	|  TFTLCD |
	|__________|
*/
	else if(DisplayMode==DisplayMode_H_Default) 
	{
		TFTLCD_Register_Address(0x36);       //Addressing Scan Mode Register of TFTLCD
		TFTLCD_Register_WriteIn(0x28);       //Scan Direction,Left to Right,Up to Down
		TFTLCD_Model.TFTLCD_Width=TFTLCD_Model_DefaultHeight;
		TFTLCD_Model.TFTLCD_Height=TFTLCD_Model_DefaultWidth;
	}
/* __________
	|          |
	 | TFTLCD  |
	|__________|
*/
	else if(DisplayMode==DisplayMode_H_Reverse) 
	{
		TFTLCD_Register_Address(0x36);       //Addressing Scan Mode Register of TFTLCD
		TFTLCD_Register_WriteIn(0xe8);       //Scan Direction,Right to Left,Down to Up
		TFTLCD_Model.TFTLCD_Width=TFTLCD_Model_DefaultHeight;
		TFTLCD_Model.TFTLCD_Height=TFTLCD_Model_DefaultWidth;
	}
	
	//Set Mode Cover Area
	TFTLCD_Register_Address(0x2a);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(TFTLCD_Model_DefaultWidth>>8);         //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(TFTLCD_Model_DefaultWidth&0xff);       //WriteIn Low 8Bit
	
	TFTLCD_Register_Address(0x2b);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(0x00);
	TFTLCD_Register_WriteIn(TFTLCD_Model_DefaultHeight>>8);        //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(TFTLCD_Model_DefaultHeight&0xff);      //WriteIn Low 8Bit

	TFTLCD_WindowInit();
}

//Set Coords
void TFTLCD_SetCoords(u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End)
{
	//Set X_Start and X_End
	TFTLCD_Register_Address(0x2a);
	TFTLCD_Register_WriteIn(X_Start>>8);                             //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(X_Start&0xff);                           //WriteIn Low 8Bit
	TFTLCD_Register_WriteIn(X_End>>8);     //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(X_End&0xff);   //WriteIn Low 8Bit
	
	//Set Y_Start and Y_End
	TFTLCD_Register_Address(0x2b);
	TFTLCD_Register_WriteIn(Y_Start>>8);                             //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(Y_Start&0xff);                           //WriteIn Low 8Bit
	TFTLCD_Register_WriteIn(Y_End>>8);    //WriteIn High 8Bit
	TFTLCD_Register_WriteIn(Y_End&0xff);  //WriteIn Low 8Bit
}
/*Basic Function Defination*/










/*Exband Function Defination*/
//TFTLCD Fill an Area
void TFTLCD_FillArea(u32 RGB888,u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End)
{
	int i;
	TFTLCD_SetCoords(X_Start,Y_Start,X_End,Y_End);
	TFTLCD_ReadWriteRGBCmd;
	for(i=0;i<(X_End-X_Start+1)*(Y_End-Y_Start+1);i++)
	{
		TFTLCD_WriteRGB888(RGB888);
	}
}

//Init WindowX Parameter
void TFTLCD_WindowInit(void)
{
	u8 i;
	for(i=0;i<WindowNum_Max;i++)
	{
		WindowX.WindowColor[1]=0x00;
		WindowX.X_Start[i]=0;
		WindowX.Y_Start[i]=0;
		WindowX.X_End[i]=TFTLCD_Model.TFTLCD_Width;
		WindowX.Y_End[i]=TFTLCD_Model.TFTLCD_Height;
		WindowX.X_Base[i]=0;
		WindowX.Y_Base[i]=0;
	}
}

//Open a Window with X,Y Start and X,Y End,Fill color
void TFTLCD_SetWindow(u8 WindowNum,u32 RGB888,u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End)
{
	u32 i;
	WindowX.WindowColor[WindowNum]=RGB888;
	TFTLCD_SetCoords(X_Start,Y_Start,X_End,Y_End);
	TFTLCD_ReadWriteRGBCmd;
	for(i=0;i<(X_End-X_Start+1)*(Y_End-Y_Start+1);i++)
	TFTLCD_WriteRGB888(RGB888);
	
	//Refresh Base Coords
	WindowX.X_Base[WindowNum]=X_Start;
	WindowX.Y_Base[WindowNum]=Y_Start;
	
	//Refresh Window Coords
	WindowX.X_Start[WindowNum]=X_Start;
	WindowX.Y_Start[WindowNum]=Y_Start;
	WindowX.X_End[WindowNum]=X_End;
	WindowX.Y_End[WindowNum]=Y_End;
}

//Clear Screen with Chose Color
void TFTLCD_ClearScreen(u32 RGB888)
{
	TFTLCD_FillArea(RGB888,0,0,TFTLCD_Model.TFTLCD_Width,TFTLCD_Model.TFTLCD_Height);
	TFTLCD_WindowInit();
}

//Draw a Point
void TFTLCD_DrawPoint(u32 RGB888,u8 Point_Size,u16 X,u16 Y)
{
	u32 i;
	u16 X_Start=X;
	u16 Y_Start=Y;
	u16 X_End=X+Point_Size-1;
	u16 Y_End=Y+Point_Size-1;
	TFTLCD_SetCoords(X_Start,Y_Start,X_End,Y_End);
	TFTLCD_ReadWriteRGBCmd;
	for(i=0;i<(X_End-X_Start+1)*(Y_End-Y_Start+1);i++)
	TFTLCD_WriteRGB888(RGB888);
}

//Config Font and Font color
void TFTLCD_FontDisplayConfig(u8 Font,u32 FontColor)
{
	TFTLCD_FontConfig.Font_Color=FontColor;
	if(Font==ASCII1208) TFTLCD_FontConfig.TFTLCD_Font=&ASCII_1208;
	else if(Font==ASCII1608) TFTLCD_FontConfig.TFTLCD_Font=&ASCII_1608;
	else if(Font==ASCII2016) TFTLCD_FontConfig.TFTLCD_Font=&ASCII_2016;
	else if(Font==ASCII2416) TFTLCD_FontConfig.TFTLCD_Font=&ASCII_2416;
	else if(Font==ASCII3216) TFTLCD_FontConfig.TFTLCD_Font=&ASCII_3216;
}

//TFTLCD Display a Word
void TFTLCD_DisplayWord(u8 WindowNum,u8 Word)
{
	u8 Width=TFTLCD_FontConfig.TFTLCD_Font->Font_Width;
	u8 Height=TFTLCD_FontConfig.TFTLCD_Font->Font_Height;
	u32 Pointer=(Word-' ')*Width*Height/8;
	u16 X,Y;
	u8 x,y;
	u8 P=0x01;
	
/*Area Control*/
	//Return to Window Left
	if(Word=='\r')
	{
		WindowX.X_Base[WindowNum]=WindowX.X_Start[WindowNum];
		return;
	}
	//New line
	else if(Word=='\n')
	{
		WindowX.Y_Base[WindowNum]+=Height;
		return;
	}
	if(WindowX.X_Base[WindowNum]+Width>WindowX.X_End[WindowNum])
	{
		WindowX.X_Base[WindowNum]=WindowX.X_Start[WindowNum];
		WindowX.Y_Base[WindowNum]+=Height;
		return;
	}
	if(WindowX.Y_Base[WindowNum]+Height>WindowX.Y_End[WindowNum]) 
	{
		TFTLCD_SetWindow(WindowNum,WindowX.WindowColor[WindowNum],WindowX.X_Start[WindowNum],WindowX.Y_Start[WindowNum],WindowX.X_End[WindowNum],WindowX.Y_End[WindowNum]);
	}
/*Area Control*/
	
	X=WindowX.X_Base[WindowNum];
	Y=WindowX.Y_Base[WindowNum];
	
/*Draw Point*/
	for(y=0;y<Height;y++)
	{
		for(x=0;x<Width;x++)
		{
			if(TFTLCD_FontConfig.TFTLCD_Font->Font_Pointer[Pointer]&P)
			{
				TFTLCD_DrawPoint(TFTLCD_FontConfig.Font_Color,1,X,Y);
			}
			P<<=1;
			if(!P)
			{
				P=0x01;
				Pointer++;
			}
			X++;
		}
		Y++;
		X-=Width;
	}
	Y-=Height;
/*Draw Point*/
	
//Refresh Base Coords
	WindowX.X_Base[WindowNum]=X+Width;
	WindowX.Y_Base[WindowNum]=Y;
}

//Display String
void TFTLCD_DisplayString(u8 WindowNum,u8* String)
{
	while(*String)
	{
		TFTLCD_DisplayWord(WindowNum,*String);
		String++;
	}
}

//Display Twinkle Cursor
void TFTLCD_CursorTwink(u8 WindowNum,u8* CursorString,u16 delay_nms)
{
	u8 P=0;
	u16 X_Start;
	u16 Y_Start;
	u16 X_End;
	u16 Y_End;
	
	//Get Number of Cursor Char
	while(*CursorString)
	{
		CursorString++;
		P++;
	}
	
	//Pointer Reduction
	CursorString-=P;
	
	//Cursor String can only Display on one Line,if the Length of Cursor String Byond One Line, go to Next Line
	if((WindowX.X_Base[WindowNum]+P*TFTLCD_FontConfig.TFTLCD_Font->Font_Width)>WindowX.X_End[WindowNum]) 
	{
		TFTLCD_DisplayString(WindowNum,"\r\n");
	}
	
	//Display Cursor String
	while(*CursorString)
	{
		TFTLCD_DisplayWord(WindowNum,*CursorString);
		CursorString++;
		delay_ms(delay_nms);
	}
	
	X_Start=WindowX.X_Base[WindowNum]-P*TFTLCD_FontConfig.TFTLCD_Font->Font_Width;
	Y_Start=WindowX.Y_Base[WindowNum];
	X_End=WindowX.X_Base[WindowNum];
	Y_End=WindowX.Y_Base[WindowNum]+TFTLCD_FontConfig.TFTLCD_Font->Font_Height-1;
	
	//Clear Cursor String
	TFTLCD_FillArea(WindowX.WindowColor[WindowNum],X_Start,Y_Start,X_End,Y_End);
	
	WindowX.X_Base[WindowNum]=X_Start;
	WindowX.Y_Base[WindowNum]=Y_Start;
	
	delay_ms(delay_nms);
}
/*Exband Function Defination*/
