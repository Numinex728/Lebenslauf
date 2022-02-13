#include "interrupt.h"

//Interrupt Service Routine
void EXTI4_IRQHandler(void){
	//Clear pending interrupt
	EXTI->PR |= EXTI_PR_PR0;	
	extern uint16_t i;
	
	GPIOD->ODR = i;
	
	//EXTI0_PIR();
	
}

	 