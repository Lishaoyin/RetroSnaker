#include "DFC.h"

/*DFC means "Data Flow Capture",This system suite any Single Byte Transmitting*/

//Init
DFC_TypeDef DFC=
{
	0,
	0,
};

//Reset
void DFC_Reset(void)
{
	unsigned char i;
	for(i=0;i<DFC_DataLength_Max;i++)
	{
		DFC.Data[i]=0;
	}
	DFC.Count=0;
}

//Init
void DFC_Init(void)
{
	DFC_Reset();
}

//This Function used to Store Byte one by one
void DFC_DataStore(unsigned DataFlow)
{
	DFC.Data[DFC.Count]=DataFlow;
	DFC.Count++;
	if(DFC.Count==DFC_DataLength_Max) DFC.Count=0;
}

//This Function used to Catch target String
unsigned char DFC_DataCapture(unsigned char* String)
{
	unsigned char p1,p2;
	for(p1=0;p1<DFC_DataLength_Max;p1++)
	{
		for(p2=0;DFC.Data[p1+p2]==String[p2];p2++)
		{
			if(!String[p2+1]) 
				{
					DFC_Reset();
					return 1;
				}
		}
	}
	return 0;
}

