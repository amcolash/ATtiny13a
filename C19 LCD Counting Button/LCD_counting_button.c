/*
 * Add a button interrupt, which causes a variable to count up every time button is pressed.
 * We use PCINT4 as our button interrupt, since PB4 is controlled by our button.
 * Debounce has to be taken into account when counting the number of button presses. 
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


char counter = 0; 	//This variable is used to deal with switch debounce. 
int flash_num =0;	//This variable keeps track of how many times the "count" button was pressed.

ISR(TIM0_OVF_vect)	//timer module used for debounce
{
  counter++;
} 


int main(void) {
  LCD_init();

	PCMSK |= (1<<PCINT4);	
	GIMSK |= (1<<PCIE);		
	sei(); 							
	TIMSK0 |= (1<<TOIE0);	


	clear_display();
	cursor_right();
  Disp_num(0);

	for (;;){ 
		_delay_ms(10); 		
		if (counter<50) { 						//Stop counting to prevent overflow. 
			TCCR0B |= (1<<CS00);					//enable timer overflow interrupt by setting its prescale
		} else {
		  TCCR0B &= 0B11111000;			//if counter is over 50 the timer is no longer needed. the next button change will be counted. 
	  }
	}
	return 0;
}

void base_convert(int num, int base){
  char remainder;
  char index = 0 ;
  char digit[4];
  while(num != 0){
     remainder = (num%base);
     num = (num/base);
     digit[index] = remainder;
     Disp_num(digit[index]);
     index++;
     shift_cursor();
     shift_cursor();
   }
}

void Disp_num(int num) {			//Takes in a number from 0 to 9 and displays it on screen.
  char remainder;
  char index = 0 ;
  char digit[4]={0,0,0,0};
  while(num != 0){
     remainder = (num%2);
     num = (num/2);
     digit[index] = remainder;
     index++;
	  }
  LCD_data(0,0,1,1,digit[3],digit[2],digit[1],digit[0]);
}


ISR (PCINT0_vect) 			// ISR when "Count" Button is pressed.
{ 
	TCCR0B &= 0B11111000;;				//Disable timer interrupts. The button has been pressed.
	if (counter < 15){
		counter = 0;						// We haven't reached 15 counts, so what caused the trigger is just a bounce. No change to LED.
	}	else {
		counter = 0;					//if counter is greater than 15, the trigger is an actual button press so change LED output.
		
	  flash_num++;
	
	  clear_display();
	  cursor_right();
	  base_convert(flash_num, 10);
	}
}
