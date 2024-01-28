#ifndef SCREENS_H
#define SCREENS_H

#include <SDL.h>

// Enum for screen types
typedef enum {
  TITLE_SCREEN,
  LEVEL_SCREEN,
  NUM_SCREENS  // Number of screens, always keep this last
} SCREEN_TYPE;

// Functions
void load_screens();
void draw_screen(SCREEN_TYPE type);
void cleanup_screens();

#endif  // SCREENS_H
