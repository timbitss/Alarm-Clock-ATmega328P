#include "timers.h"


void initializeSecondsTimer(void){
    
    
    TCCR0B |= ((1 << CS01) | (1 << CS00)); //initializing Timer 0 to internal CPU clk (1Mhz) / 64 operating in normal mode


}

void initializeDebounceTimer(void){

    TCCR2B |= (1 << CS21) ; //initializing Timer 2 to CPU clk / 8 operating in normal mode

}