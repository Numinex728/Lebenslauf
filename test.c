
#include "wartefunktionen.h"
#include "funnytacho.h"
#include "warten.h"
#include "servo.h" //Accept Niederlage
#include "gettingJumped.h"

int main (void)
{
	//Ansprechen von Port D/L
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	MODIFY_REG(GPIOD->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	
	//Ansprechen von Port A0
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
	
	init_servo();
	
	//Port C einschalten
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRL &= 0xFFFFFFF0;
	
	//Port D enabled für Testen
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	GPIOD->CRL = 0x33333333;
	GPIOD->CRH = 0x33333333;
	
	set_Wandler();
	
	while(1){
		
		int16_t i;
		//Kleines Offset, vielleicht gibt es ein besseres
		for(i = 0; i < 101; i += 10)
		{
			set_servo(i);
			busy_wait_ms(1000);
			
		}
		
		
		konvertieren(3);
		
		GPIOA->BSRR = GPIO_BSRR_BS0;	
		
		wait_10us(2000);
		//busy_wait_mikro_skalierbarer(1285);
		//busy_wait_ms(100);
		//tim6_wait_ms (1);
		
		
		GPIOA->BSRR = GPIO_BSRR_BR0;	
		
		wait_10us(2000);
		//busy_wait_mikro_skalierbarer(24427);
		//busy_wait_ms(10000);
		//tim6_wait_ms (1);
		

	}
	
	
	//setup_timer6_ms(1);
	
	//while(1);
	
}
