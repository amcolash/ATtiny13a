/*
 * Use the ATtiny13's built-in ADC to get a voltage reading from a potentiometer.
 * Use 4 output LEDs to indicate the value
 * We use ADC2, which is PB4. 
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>

#define OUT1 PB0
#define OUT2 PB1
#define OUT3 PB2
#define OUT4 PB3

int main(void) {
  int adc_val;
  DDRB = (1<<OUT1) | (1<<OUT2) | (1<<OUT3) | (1<<OUT4);
  PORTB = 0;
  ADMUX |= (1 << MUX1);		//Select input channel ADC2 (PB4). See Table 14-3 of ATtiny13 Datasheet.
  ADMUX |= (1 << ADLAR);		//Left-Adjust result.

  // Set clock prescaler (/8). See table 14-4.
  // (1<<ADEN) must be set to 1 to allow ADC. 
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
  
  while (1) {
    adc_val = adc_read();
    PORTB = (ADCH >>4) << PORTB0;
  }
  
  return 0;
}

int adc_read (void) {
  // Start the conversion
  ADCSRA |= (1 << ADSC);

  // Wait for it to finish
  while (ADCSRA & (1 << ADSC));		//(1<<ADSC) returns 0 when the conversion is complete.
  return ADCH;
}
