#include "utilities.h"

u8 key_state;				// debounced and inverted key state: bit = 1: key pressed
u8 key_press;				// key press detect


u8 get_key_press( u8 key_mask )
{
  ATOMIC_BLOCK(ATOMIC_FORCEON){		// read and clear atomic !
    key_mask &= key_press;		// read key(s)
    key_press ^= key_mask;		// clear key(s)
  }
  return key_mask;
}