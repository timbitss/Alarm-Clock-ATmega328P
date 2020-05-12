// Alarm Clock Project
// Author: Timothy Nguyen
// Features: Displays Adjustable Time
//
//
//
// Credits: Peter Dannegger for Debouncing Technique, Peter Fleury for LCD Driver and Controller  

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "lcd.h"
#include "timers.h"
#include "interrupts.h"
#include "utilities.h"
#include "GlobalDefinitions.h"


#define ticksPerSec 61 //number of interrupts per second with prescaler of 64

unsigned int seconds = 0; //for main function
volatile unsigned int minutes = 0; //for main function



ISR(TIMER0_OVF_vect){ 
    static uint8_t secondtick = 0;
    secondtick++;          //acts as interrupt counter for Timer 0
    if(secondtick == ticksPerSec){
        secondtick = 0;
        seconds++;
    }
    if(seconds == 60){
        seconds = 0;
        minutes++;
    }
}



ISR( TIMER2_COMPA_vect )		// every 10ms (Sampling 4 times)
{
  static u8 ct0 = 0xFF, ct1 = 0xFF;	// 8 * 2bit counters
  u8 i;

  i = ~PINC;				// read keys (low active)
  i ^= key_state;			// key changed ?
  ct0 = ~( ct0 & i );			// reset or count ct0
  ct1 = ct0 ^ (ct1 & i);		// reset or count ct1
  i &= ct0 & ct1;			// count until roll over ?
  key_state ^= i;			// then toggle debounced state
  key_press |= key_state & i;		// 0->1: key press detect
}



int main(void){


    key_state = 0; //buttons not pressed initially	


    initializeDebounceTimer(); //initializes compare match interrupt as well
    initializeSecondsTimer();
    initializeSecondsInterrupt();
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();

    DDRC &= ~((1<<DD4)|(1<<DD5)); //setting PC4 and PC5 as input
    PORTC |= (1<<PORT4) | (1<<PORT5); //enable internal pullup-resistor for PC4
    

    sei(); //enable global interrupts
 

    while(1){ //loops forever
        
        placeNum(seconds,3,0);
        lcd_gotoxy(2,0);
        lcd_putc(':');
        placeNum(minutes,0,0);
        
        if( get_key_press(1<<PINC4)){ //check if seconds pushbutton is pressed
            minutes++;
        }
        if( get_key_press(1<<PINC5)){
            seconds++;
        }
        if( minutes == 60){
          minutes = 0;
        }

    } 



    return 0;
}



