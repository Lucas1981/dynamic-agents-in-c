#ifndef SCREENS_H
#define SCREENS_H

#include <SDL.h>

typedef enum {
  TITLE_SCREEN,
  LEVEL_SCREEN,
  NUM_SCREENS  // Number of screens, always keep this last
} ScreenType;

void load_screens(void);
void draw_screen(ScreenType type);
void cleanup_screens(void);

#endif  // SCREENS_H
