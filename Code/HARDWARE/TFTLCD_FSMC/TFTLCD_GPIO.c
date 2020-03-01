#include "TFTLCD.h"

void TFTLCD_GPIOConfigInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	//LCD_RST
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//LCD_BackLight
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

}

//Reset TFTLCD
void TFTLCD_Reset(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	delay_ms(30);
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	delay_ms(30);
}
