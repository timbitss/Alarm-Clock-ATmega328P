#include "interrupts.h"

void initializeSecondsInterrupt(void){
    
    TIMSK0 = (1 <<  TOIE0); //enable timer 0 overflow interrupt

}

void initializeADCInterrupt(void){

    ADCSRA |= (1 << ADIE);

}

