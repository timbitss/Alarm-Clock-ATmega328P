//Timer Function Prototypes
#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>

void initializeSecondsTimer(void); //initialize seconds timer (T0)
void initializeDebounceTimer(void); //initialize debounce timer (T2)

#endif