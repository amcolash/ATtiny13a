/*
 * MCU: ATtiny13
 * Keep one LED turned on while the other flashes using delays
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h> 						// Allows the use of delays

int main(void) {
	DDRB = (1<<DDB4) | (1<<DDB3);     // Set PB3 and PB4 as output

	while(1) {  											//loop forever, alternate which LED is on
//		PORTB = (1<<PB3) | (1<<PB3); 	  //Set output of PB3 and PB4 as HIGH.
		PORTB = (1<<PB3);            	  //Set only PB3 as high, PB4 is low
		_delay_ms(200);
		PORTB = (1<<PB4); 							//Set only PB4 as high, PB3 is low
		_delay_ms(200);
	}
	
	return 0;
}
