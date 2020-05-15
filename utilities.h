#ifndef UTILITIES_H
#define UTILITIES_H

#include <util/atomic.h>
#include <stdlib.h>
#include "GlobalDefinitions.h"
#include "lcd.h"



extern u8 key_state;				// debounced and inverted key state: bit = 1: key pressed
extern u8 key_press;				// key press detect

u8 get_key_press( u8 key_mask ); //gets key press from bank of pins

void placeTemperature(unsigned long number, uint8_t startx, uint8_t y); //places temp
void placeTime(unsigned int hours, unsigned int minutes, unsigned int seconds, uint8_t startx, uint8_t y);
void placeString(const char* str, uint8_t startx, uint8_t y);


#endif