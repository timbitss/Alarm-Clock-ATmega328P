#include "timers.h"


void initializeSecondsTimer(void){
    
    
    TCCR0B |= ((1 << CS01) | (1 << CS00)); //initializing Timer 0 to internal CPU clk (1Mhz) / 64 operating in normal mode


}

void initializeDebounceTimer(void){

    TCCR2A = 1<<WGM21;			// T2 Mode 2: CTC
    TCCR2B = (1<<CS22 | 1<< CS21);		// divide by 256
    OCR2A = 39;	// ~10ms per interrupt
    TIMSK2 = 1<<OCIE2A;			// enable T2 interrupt

}
