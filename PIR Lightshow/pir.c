#include "pir.h"
#include "warten.h"

int pir_init(void)
{
	
	//set prescaler
	MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCPRE, RCC_CFGR_ADCPRE_0 + RCC_CFGR_ADCPRE_1);
	//enable clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	//enable ADC1
	ADC1->CR2 |= ADC_CR2_ADON;
	//start
	MODIFY_REG(ADC1->CR2, ADC_CR2_EXTSEL, ADC_CR2_EXTSEL_0 + ADC_CR2_EXTSEL_1 + ADC_CR2_EXTSEL_2);
	//sampling time 41.5
	MODIFY_REG(ADC1->SMPR2,ADC_SMPR2_SMP0, ADC_SMPR2_SMP0_2);
	//wait 20ms
	tim6_wait_ms(20);
	//callibrate
	ADC1->CR2 |= ADC_CR2_ADON + ADC_CR2_CAL;
	//wait for callibration
	while(READ_BIT(ADC1->CR2, ADC_CR2_CAL));

	
	
	
	return 0;
}

uint16_t convert()
{
	
	//Abzahl Kanäle (0 -> 1 Kanal)
	MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, 0);
	//Kanal wählen
	MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, 4);
	//Finish flg
	CLEAR_BIT(ADC1->SR, ADC_SR_EOC);
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_SWSTART;
	//warten
	while(! READ_BIT(ADC1->SR, ADC_SR_EOC));
	//return
	return ADC1->DR & 0x0FFF;
}
