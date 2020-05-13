#include "utilities.h"

u8 key_state;				// debounced and inverted key state: bit = 1: key pressed
u8 key_press;				// key press detect


u8 get_key_press( u8 key_mask )
{
  ATOMIC_BLOCK(ATOMIC_FORCEON){		// read and clear atomic !
    key_mask &= key_press;		// read key(s)
    key_press ^= key_mask;		// clear key(s)
  }
  return key_mask;
}

void placeNum(unsigned int number, uint8_t startx, uint8_t y){ //places hours/minutes/seconds)
        
        char buff[4]; //to store each digit
        lcd_gotoxy(startx + 1,y);
        utoa( number % 10, buff, 10); //puts first digit in buffer (integer to character string)
        lcd_puts(buff); //displays first digit of seconds
        lcd_gotoxy(startx,y);
        utoa( number / 10, buff, 10); //puts second digit in buffer
        lcd_puts(buff); //displays second digit of seconds

}

void placeTemperature(unsigned long number, uint8_t startx, uint8_t y){
        char buff[2];
        ltoa(number, buff, 10); //converts long to string
        lcd_gotoxy(startx,y);
        lcd_puts(buff);
}