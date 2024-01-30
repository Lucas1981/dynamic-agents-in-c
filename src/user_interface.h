#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef enum {
  TEXT_ALIGN_LEFT,
  TEXT_ALIGN_CENTER,
  TEXT_ALIGN_RIGHT
} TextAlignment;

// Function to initiate the user interface (SDL and SDL_ttf)
void initiate_user_interface();

void print_user_interface_with_outline(const char* string, int x, int y,
                                       TextAlignment horizontal_text_alignment);

// Function to print text to the screen at specified coordinates
void print_user_interface(const char* string, int x, int y,
                          TextAlignment horizontal_text_alignment);

// Function to clean up resources used by the user interface
void cleanup_user_interface();

#endif  // USER_INTERFACE_H
