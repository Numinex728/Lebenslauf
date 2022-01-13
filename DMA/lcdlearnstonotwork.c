#include "lcdlearnstonotwork.h"
#include "warten.h"
#include "stm32f10x.h"

void lcdHelloWorld(void)
{
	
		setup_tim6();
		i2c_init(0, 8000000);
		LCD_init();
		uint8_t y = 1,x =0;
		uint8_t i = 15;
	
		while(1)
		{
			LCD_String(x, y, "I");
			LCD_String(i, 1, "O");
			
			tim6_wait_ms(400);
			LCD_Clear();
			i--;
			
		if (i==0){
			LCD_String(i, 1, "O");
			tim6_wait_ms(400);
			i = 15;
		
		
		
		}


		LCD_Clear();
		if (i==x && y==1){
			
			LCD_String(0, 1, "Verloren");
		tim6_wait_ms(400);
		}
		}
		
		
		
		
}
