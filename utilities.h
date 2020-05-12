#ifndef UTILITIES_H
#define UTILITIES_H

#include <util/atomic.h>
#include "GlobalDefinitions.h"
#include "lcd.h"


extern u8 key_state;				// debounced and inverted key state: bit = 1: key pressed
extern u8 key_press;				// key press detect

u8 get_key_press( u8 key_mask ); //gets key press from bank of pins
void placeNum(unsigned int number, uint8_t startx, uint8_t y); //places hours/minutes/seconds



#endif