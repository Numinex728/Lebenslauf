/*
* Autor: Jan Remfert
*/

#include <stdint.h>
#include "stm32f10x.h"
#include "warten.h"

int main(void)
{
	//Timer initialisierung, für zeitgesteuertes Event
	setup_tim6();
	
	//Enablen von Port A, B, C, D und E
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN + RCC_APB2ENR_IOPBEN + RCC_APB2ENR_IOPDEN + RCC_APB2ENR_IOPCEN + RCC_APB2ENR_IOPEEN;
	
	while(1)
	{
	
		
		
	}
	
	//return 0;
}
