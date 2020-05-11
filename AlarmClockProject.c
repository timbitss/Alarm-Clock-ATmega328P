// Alarm Clock Project
// Author: Timothy Nguyen
// Features: Displays Time
//test
//
//
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "timers.h"
#include "interrupts.h"

#define ticksPerSec 61 //number of interrupts per second with prescaler of 64


volatile char secondtick = 0; 
volatile unsigned int seconds = 0;
volatile unsigned int minutes = 0;

ISR(TIMER0_OVF_vect){
    secondtick++; 
    if(secondtick == ticksPerSec){
        secondtick = 0;
        seconds++;
    }
    if(seconds == 60){
        seconds = 0;
        minutes++;
    }
}

int main(void){

   char buffer[2];
   initializeSecondsTimer();
   initializeSecondsInterrupt();
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   sei(); //enable global interrupts

   while(1){ //loops forever
        
    lcd_gotoxy(1,0);
    itoa( seconds % 10, buffer, 10); //puts first digit in buffer
    lcd_puts(buffer); //displays first digit
    lcd_gotoxy(0,0);
    itoa( seconds / 10, buffer, 10); //puts second digit in buffer
    lcd_puts(buffer); //displays second digit
    
  
    
   

   }



    return 0;
}