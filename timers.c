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

void initializeSoundTimer(void){

    TCCR1A |= ((1<<COM1A0) | (1<<WGM11) | (1<<WGM10)); //fast PWM mode, toggle on compare match to act as square wave
    TCCR1B |=  ((1<<CS11) | (1<<CS10));
    TCCR1B |= ((1<<WGM13) | (1<<WGM12)); 
    

}

void setSoundPitch(const uint16_t value){ 

    OCR1A = value; //change output compare register

} 
