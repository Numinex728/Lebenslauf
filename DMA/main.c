#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"
#include "warten.h"
//#include "wait.h"
//#include "servo.h"
#include "adc.h"
#include "dma.h"
#include "BART.h"
#include "lcdlearnstonotwork.h"

int main(void){
	
	/* Wichtig für ADC Wandler, Teil 1.1
	//enable port D
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	//enable port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= 0xFFFF0FFF;
	//configure port D
	MODIFY_REG(GPIOD->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	GPIOD->CRL = 0x33333333;
	GPIOD->CRH = 0x33333333;
	*/
	
	
	/* UART Implementierung Part 1/2
	setup_tim6();
	//DMA Init und Takt einschalten
	init_dma();
	init_adc();
	init_UART();
	USART1->CR1 |= USART_CR1_RXNEIE; //Interrupt Enablierung
	*/
	
	lcdHelloWorld();
	
	while(1){
		
		//lcdHelloWorld();
		
		
		
		/* UART Implementierung Part 2/2
		char* alex = "Hello World";
		//USART1->DR = 'a';
		UART_learns_to_talk(1, alex, (int)strlen(alex));
		//tim6_wait_ms(200);
		*/
		
		/* ADC Konvertierer für Bitfarben, Teil 1.2 
		uint16_t test = konvertiere(3);
		GPIOD->ODR = test;
		
		set_servo(test*100/4095);
		*/
		
		
		//for(uint16_t i = 0; i <=100; i+=10){
			//set_servo(i);
		//}
		//turn on LED
//		GPIOD->BSRR = GPIO_BSRR_BS0;
//		time6_wait_ms(0);
		//turn off LED
//		GPIOD->BSRR = GPIO_BSRR_BR0;
//		time6_wait_ms(0);
	}
//	return 0;
}
