#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"

#include "hd44780_i2c.h"
#include "i2c.h"


/*
 - Anbindung des LCDs über einen I2C-Portexpander PCF8574
 - LCD im 8080-Modus (4 Bit-Parallelport)

 - Anschluss des Portexpanders an das LCD:
	 P0 --> RS			0 = Befehl, 1 = Daten
	 P1 --> R/W			0 = schreiben, 1 = lesen
	 P2 --> E				Enable
	 P3 --> ---
	 P3 --> D4			Daten-Bit 0 (LSB)
	 P5 --> D5			Daten-Bit 1
	 P6 --> D6			Daten-Bit 2
	 P7 --> D7			Daten-Bit 3 (MSB)
*/



//--------------------------------------------------------------
// Init für das Display
//--------------------------------------------------------------
void LCD_init(void)
{
	LCD_wait(LCD_DELAY_INIT);
	
	// Erster Init Impuls
	LCD_clock( 0x38);
	LCD_wait(LCD_DELAY_20000);

	// Zweiter Init Impuls
	LCD_clock( 0x38);
	LCD_wait(LCD_DELAY_20000);

	// Dritter Init Impuls
	LCD_clock( 0x38);
	LCD_wait(LCD_DELAY_20000);

	// LCD-Modus einstellen (4Bit-Mode)
	LCD_clock( 0x28);
	LCD_wait(LCD_DELAY_INIT);
	
	
	// LCD-Settings einstellen
	LCD_sendCmd(0x28);	// 2 Zeilen Display, 5x7 Punkte
	LCD_sendCmd(0x06);  // Cursor increase, Display fix
	LCD_sendCmd(0x0C); 	// Display=EIN, Cursor=AUS, Blinken=Aus	
	LCD_sendCmd(0x01); 	// Display löschen
	LCD_wait(LCD_DELAY_INIT);
}


//--------------------------------------------------------------
// Löscht das Text-LCDisplay
//--------------------------------------------------------------
void LCD_Clear(void)
{
	LCD_sendCmd(0x01);					// Kommando 0x01 löscht Display (siehe https://www.mikrocontroller.net/articles/HD44780#Kommandos)
	LCD_wait(LCD_DELAY_20000);
}


//--------------------------------------------------------------
// Ausgabe von einem String auf dem Display an x,y Position
// x : 0 bis 39
// y : 0 bis 3
//--------------------------------------------------------------
void LCD_String( uint8_t x, uint8_t y, char *ptr)
{
	LCD_setCursor( x, y);
	while (*ptr != 0)
	{
		LCD_data( *ptr);
		ptr++;
	}
}





//--------------------------------------------------------------
// einen Clock Impuls ausgeben
//--------------------------------------------------------------
void LCD_clock( uint8_t wert)
{
	uint8_t reg_adr = 0x80;

	// Pin-E auf Hi 
	uint8_t byte = wert | 0x04;	
	i2c_writeByte(SLAVE_ADDR, reg_adr, byte);
	LCD_wait(LCD_DELAY_500);

	// Pin-E auf L 
	byte = wert & 0xFB;
	i2c_writeByte(SLAVE_ADDR, reg_adr, byte);
	LCD_wait(LCD_DELAY_500);
}


//--------------------------------------------------------------
// Kommando an das Display senden
//--------------------------------------------------------------
void LCD_sendCmd( uint8_t wert)
{
	uint8_t l_byte, h_byte;

	// H-Nibble ausgeben | RS=Lo (Command)
	h_byte = (wert & 0xf0) | 0x08;
	LCD_clock( h_byte);
	
	// L-Nibble ausgeben
	l_byte = ((wert << 4) & 0xf0) | 0x08;
	LCD_clock( l_byte);
}

//--------------------------------------------------------------
// Daten an das Display senden
//--------------------------------------------------------------
void LCD_data( uint8_t wert)
{
	// H-Nibble ausgeben
	uint8_t h_byte = (wert & 0xf0)  | 0x09;
	LCD_clock( h_byte);
	
	// L-Nibble ausgeben
	uint8_t l_byte = ((wert << 4) & 0xf0) | 0x09;
	LCD_clock( l_byte);
}

//--------------------------------------------------------------
// Cursor auf x,y stellen
//--------------------------------------------------------------
void LCD_setCursor( uint8_t x, uint8_t y)
{
	// Cursor position: 0x80 + position
	uint8_t wert;

	if(x>=SPALTEN) x=0;
	if(y>=ZEILEN) y=0;

	if(y==0)
		wert = 0x80 + 0x00 + x;
	else if(y==1)
		wert = 0x80 + 0x40 + x;
	else if(y==2)
		wert = 0x80 + 0x14 + x;
	else if(y==3)
		wert = 0x80 + 0x54 + x;
	else
		wert = 0x80 + 0x00 + x; //handle undefined y value!

	LCD_sendCmd( wert);
}

//--------------------------------------------------------------
// kleine Pause (ohne Timer)
//--------------------------------------------------------------
void LCD_wait(volatile uint32_t nCount)
{
  while(nCount--)
  {
  }
}
