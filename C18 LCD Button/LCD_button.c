/*
 * Display "LOW" When button is unpressed, and "HIGH" when button is pressed.
 * Continuously poll PB4 to know if the button is pressed or not.
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void) {

	PCMSK |= (1<<PCINT4);   // pin change mask: listen to the designated pin of port B. (Choose PCINT0,PCINT1, etc...)
	GIMSK |= (1<<PCIE);   // enable Pin-Change interrupt (PCINT)
	sei();   // Set Enable Global Interrupt bit
  DDRB &= ~(1<<DDB4);		//PB4 is an input

  LCD_init();
  clear_display();
  Print_low();

  for (;;) {}
  
  return 0;
}

ISR (PCINT0_vect) {
  clear_display();
  
  if ( ( PINB & (1<<PB4) ) == (1<<PB4))	{ //if PB4 is high, print "HIGH". Else Print "LOW"
	  Print_high();
  } else {
    Print_low();
  }
}


void Print_high(void){		//Prints the word "HIGH"
	LCD_data(0,1,0,0,1,0,0,0);
	LCD_data(0,1,0,0,1,0,0,1);
	LCD_data(0,1,0,0,0,1,1,1);
	LCD_data(0,1,0,0,1,0,0,0);
}

void Print_low(void){		//Prints the word "LOW"
	LCD_data(0,1,0,0,1,1,0,0);
	LCD_data(0,1,0,0,1,1,1,1);
	LCD_data(0,1,0,1,0,1,1,1);
}
