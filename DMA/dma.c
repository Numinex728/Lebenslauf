#include <stdint.h>
#include "stm32f10x.h"
#include "warten.h"
#include "adc.h"
#include "dma.h"

uint16_t data; 

void init_dma(void){
	//DMA Takt einswitchen
	RCC-> AHBENR |= RCC_AHBENR_DMA1EN;
	tim6_wait_ms(20);
	
	//|= ADC1 -> DR;
	DMA1_Channel1 -> CPAR = (uint32_t)&(ADC1 -> DR);
	DMA1_Channel1 -> CMAR = (uint32_t)&data;
	DMA1_Channel1 -> CNDTR = 20;
	DMA1_Channel1 -> CCR |= DMA_CCR1_PL;
	DMA1_Channel1 -> CCR |= DMA_CCR1_CIRC;
	DMA1_Channel1 -> CCR |= DMA_CCR1_PINC;
	DMA1_Channel1 -> CCR |= DMA_CCR1_MINC;
	DMA1_Channel1 -> CCR |= DMA_CCR1_MSIZE_1;
	DMA1_Channel1 -> CCR |= DMA_CCR1_PSIZE_1;
	DMA1_Channel1 -> CCR |= DMA_CCR1_EN;
}
