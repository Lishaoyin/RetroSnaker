#include "RNG.h"

void RNG_Init(void)
{
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE);
}

//Get a Random Number Between NumMin and NumMax
u32 RNG_GetRandomNum(u32 NumMin,u32 NumMax)
{
	while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==RESET);
	return RNG_GetRandomNumber()%(NumMax-NumMin+1)+NumMin;
}
