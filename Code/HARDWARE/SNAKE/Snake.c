#include "Snake.h"

//Parameter Structure of Snake moving
Snake_TypeDef SNAKE;

//Speed Parameter
u8 Snake_MoveSpeed=10;

//Display Frame
void Snake_DisplayFrame(void)
{
	u8 FrameThickness=(ScreenWidth-FileWidth)/2;
	Snake_FillArea(FrameColor,0,0,ScreenWidth-1,FrameThickness-1);
	Snake_FillArea(FrameColor,ScreenWidth-FrameThickness,0,ScreenWidth-1,ScreenHeight-1);
	Snake_FillArea(FrameColor,0,ScreenHeight-FrameThickness,ScreenWidth-1,ScreenHeight-1);
	Snake_FillArea(FrameColor,0,0,FrameThickness-1,ScreenHeight-1);
}

//Parameter Init
void RetroSnaker_Init(void)
{
	u8 i;
	SNAKE.FrogNum=0;
	SNAKE.LocatPoint_Num=2;
	//Snake Tail Loacting
	SNAKE.LocatPoint[X][Tail]=(ScreenWidth-FileWidth)/2+SnakeThickness;
	SNAKE.LocatPoint[Y][Tail]=(ScreenHeight-FileHeight)/2+SnakeThickness;
	//Snake Head Locating
	SNAKE.LocatPoint[X][Head]=SNAKE.LocatPoint[X][Tail]+SnakeThickness;
	SNAKE.LocatPoint[Y][Head]=SNAKE.LocatPoint[Y][Tail];
	SNAKE.DIR_Head=DIR_R;
	SNAKE.DIR_Tail=DIR_R;
	SNAKE.StartCmd=0;
	SNAKE.DeathFlag=0;
	Snake_DisplayReset;
	Snake_FrogInit();
	Snake_DisplayFrame();
	
	//Snake Display Body
	for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
	{
		Snake_DisplaySection(SNAKE.LocatPoint[X][i],SNAKE.LocatPoint[Y][i],SNAKE.LocatPoint[X][i+1],SNAKE.LocatPoint[Y][i+1]);
	}
	
	//Fill Snake Head Color
	Snake_FillArea(SnakeColor_Head,SNAKE.LocatPoint[X][Head]-SnakeThickness/2,SNAKE.LocatPoint[Y][Head]-SnakeThickness/2,SNAKE.LocatPoint[X][Head]+SnakeThickness/2,SNAKE.LocatPoint[Y][Head]+SnakeThickness/2);
	
}

//System Command
void Snake_Cmd(u8 Cmd)
{
	if(Cmd==Cmd_Start_Stop) SNAKE.StartCmd=!SNAKE.StartCmd;
	else if(Cmd==Cmd_Restart) 
	{
		Snake_MoveSpeed=10;
		RetroSnaker_Init();
	}
}

//Display a Section of Body
void Snake_DisplaySection(u16 X_Start,u16 Y_Start,u16 X_End,u16 Y_End)
{
	u16 x_start,y_start,x_end,y_end;
	
	if(X_Start==X_End)
	{
		x_start=X_Start-SnakeThickness/2;
		x_end=X_Start+SnakeThickness/2;
		if(Y_Start<Y_End)
		{
			y_start=Y_Start-SnakeThickness/2;
			y_end=Y_End+SnakeThickness/2;
		}
		else if(Y_Start>Y_End)
		{
			y_start=Y_End-SnakeThickness/2;
			y_end=Y_Start+SnakeThickness/2;
		}
	}
	else if(Y_Start==Y_End)
	{
		y_start=Y_Start-SnakeThickness/2;
		y_end=Y_Start+SnakeThickness/2;
		if(X_Start<X_End)
		{
			x_start=X_Start-SnakeThickness/2;
			x_end=X_End+SnakeThickness/2;
		}
		else if(X_Start>X_End)
		{
			x_start=X_End-SnakeThickness/2;
			x_end=X_Start+SnakeThickness/2;
		}
	}
	Snake_FillSection(x_start,y_start,x_end,y_end);
}

