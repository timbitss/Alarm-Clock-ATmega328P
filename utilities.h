#ifndef UTILITIES_H
#define UTILITIES_H

#include "GlobalDefinitions.h"
#include <util/atomic.h>

extern u8 key_state;				// debounced and inverted key state: bit = 1: key pressed
extern u8 key_press;				// key press detect

u8 get_key_press( u8 key_mask );



#endif