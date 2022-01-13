#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"

#include "i2c.h"


//--------------------------------------------------------------
// Initialisiert I2C
// fastmode: true, false
// apbl_clk: Peripherietakt
//--------------------------------------------------------------
void i2c_init(bool fastMode, uint32_t apb1_clock)
{
    // Takt für Port B and Alternative Funktionen einschalten
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN + RCC_APB2ENR_AFIOEN);
    
    // Takt für I2C einschalten
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
    
    // Peripherie ausschalten
    CLEAR_BIT(I2C1->CR1, I2C_CR1_PE);

    // Timing konfigurieren
    MODIFY_REG(I2C1->CR2, I2C_CR2_FREQ, apb1_clock/1000000);
    if (fastMode)
    {
        MODIFY_REG(I2C1->CCR, I2C_CCR_CCR, apb1_clock/800000);
        MODIFY_REG(I2C1->TRISE, I2C_TRISE_TRISE, apb1_clock/4000000+1);
    }
    else
    {
        MODIFY_REG(I2C1->CCR, I2C_CCR_CCR, apb1_clock/200000);
        MODIFY_REG(I2C1->TRISE, I2C_TRISE_TRISE, apb1_clock/1000000+1);
    }

    // Peripherie einschalten
    SET_BIT(I2C1->CR1, I2C_CR1_PE);

    // GPIO als Alternative Funktion, Open-Drain und 2 MHz konfigurieren (PB6=SCL, PB7=SDA)
		CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_I2C1_REMAP);
		MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF6 + GPIO_CRL_MODE6, GPIO_CRL_CNF6_0 + GPIO_CRL_CNF6_1 + GPIO_CRL_MODE6_1);
		MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF7 + GPIO_CRL_MODE7, GPIO_CRL_CNF7_0 + GPIO_CRL_CNF7_1 + GPIO_CRL_MODE7_1);
}




//--------------------------------------------------------------
// Sendet ein Byte an den adressierten I2C-Slave
// slave_addr: Bausteinadresse
// addr: Registeradresse
// value: zu sendender Wert
//--------------------------------------------------------------
int i2c_writeByte(uint8_t slave_addr, uint8_t reg_addr, uint8_t value)
{
    // Adresse zurechtrücken
    slave_addr=(uint8_t)((uint16_t)slave_addr << 1);

		// Startbit und Slave-Adresse senden
		SET_BIT(I2C1->CR1, I2C_CR1_START);                     
		while (!READ_BIT(I2C1->SR1, I2C_SR1_SB));              
		WRITE_REG(I2C1->DR,slave_addr);                        
		while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR))             
		{
				if (READ_BIT(I2C1->SR1, I2C_SR1_AF))
				{
						return -1;
				}
		}
		
		// ADDR löschen
    READ_REG(I2C1->SR2);                                
		
		// Registeradresse senden
		WRITE_REG(I2C1->DR, reg_addr);      										
		while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE))           
		{
				if (READ_BIT(I2C1->SR1, I2C_SR1_AF))
				{
						return -1;
				}
		}
		// Warten bis Transfer abgeschlossen ist
		while (!READ_BIT(I2C1->SR1, I2C_SR1_BTF))              
		{
				if (READ_BIT(I2C1->SR1, I2C_SR1_AF))
				{						
						return -1;
				}
		}

    // Datum senden
		WRITE_REG(I2C1->DR, value);      										
		while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE))           
		{
				if (READ_BIT(I2C1->SR1, I2C_SR1_AF))
				{
						return -1;
				}
		}
		// Warten bis Transfer abgeschlossen ist
		while (!READ_BIT(I2C1->SR1, I2C_SR1_BTF))   
		{
				if (READ_BIT(I2C1->SR1, I2C_SR1_AF))
				{
						return -1;
				}
		}
		
		// Stopbit senden
		SET_BIT(I2C1->CR1, I2C_CR1_STOP);                       
		while (READ_BIT(I2C1->CR1, I2C_CR1_STOP));              
		
		return 0;
}
	
	