//Direction of Snake Head，Can not Turn Around but Turn 90 Degree every time 
void Snake_Turn(u8 Dir)
{
	if(!SNAKE.StartCmd) return;
	
	else if(Dir==DIR_R)
	{
		if(SNAKE.DIR_Head==DIR_D||SNAKE.DIR_Head==DIR_U)
		{
			SNAKE.DIR_Head=DIR_R;
			SNAKE.LocatPoint_Num++;
			SNAKE.LocatPoint[X][Head]=SNAKE.LocatPoint[X][Head-1];
			SNAKE.LocatPoint[Y][Head]=SNAKE.LocatPoint[Y][Head-1];
		}	
	}
	
	else if(Dir==DIR_D)
	{
		if(SNAKE.DIR_Head==DIR_R||SNAKE.DIR_Head==DIR_L)
		{
			SNAKE.DIR_Head=DIR_D;
			SNAKE.LocatPoint_Num++;
			SNAKE.LocatPoint[X][Head]=SNAKE.LocatPoint[X][Head-1];
			SNAKE.LocatPoint[Y][Head]=SNAKE.LocatPoint[Y][Head-1];
		}
	}
	
	else if(Dir==DIR_L)
	{
		if(SNAKE.DIR_Head==DIR_D||SNAKE.DIR_Head==DIR_U)
		{
			SNAKE.DIR_Head=DIR_L;
			SNAKE.LocatPoint_Num++;
			SNAKE.LocatPoint[X][Head]=SNAKE.LocatPoint[X][Head-1];
			SNAKE.LocatPoint[Y][Head]=SNAKE.LocatPoint[Y][Head-1];
		}	
	}
	
	else if(Dir==DIR_U)
	{
		if(SNAKE.DIR_Head==DIR_R||SNAKE.DIR_Head==DIR_L)
		{
			SNAKE.DIR_Head=DIR_U;
			SNAKE.LocatPoint_Num++;
			SNAKE.LocatPoint[X][Head]=SNAKE.LocatPoint[X][Head-1];
			SNAKE.LocatPoint[Y][Head]=SNAKE.LocatPoint[Y][Head-1];
		}
	}

}

//Snake Head Moving
void Snake_HeadMove(void)
{
	if(!SNAKE.StartCmd) return;
	else if(SNAKE.DIR_Head==DIR_R) SNAKE.LocatPoint[X][Head]+=Snake_MoveStep;
	else if(SNAKE.DIR_Head==DIR_D) SNAKE.LocatPoint[Y][Head]+=Snake_MoveStep;
	else if(SNAKE.DIR_Head==DIR_L) SNAKE.LocatPoint[X][Head]-=Snake_MoveStep;
	else if(SNAKE.DIR_Head==DIR_U) SNAKE.LocatPoint[Y][Head]-=Snake_MoveStep;
	
}

