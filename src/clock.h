#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>

// Function to get the current time
Uint32 get_now();

// Function to get the previous time
Uint32 get_prev();

// Function to get the elapsed time since the last update
Uint32 get_elapsed_time();

// Function to update the current and previous time
void set_time();

#endif  // CLOCK_H
