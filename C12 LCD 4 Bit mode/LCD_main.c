/*
 * Initialize the hitachi HD44780 screen in 4-bit mode, then display a character. 
 * Created by TronClub.com
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
  LCD_init();
  clear_display();
  
  print_string("Andrew Rocks!");
  // New line
  print_string("       ");
  print_string("Easier than expected");
  
  return 0;
}