//Snake Tail Moving
void Snake_TailMove(void)
{
	u8 i;
	u16 X_Start,Y_Start,X_End,Y_End;
	
	if(!SNAKE.StartCmd) return;
	
	/*Judge Direction of Tail Moving*/
	if(SNAKE.LocatPoint[X][Tail]==SNAKE.LocatPoint[X][Tail+1])
	{
		if(SNAKE.LocatPoint[Y][Tail]<SNAKE.LocatPoint[Y][Tail+1]) SNAKE.DIR_Tail=DIR_D;
		else if(SNAKE.LocatPoint[Y][Tail]>SNAKE.LocatPoint[Y][Tail+1]) SNAKE.DIR_Tail=DIR_U;
	}
	else if(SNAKE.LocatPoint[Y][Tail]==SNAKE.LocatPoint[Y][Tail+1])
	{
		if(SNAKE.LocatPoint[X][Tail]<SNAKE.LocatPoint[X][Tail+1]) SNAKE.DIR_Tail=DIR_R;
		else if(SNAKE.LocatPoint[X][Tail]>SNAKE.LocatPoint[X][Tail+1]) SNAKE.DIR_Tail=DIR_L;
	}
	/*Judge Direction of Tail Moving*/
	
	if(SNAKE.DIR_Tail==DIR_R)
	{
		X_Start=SNAKE.LocatPoint[X][Tail]-SnakeThickness/2;
		Y_Start=SNAKE.LocatPoint[Y][Tail]-SnakeThickness/2;
		X_End=X_Start+Snake_MoveStep-1;
		Y_End=SNAKE.LocatPoint[Y][Tail]+SnakeThickness/2;
		Snake_FillArea(FileColor,X_Start,Y_Start,X_End,Y_End);
		SNAKE.LocatPoint[X][Tail]+=Snake_MoveStep;
		if(SNAKE.LocatPoint[X][Tail]==SNAKE.LocatPoint[X][Tail+1])
		{
			SNAKE.LocatPoint[X][Tail+1]=SNAKE.LocatPoint[X][Tail];
			SNAKE.LocatPoint[Y][Tail+1]=SNAKE.LocatPoint[Y][Tail];
			for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
			{
				SNAKE.LocatPoint[X][i]=SNAKE.LocatPoint[X][i+1];
				SNAKE.LocatPoint[Y][i]=SNAKE.LocatPoint[Y][i+1];
			}
			SNAKE.LocatPoint_Num--;
		}
	}
	
	else if(SNAKE.DIR_Tail==DIR_D)
	{
		X_Start=SNAKE.LocatPoint[X][Tail]-SnakeThickness/2;
		Y_Start=SNAKE.LocatPoint[Y][Tail]-SnakeThickness/2;
		X_End=SNAKE.LocatPoint[X][Tail]+SnakeThickness/2;
		Y_End=Y_Start+Snake_MoveStep-1;
		Snake_FillArea(FileColor,X_Start,Y_Start,X_End,Y_End);
		SNAKE.LocatPoint[Y][Tail]+=Snake_MoveStep;
		if(SNAKE.LocatPoint[Y][Tail]==SNAKE.LocatPoint[Y][Tail+1])
		{
			SNAKE.LocatPoint[X][Tail+1]=SNAKE.LocatPoint[X][Tail];
			SNAKE.LocatPoint[Y][Tail+1]=SNAKE.LocatPoint[Y][Tail];
			for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
			{
				SNAKE.LocatPoint[X][i]=SNAKE.LocatPoint[X][i+1];
				SNAKE.LocatPoint[Y][i]=SNAKE.LocatPoint[Y][i+1];
			}
			SNAKE.LocatPoint_Num--;
		}
	}
	
	else if(SNAKE.DIR_Tail==DIR_L)
	{
		X_Start=SNAKE.LocatPoint[X][Tail]+SnakeThickness/2-Snake_MoveStep+1;
		Y_Start=SNAKE.LocatPoint[Y][Tail]-SnakeThickness/2;
		X_End=SNAKE.LocatPoint[X][Tail]+SnakeThickness/2;
		Y_End=SNAKE.LocatPoint[Y][Tail]+SnakeThickness/2;
		Snake_FillArea(FileColor,X_Start,Y_Start,X_End,Y_End);
		SNAKE.LocatPoint[X][Tail]-=Snake_MoveStep;
		if(SNAKE.LocatPoint[X][Tail]==SNAKE.LocatPoint[X][Tail+1])
		{
			SNAKE.LocatPoint[X][Tail+1]=SNAKE.LocatPoint[X][Tail];
			SNAKE.LocatPoint[Y][Tail+1]=SNAKE.LocatPoint[Y][Tail];
			for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
			{
				SNAKE.LocatPoint[X][i]=SNAKE.LocatPoint[X][i+1];
				SNAKE.LocatPoint[Y][i]=SNAKE.LocatPoint[Y][i+1];
			}
			SNAKE.LocatPoint_Num--;
		}
	}
	
	else if(SNAKE.DIR_Tail==DIR_U)
	{
		X_Start=SNAKE.LocatPoint[X][Tail]-SnakeThickness/2;
		Y_Start=SNAKE.LocatPoint[Y][Tail]+SnakeThickness/2-Snake_MoveStep+1;
		X_End=SNAKE.LocatPoint[X][Tail]+SnakeThickness/2;
		Y_End=SNAKE.LocatPoint[Y][Tail]+SnakeThickness/2;
		Snake_FillArea(FileColor,X_Start,Y_Start,X_End,Y_End);
		SNAKE.LocatPoint[Y][Tail]-=Snake_MoveStep;
		if(SNAKE.LocatPoint[Y][Tail]==SNAKE.LocatPoint[Y][Tail+1])
		{
			SNAKE.LocatPoint[X][Tail+1]=SNAKE.LocatPoint[X][Tail];
			SNAKE.LocatPoint[Y][Tail+1]=SNAKE.LocatPoint[Y][Tail];
			for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
			{
				SNAKE.LocatPoint[X][i]=SNAKE.LocatPoint[X][i+1];
				SNAKE.LocatPoint[Y][i]=SNAKE.LocatPoint[Y][i+1];
			}
			SNAKE.LocatPoint_Num--;
		}
	}
}

