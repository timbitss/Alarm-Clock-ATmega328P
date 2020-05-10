#include "timers.h"
#include <avr/io.h>

void initializeSecondsTimer(void){
    
    
    TCCR0B |= ((1 << CS02) | (1 << CS00)); //initializing Timer 0 to internal CPU clk (1Mhz) / 1024


}