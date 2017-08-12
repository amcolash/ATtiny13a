/*
 * Make an LED flash using a timer interrupt.
 * Interrupt Service Routine (ISR) is carried out every time the timer register (TCNT0) overflows. Overflows after 256 counts.
 * The default clock speed of the Attiny13 is 9.6MHz/8 = 1.2 MHz
 * overflow occurs at 256/1200000 = 0.2133 ms. A prescaler of 1024 means overflow occurs every 0.2133*1024 = 218.4 ms
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 	//Allows the use of interrupts

ISR(TIM0_OVF_vect) {
  PORTB ^= (1<<PB4) | (1<<PB3);   //toggle LED ON/OFF
}

int main(void) {
  cli();	//Clears the global interrupt flag
  DDRB = (1<<DDB4) | (1<<DDB3);
  PORTB = (1<<PB3);
  TCCR0B |= (1<<CS02) | (1<<CS00) ;    //prescale timer by a factor of 1024
  TIMSK0 |= (1<<TOIE0);    //enable timer overflow interrupt
  sei();    //Sets global interrupt bit; Enables interrupts
  while(1);	//loop forever, and let the interrupts do the work.
}