void Snake_FrogInit(void)
{
	u8 i,j;
	Frog_RandomInit;
	for(i=0;i<FrogNum_Max;i++)
	{
		SNAKE.LocatFrog[X][i]=LocatFrog_X;
		SNAKE.LocatFrog[Y][i]=LocatFrog_Y;
		Snake_SetCoords(SNAKE.LocatFrog[X][i]-SnakeThickness/2,SNAKE.LocatFrog[Y][i]-SnakeThickness/2,SNAKE.LocatFrog[X][i]+SnakeThickness/2,SNAKE.LocatFrog[Y][i]+SnakeThickness/2);
		Snake_WriteRGBCmd;
		for(j=0;j<SnakeThickness*SnakeThickness;j++)
		{
			Snake_WriteRGB888(FrogShape[j]);
		}
	}
}

//Every Time Call This Function,Snake will Eat a Frog
void Snake_EatFrog(void)
{
	if(SNAKE.DIR_Tail==DIR_R) SNAKE.LocatPoint[X][Tail]-=SnakeThickness;
	else if(SNAKE.DIR_Tail==DIR_D) SNAKE.LocatPoint[Y][Tail]-=SnakeThickness;
	else if(SNAKE.DIR_Tail==DIR_L) SNAKE.LocatPoint[X][Tail]+=SnakeThickness;
	else if(SNAKE.DIR_Tail==DIR_U) SNAKE.LocatPoint[Y][Tail]+=SnakeThickness;
}

//Check if a Frog has been Eaten
void Snake_HuntFrog(void)
{
	u8 i;
	u8 Flag1,Flag2,Flag3;
	for(i=0;i<FrogNum_Max;i++)
	{
		if((SNAKE.LocatPoint[X][Head]>(SNAKE.LocatFrog[X][i]-SnakeThickness))&&(SNAKE.LocatPoint[X][Head]<(SNAKE.LocatFrog[X][i]+SnakeThickness)))
			Flag1=1;
		else Flag1=0;
		
		if((SNAKE.LocatPoint[Y][Head]>(SNAKE.LocatFrog[Y][i]-SnakeThickness))&&(SNAKE.LocatPoint[Y][Head]<(SNAKE.LocatFrog[Y][i]+SnakeThickness)))
			Flag2=1;
		else Flag2=0;
		
		if((SNAKE.LocatFrog[X][i]!=0)&&(SNAKE.LocatFrog[Y][i]!=0))
			Flag3=1;
		else Flag3=0;
		
		if(Flag1&&Flag2&&Flag3)
		{
			Snake_EatFrog();
			Snake_FillArea(FileColor,SNAKE.LocatFrog[X][i]-SnakeThickness/2,SNAKE.LocatFrog[Y][i]-SnakeThickness/2,SNAKE.LocatFrog[X][i]+SnakeThickness/2,SNAKE.LocatFrog[Y][i]+SnakeThickness/2);
			SNAKE.LocatFrog[X][i]=0;
			SNAKE.LocatFrog[Y][i]=0;
			SNAKE.FrogNum++;
			return;
		}
	}
	
}

