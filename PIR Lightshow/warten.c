#include "stm32f10x.h"
#include "warten.h"

void setup_tim6(void){
	// enable timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// clear config bits
	TIM6->CR1 &= 0xFF70;	
	// set to one pulse mode
	TIM6->CR1 |= TIM_CR1_OPM;	
	// set prescaler to count with 10 kHz (72 MHz / 7200)
	TIM6->PSC = 7199;
	// update config register
	TIM6->EGR |= TIM_EGR_UG;
}


void setup_tim7(void){
	// enable timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	// set prescaler to 71 (count with 1 MHz)
	TIM7->PSC = 71;
	// clear config bits
	TIM7->CR1 &= 0xFF70;
	//enable auto reload
	TIM7->CR1 |= TIM_CR1_ARPE;
	// enable interrupts
	TIM7->DIER |= TIM_DIER_UIE;
	// update register
	TIM7->EGR |= TIM_EGR_UG;
	// register interrupt with interrupt controller
	NVIC_EnableIRQ(TIM7_IRQn);
}

// busy wait by counting 8 NOPs at 8 MHz processor frequency
void wait_us(void){
	for (int i = 0; i < 8; i++){
		__NOP();
	}
}


void tim6_wait_10us(uint16_t us){
	// set prescaler to count with 10 kHz (72 MHz / 7200)
	TIM6->PSC = 71;
	// set max. count value	
	TIM6->ARR = (10*us)-1;
	// reset counter
	TIM6->CNT = 0;	
	// enable timer (go!)
	TIM6->CR1 |= TIM_CR1_CEN;
	// wait until done (enable == 0)
	while(TIM6->CR1 & TIM_CR1_CEN);
}


void tim6_wait_ms(uint16_t ms){
	// set prescaler to count with 10 kHz (72 MHz / 7200)
	TIM6->PSC = 7199;
	// set max. count value	
	TIM6->ARR = (10*ms)-1;
	// reset counter
	TIM6->CNT = 0;
	// enable timer (go!)
	TIM6->CR1 |= TIM_CR1_CEN;
	// wait until done (enable == 0)
	while(TIM6->CR1 & TIM_CR1_CEN);
}



void tim6_wait_s(uint16_t s){
		// set prescaler to count with 2 kHz (72 MHz / 36 k)
	TIM6->PSC = 35999;
	// set max. count value	
	TIM6->ARR = (2000*s)-1;
	// reset counter
	TIM6->CNT = 0;
	// enable timer (go!)
	TIM6->CR1 |= TIM_CR1_CEN;
	// wait until done (enable == 0)
	while(TIM6->CR1 & TIM_CR1_CEN);
}

void tim7_gen_us(uint16_t us){
	// set prescaler to count with 2 MHz
	// so we can count to 2*us-1
	TIM7->PSC = 35;
	// set value to count to
	TIM7->ARR = (us<<1) -1;
	// update register
	TIM7->EGR |= TIM_EGR_UG;
	// start timer 7
	TIM7->CR1 |= TIM_CR1_CEN;
}

void tim7_gen_ms(uint16_t ms){
	// set prescaler to count with 2 kHz
	// so each ms is 2 counts
	TIM7->PSC = 35999;
	// set value to count to
	TIM7->ARR = (ms<<1) -1;
	// update register
	TIM7->EGR |= TIM_EGR_UG;
	// start timer 7
	TIM7->CR1 |= TIM_CR1_CEN;
}

void tim7_gen_s(uint16_t s){
	// set prescaler to count with 1,2 kHz
	// so each s is 1200 counts
	TIM7->PSC = 59999;
	// set value to count to
	TIM7->ARR = (1200 * s) -1;
	// update register
	TIM7->EGR |= TIM_EGR_UG;
	// start timer 7
	TIM7->CR1 |= TIM_CR1_CEN;
}

// Copy this function to implement interrupt handler
//void TIM7_IRQHandler(void){		
	/*
	// clear interrupt flag
	TIM7->SR &= 0xFFFE;
	// do something
	...
	*/
//}
