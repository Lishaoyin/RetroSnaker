#ifndef _DFC_H
#define _DFC_H

//This Parameter is Changed to suite Data Length
#define DFC_DataLength_Max 50

#endif

typedef struct 
{
	unsigned char Data[DFC_DataLength_Max];
	int Count;
} DFC_TypeDef;

void DFC_Reset(void);
void DFC_Init(void);
void DFC_DataStore(unsigned DataFlow);
unsigned char DFC_DataCapture(unsigned char* String);
