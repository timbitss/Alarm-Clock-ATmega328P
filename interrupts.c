#include "interrupts.h"
#include <avr/io.h>

void initializeSecondsInterrupt(void){
    
    TIMSK0 = (1 <<  TOIE0); //enable timer 0 overflow interrupt

}