//When Snake Died,This Function will be Called
void Snake_Death(void)
{
	Snake_SetWindow(0xff0000,0,0,ScreenWidth-1,ScreenHeight-1);
	delay_ms(100);
	Snake_SetWindow(0x000000,0,0,ScreenWidth-1,ScreenHeight-1);
	delay_ms(100);
	Snake_SetWindow(0xff0000,0,0,ScreenWidth-1,ScreenHeight-1);
	delay_ms(100);
	Snake_SetWindow(0x000000,0,0,ScreenWidth-1,ScreenHeight-1);
	delay_ms(100);
	Snake_SetWindow(0xff0000,0,0,ScreenWidth-1,ScreenHeight-1);
	delay_ms(100);
	Snake_SetWindow(0x000000,0,0,ScreenWidth-1,ScreenHeight-1);
	Snake_SetWindow(0x000000,47,223,ScreenWidth-1,ScreenHeight-1);
	Snake_DisplayString("You Just Lost!");
	delay_ms(1000);
	delay_ms(1000);
	RetroSnaker_Init();
}

//Check if Snake Hit on Frame or Eat a Frog
void Snake_CheckStatus(void)
{
	//Check Hit on Frame
	if(SNAKE.DIR_Head==DIR_R)
	{
		if(SNAKE.LocatPoint[X][Head]+SnakeThickness/2>=(ScreenWidth+FileWidth)/2) SNAKE.DeathFlag=1;
	}
	else if(SNAKE.DIR_Head==DIR_D)
	{
		if(SNAKE.LocatPoint[Y][Head]+SnakeThickness/2>=(ScreenHeight+FileHeight)/2) SNAKE.DeathFlag=1;
	}
	else if(SNAKE.DIR_Head==DIR_L)
	{
		if(SNAKE.LocatPoint[X][Head]-SnakeThickness/2<=(ScreenWidth-FileWidth)/2) SNAKE.DeathFlag=1;
	}
	else if(SNAKE.DIR_Head==DIR_U)
	{
		if(SNAKE.LocatPoint[Y][Head]-SnakeThickness/2<=(ScreenHeight-FileHeight)/2) SNAKE.DeathFlag=1;
	}
	
	if(SNAKE.DeathFlag) Snake_Death();
	if(SNAKE.FrogNum==FrogNum_Max)
	{
		RetroSnaker_Init();
		Snake_MoveSpeed-=2;
		if(Snake_MoveSpeed<2) 
			Snake_MoveSpeed=1;
	}		
}

//Snake Moving
void Snake_Move(void)
{
	u8 i;
	
	if(!SNAKE.StartCmd) return;
	
	Snake_HuntFrog();
	Snake_CheckStatus();
	
	Snake_HeadMove();
	Snake_TailMove();
	
	//Snake Display Body
	for(i=0;(i+1)<SNAKE.LocatPoint_Num;i++)
	{
		Snake_DisplaySection(SNAKE.LocatPoint[X][i],SNAKE.LocatPoint[Y][i],SNAKE.LocatPoint[X][i+1],SNAKE.LocatPoint[Y][i+1]);
	}
	
	//Fill Snake Head Color
	Snake_FillArea(SnakeColor_Head,SNAKE.LocatPoint[X][Head]-SnakeThickness/2,SNAKE.LocatPoint[Y][Head]-SnakeThickness/2,SNAKE.LocatPoint[X][Head]+SnakeThickness/2,SNAKE.LocatPoint[Y][Head]+SnakeThickness/2);
	
	//Refresh Frame
	Snake_DisplayFrame();
	delay_ms(Snake_MoveSpeed);
	
}
