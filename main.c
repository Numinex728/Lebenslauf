int main(){
 //Port A anschalten
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//Enable Port A für PA4
	GPIOA->CRL &= 0xFFF0FFFF; 
  
  uint16_t erg; //enthält ergebnis des AD-Wandlers
  
  while(1){
   erg = konvertiere(4); //Kanal 4, da PA4 
    
    //Ab hier mit erg machen, was man braucht
  }
}
