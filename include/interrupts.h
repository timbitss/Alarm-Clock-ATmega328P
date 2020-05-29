//Initializes interrupts
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/io.h>


void initializeSecondsInterrupt(void); //initializes Timer 0 interrupts for seconds timer
void initializeADCInterrupt(void); //initializes ADC interrupts

#endif
