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
#include <util\atomic.h> //to avoid function being interrupted


#define ticksPerSec 61 //number of interrupts per second with prescaler of 64

typedef unsigned char	u8;
typedef signed short	s16;

volatile char secondtick = 0; //acts as interrupt counter for Timer 0
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

u8 key_state;				// debounced and inverted key state:
					        // bit = 1: key pressed
u8 key_press;				// key press detect


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

u8 get_key_press( u8 key_mask )
{
  ATOMIC_BLOCK(ATOMIC_FORCEON){		// read and clear atomic !
    key_mask &= key_press;		// read key(s)
    key_press ^= key_mask;		// clear key(s)
  }
  return key_mask;
}


int main(void){


    char buffer[2];

    PORTC |= (1<<PORT3); //enable internal pullup-resistor for PORTC3

    TCCR2A = 1<<WGM21;			// T2 Mode 2: CTC
    TCCR2B = (1<<CS22 | 1<< CS21);		// divide by 256
    OCR2A = 39;	// 10ms
    TIMSK2 = 1<<OCIE2A;			// enable T0 interrupt
    key_state = 0; //buttons not pressed initially	

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

    if( get_key_press(1<<PINC3)){ //check if seconds pushbutton is pressed
        seconds++;
    }


    
   

   }



    return 0;
}



