#include "BART.h"
#include "stm32f10x.h"
#include "warten.h"

int init_UART(void)
{	
	//enable port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN + RCC_APB2ENR_AFIOEN;
	MODIFY_REG(GPIOA->CRH, GPIO_CRH_CNF10, GPIO_CRH_CNF10_1); //Mode 10 steht auf 00 für Input Mode
	MODIFY_REG(GPIOA->CRH, GPIO_CRH_CNF9 + GPIO_CRH_MODE9, GPIO_CRH_CNF9_1 + GPIO_CRH_MODE9_0 + GPIO_CRH_MODE9_1); //Mode setzen auf 11 für Output Mode 55MHZ
	
	//Clock Enable für UART
	RCC-> APB2ENR |= RCC_APB2ENR_USART1EN;
	tim6_wait_ms(20);
	
	//USART Enablen
	USART1->CR1 |= USART_CR1_UE;
	//USART1->CR1 |= USART_CR1_M; //Im Reference Manual ist 0 der Reset Wert. Dieser Code setzt die Wortlänge also auf 9 Bit, da wir M auf 1 setzen
	//USART1->CR2 |= USART_CR2_STOP_1; //10 sind 2 Stop Bits, USART Standard
	
	//USART Mantisse und Fraction setzen auf 281,25, für 256.000 Baud Rate 0x1194    Für 9600 0x1D4C    Für 14400 = 0x1388;
	USART1->BRR = 0x7530;
	
	//Transmitter Enablierung
	USART1->CR1 |= USART_CR1_TE; //Transmitter
	USART1->CR1 |= USART_CR1_RE; //Receiver
	
	return 1;
}

//Returned -1 als Fehler, 1 als Erfolg
int UART_learns_to_talk(int isInit, char* data, int length)
{
	//Bei leerem Register oder "fehlendem Init", Fehlercode
	if((isInit != 1))
		return -1;
	
	int i = 0;
	
	while(i < length)
	{
		while((USART1->SR & USART_SR_TXE) == 0);
		USART1->DR = data[i++];
		tim6_wait_ms(10);
	}
	return 1;
}

void UART_learns_to_listen(char* data)
{

	
		if(USART1->SR & USART_SR_RXNE)
		{
		
		data[0] = USART1->DR;
		UART_learns_to_talk(1, data,  1);
		}
		
		
		
	
	
	
}
