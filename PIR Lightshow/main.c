#include <stdint.h>
#include <math.h>
#include "stm32f10x.h"
#include "warten.h"
#include "interrupt.h"
#include "pir.h"

#define MIN_VALUE 0xC1F

volatile uint16_t i = 0;

int main(void)
{
	//Timer initialisierung, für zeitgesteuertes Event
	setup_tim6();
	
	//PIR Initialisierung
	pir_init();
	
	//Enablen von Port A, B, C, D und E
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN + RCC_APB2ENR_IOPBEN + RCC_APB2ENR_IOPDEN + RCC_APB2ENR_IOPCEN + RCC_APB2ENR_IOPEEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Konfiguration aller vorher gennanten Ports
	/*
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOC->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOD->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	MODIFY_REG(GPIOE->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	*/
	
	// Eigentlich müssten die Interrupt Routinen eh alles steuern können
	//MODIFY_REG(AFIO->EXTICR[2], AFIO_EXTICR2_EXTI4, AFIO_EXTICR2_EXTI4_PA);
	//MODIFY_REG(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0, AFIO_EXTICR1_EXTI0_PD);
	
	AFIO->EXTICR[1] &= 0xFFFFFFF0;
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI4_PA;
	
	//Interrupt Konfiguration, wie entnommen aus den Vorlesungen und Übungen
	//unmask interrupt
	EXTI->IMR |= EXTI_IMR_MR4;
	//set rising trigger
	EXTI->RTSR |= EXTI_RTSR_TR4;
	//enable interrupt handler call
	NVIC_EnableIRQ(EXTI4_IRQn);
	//clear pending interrupt
	EXTI->PR |= EXTI_PR_PR4;
	
	GPIOD->CRL = 0x33333333;
	GPIOD->CRH = 0x33333333;
	
	uint16_t scope = 0xFFF - MIN_VALUE;
	double stepsize = scope / 12.0;
	GPIOD->BSRR = GPIO_BSRR_BR0;
	
	uint16_t j = 0;
	while(1)
	{
		//GPIOD->BSRR = GPIO_BSRR_BS0;
		i = convert();
		//tim6_wait_ms(3000);
		//EXTI0_IRQHandler();
		//GPIOD->ODR = 0xFFFF;
		//9 Ports, 18 Reihen, 72 Positionen
		//Max Spannung 2V, Minimale Spannung Mikro: 1100 0001 1111 Stufengröße: 
		i = i - MIN_VALUE;
		i = (uint16_t)(i / stepsize);
		i = (uint16_t)(pow(2, i) - 1);
		
		//if(j++ % 2)
		//	GPIOD->ODR = i;
	}
	
	//return 0;
}
