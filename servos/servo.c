/*
 * MCU: ATtiny13
 * Code to control a servo
 * Created by Andrew McOlash 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PWM

/* PWM Version */
#ifdef PWM

int counter = 0;

ISR(TIM0_OVF_vect) {
  counter++;
  if (counter < 8) {
    PORTB = (1<<PB4);
  } else if (counter < 100) {
    PORTB = (0<<PB4);
  } else {
    counter = 0;
  }
} 

int main(void) {
  cli();   //Clears the global interrupt flag
  DDRB = (1<<DDB4); 
  PORTB = 0; 
  TCCR0B |= (0<<CS02) | (0<<CS00) | (1<<CS00) ;   //prescale timer by a factor of 1024 
  TIMSK0 |= (1<<TOIE0);   //enable timer overflow interrupt   
  sei();   //Sets global interrupt bit; Enables interrupts
  while(1);   //loop forever, and let the interrupts do the work. 
}

#endif




/* Software Version */
#ifndef PWM

int main(void) {
	DDRB = (1<<DDB4); // Set PB4 as output

  while(1) {
	  // Should be at center (1.5ms)
	  int delay = 1500;
	
	  PORTB = (1<<PB4); // Set output of PB4 as HIGH.
	  _delay_us(delay);
	  PORTB = (0<<PB4); // Set output of PB4 as LOW.
	  _delay_us(25000 - delay);
  }

	return 0;
}

#endif
