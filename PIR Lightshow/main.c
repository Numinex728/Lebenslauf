#include <stdint.h>
#include "stm32f10x.h"
#include "warten.h"
#include "interrupt.h"
#include "pir.h"

int main(void)
{
	//Timer initialisierung, für zeitgesteuertes Event
	setup_tim6();
	
	//PIR Initialisierung
	pir_init();
	
	//Enablen von Port A, B, C, D und E
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN + RCC_APB2ENR_IOPBEN + RCC_APB2ENR_IOPDEN + RCC_APB2ENR_IOPCEN + RCC_APB2ENR_IOPEEN;
	
	//Konfiguration aller vorher gennanten Ports
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOC->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOD->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOE->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	
	/* Eigentlich müssten die Interrupt Routinen eh alles steuern können
	MODIFY_REG(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0, AFIO_EXTICR1_EXTI0_PC);
	MODIFY_REG(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0, AFIO_EXTICR1_EXTI0_PD);
	*/
	
	//Interrupt Konfiguration, wie entnommen aus den Vorlesungen und Übungen
	//unmask interrupt
	EXTI->IMR |= EXTI_IMR_MR0;
	//set rising trigger
	EXTI->RTSR |= EXTI_RTSR_TR0;
	//enable interrupt handler call
	NVIC_EnableIRQ(EXTI0_IRQn);
	//clear pending interrupt
	EXTI->PR |= EXTI_PR_PR0;
	
	
	GPIOD->BSRR = GPIO_BSRR_BS0;
	int i = 0;
	while(1)
	{
		GPIOD->BSRR = GPIO_BSRR_BS0;
		i = convert();
		//tim6_wait_ms(3000);
		//EXTI0_IRQHandler();
		if(i > 1)
		{
			GPIOD->BSRR = GPIO_BSRR_BR0;
			tim6_wait_ms(1000);
		}
	}
	
	//return 0;
}
