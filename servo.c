#include "stdint.h"
#include "stm32f10x.h"
#include "servo.h"
#include "warten.h"


//Beim letzten Servo 2340 und 651
static const uint16_t SERVO_POS_0   = 2340;
static const uint16_t SERVO_POS_100 = 651;

static const uint16_t SERVO_STEP_SIZE = (SERVO_POS_0 - SERVO_POS_100) / 100;

void init_servo(void){
	// setup PA0
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	// set as output with 2 MHz max frequency
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0 + GPIO_CRL_MODE0, GPIO_CRL_MODE0_1);
	// init timer 6
	setup_tim6();
}

void set_servo(int16_t position){
	// calculate high and low ticks
	uint16_t high_ticks = SERVO_POS_0 - SERVO_STEP_SIZE * position; 
	uint16_t low_ticks  = 20000 - high_ticks;
	
	// send 25 pulses (= 0.5 s) to allow servo to switch into position
	for (int i = 0; i < 25; i++){
		// set high	
		GPIOA->ODR = 0x1;		
		tim6_wait_10us(high_ticks / 10);
		// set low
		GPIOA->ODR = 0x0;		
		tim6_wait_10us(low_ticks / 10);
	}
}
