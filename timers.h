//Timer Function Prototypes
#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>

#define disableSoundTimer TCCR1B &= ~((1<<CS11)|(1<<CS10))
#define enableSoundTimer TCCR1B |=  ((1<<CS11) | (1<<CS10));

void initializeSecondsTimer(void); //initialize seconds timer (T0)

void initializeDebounceTimer(void); //initialize debounce timer (T2)

void initializeSoundTimer(void); //initialize sound timer (T1)

void setSoundPitch(const uint16_t value); //set sound pitch, param is based on faudio = fCPU/(64*(2(OCR1A + 1)))


#endif