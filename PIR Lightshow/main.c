#include <stdint.h>
#include <math.h>
#include "stm32f10x.h"
#include "warten.h"
#include "interrupt.h"
#include "pir.h"

//Minimaler gemessener Wert Mikro: 1100 0001 1111
#define MIN_VALUE 0xC1F

volatile uint16_t i = 0;

int main(void)
{
	//Timer initialisierung, für zeitgesteuertes Event
	setup_tim6();
	
	//PIR Initialisierung
	pir_init();
	
	//Enablen von Port A, B, C, D und E und Alternate Function Takt
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN + RCC_APB2ENR_IOPBEN + RCC_APB2ENR_IOPDEN + RCC_APB2ENR_IOPCEN + RCC_APB2ENR_IOPEEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
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
	
	//Einstellen von Ports Dx auf Mode 11 und CNF 00
	GPIOD->CRL = 0x33333333;
	GPIOD->CRH = 0x33333333;
	 
	//Hierbei soll der minimal gemessene Wert als Startwert verwendet werden. Dieser Wert soll dann auf 12 Ports abgebildet werden
	//uint16_t scope = 0xFFF - MIN_VALUE;
	double stepsize = (0xFFF - MIN_VALUE) / 12.0;
	
	uint16_t j = 0;
	while(1)
	{
		//Nutzen von Mikro Peripherie
		i = convert();
		
		//Ermitteln von benötigter Portmenge via Stepsize
		i = i - MIN_VALUE;
		i = (uint16_t)(i / stepsize);
		
		//Abbildung von Portmenge auf 2er Potenzen und damit tatsächlich benötigtem Zahlenwert zum Portsetzen
		i = (uint16_t)(pow(2, i) - 1);
		
		if(j++ % 2)
			GPIOD->ODR = i;
	}
	
	//tim6_wait_ms(3000);
	//EXTI0_IRQHandler();
	//GPIOD->ODR = 0xFFFF;
	//GPIOD->BSRR = GPIO_BSRR_BS0;
	//GPIOD->BSRR = GPIO_BSRR_BR0;
	//9 Ports, 18 Reihen, 72 Positionen
}
