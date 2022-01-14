#include "interrupt.h"

//Interrupt Service Routine ISR
void EXTI0_IRQHandler(void){
	//Clear pending interrupt
	EXTI->PR |= EXTI_PR_PR0;	
	
	uint16_t led_val = GPIOD->IDR &0x1;
	if(led_val == 0x1){
		//turn LED off
		GPIOD->BSRR = GPIO_BSRR_BR0;
	}
	else{
		//Turn LED on
		GPIOD->BSRR = GPIO_BSRR_BS0;
	}
	
}

/*
//enable Port C+D
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN + RCC_APB2ENR_IOPCEN; // |= 0x20;
	
	//enable alternate function I/O to use GPIO for interrupts
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//configure Port D
	MODIFY_REG(GPIOD->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	
	//configure Port C as interrupt
	MODIFY_REG(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0, AFIO_EXTICR1_EXTI0_PC);
	
	//unmask interrupt
	EXTI->IMR |= EXTI_IMR_MR0;
	//set rising trigger
	EXTI->RTSR |= EXTI_RTSR_TR0;
	
	//enable interrupt handler call
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	//clear pending interrupt
	EXTI->PR |= EXTI_PR_PR0;
	*/
	 