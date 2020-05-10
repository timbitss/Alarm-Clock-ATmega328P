// Alarm Clock Project
// Author: Timothy Nguyen
// Features: Displays Time
//
//
//
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "timers.h"
#include "interrupts.h"

#define intPerMin 230 //number of interrupts per minute

volatile char secondtick = 0; 
volatile char minutes = 0;

ISR(TIMER0_OVF_vect){
    secondtick++;
    if(secondtick == intPerMin){
        secondtick = 0;
        minutes++;
    }
}

int main(void){

   initializeSecondsTimer();
   initializeSecondsInterrupt();
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   sei(); //enable global interrupts

   while(1){ //loops forever
    
    lcd_putc('a'); //display minutes elapsed
    

   }



    return 0;
}