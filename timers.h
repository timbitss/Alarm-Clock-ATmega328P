//Timer Function Prototypes
#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>

#define disableSoundTimer  DDRB &= ~(1<<PB1)
#define enableSoundTimer   DDRB |= (1<<PB1) //set pin as output

void initializeSecondsTimer(void); //initialize seconds timer (T0)

void initializeDebounceTimer(void); //initialize debounce timer (T2)

void initializeSoundTimer(void); //initialize sound timer (T1)

void setSoundPitch(const uint16_t value); //set sound pitch, param is based on faudio = fCPU/(64*(2(OCR1A + 1)))


#endif