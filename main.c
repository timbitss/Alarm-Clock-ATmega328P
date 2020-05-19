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
#include <stdlib.h>
#include <avr/pgmspace.h>


#include "lcd.h"
#include "timers.h"
#include "interrupts.h"
#include "utilities.h"
#include "GlobalDefinitions.h"
#include "ADC.h"
#include "SPI.h"

#define ticksPerSec 61 //number of interrupts per second with prescaler of 64

static volatile unsigned int seconds = 0; //for main.c
static volatile unsigned int minutes = 0; //for main.c
static volatile unsigned int hours = 0; //for main.c



ISR( TIMER0_OVF_vect ){ 
    static uint8_t secondtick = 0;
    secondtick++;          //acts as interrupt counter for Timer 0
    if(secondtick == ticksPerSec){
        secondtick = 0;
        seconds++;
    }
}



ISR( TIMER2_COMPA_vect )		// every 10ms (Sampling 4 times)
{
  static u8 ct0 = 0xFF, ct1 = 0xFF;	// 8 * 2bit counters
  u8 i;

  i = ~PIND;				// read keys (low active)
  i ^= key_state;			// key changed ?
  ct0 = ~( ct0 & i );			// reset or count ct0
  ct1 = ct0 ^ (ct1 & i);		// reset or count ct1
  i &= ct0 & ct1;			// count until roll over ?
  key_state ^= i;			// then toggle debounced state
  key_press |= key_state & i;		// 0->1: key press detect
}





int main(void){

    static unsigned int almSeconds = 0;
    static unsigned int almMinutes = 0;
    static unsigned int almHours = 0;
    static uint8_t setAlarmFlag = 0; //1 = set alarm time
    static uint8_t toggleAlarmFlag = 0; //1 = alarm on
    static uint8_t temp;
    static uint32_t temperature;

    key_state = 0; //buttons not pressed initially	
    
    initializeDebounceTimer(); //initializes compare match interrupt as well
    initializeSecondsTimer();
    initializeSecondsInterrupt();
    lcd_init(LCD_DISP_ON);
    ADCInit();
    ADCSelectTemp(); //free running mode
    lcd_clrscr();
    SPI_MasterInit(); //for temperature sensor

    DDRC &= ~(1 << DD4); //Set PC4 as input (for ADC)
    DDRD &= ~((1<<DD0) | (1<<DD1) | (1<<DD5) | (1<<DD6) | (1<<DD7)); //setting as input (for pushbuttons)
    PORTD |= ((1<<PORT0) | (1<<PORT1) | (1<<PORT5) | (1<<PORT6) | (1<<PORT7)); //enable internal pullup-resistor 
    DDRB |= ((1 << SS)) ; //enable PB2 (SS) as output

    sei();
 

    while(1){ //loops forever


    
        placeTime(hours,minutes,seconds,0,0);

        SPI_StartTransmission;
        SPI_MasterTransmitReceive(TEMPSTARTBYTE);
        temp = SPI_MasterTransmitReceive(TEMPSELCHANNEL0);
        temp &= 0x03; //only care about last two bits
        temperature = (temp << 8) | SPI_MasterTransmitReceive(TEMPSELCHANNEL0); //temperature variable contains 10-bit ADC value
        SPI_EndTransmission;
        temperature = (temperature * 500) / 1023; //converting to temperature
        placeTemperature(temperature, 0, 0);
        
        if(toggleAlarmFlag){
            placeTime(almHours,almMinutes, almSeconds,0,1);
            placeString("AlarmOn", 9, 1);
        }
        else{
           placeString("                      ", 0,1);
        }

        if(get_key_press(1<<PIND6)){
            setAlarmFlag ^= 1; //toggle
        }
        if(get_key_press(1<<PIND7)){
            toggleAlarmFlag ^= 1; //toggle
        }
        
        if (!setAlarmFlag){
            if( get_key_press(1<<PIND1)){ //check if seconds pushbutton is pressed
            minutes++;
            }
            if( get_key_press(1<<PIND0)){
            seconds++;
            }
            if( get_key_press(1<<PIND5)){
            hours++;
            }
        }
        else{
            if( get_key_press(1<<PIND1)){ //check if seconds pushbutton is pressed
                almMinutes++;
            }
            if( get_key_press(1<<PIND0)){
                almSeconds++;
                
            }
            if( get_key_press(1<<PIND5)){
                almHours++;
            }        
        }
        if(seconds == 60){
            seconds = 0;
            minutes++;
        }
        if(minutes == 60){
            minutes = 0;
            hours++;
        }
        if( hours == 24){
            hours = 0;
        }
        if(almMinutes == 60){
            almMinutes = 0;
            almHours++;
        }
        if(almSeconds == 60){
            almSeconds = 0;
            almMinutes++;
        }
        if(almHours == 24){
            almHours = 0;
        }

    } 



    return 0;
}



