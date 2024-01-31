#include "user_interface.h"

#include <stdio.h>   // for fprintf, NULL, stderr
#include <stdlib.h>  // for exit

#include "SDL_error.h"    // for SDL_GetError
#include "SDL_pixels.h"   // for SDL_Color
#include "SDL_rect.h"     // for SDL_Rect
#include "SDL_render.h"   // for SDL_Texture, SDL_DestroyTexture, SDL_QueryT...
#include "SDL_surface.h"  // for SDL_FreeSurface, SDL_Surface
#include "SDL_ttf.h"      // for TTF_SetFontOutline, TTF_GetError, TTF_Close...
#include "graphics.h"     // for get_renderer

// Assuming global variables for font and renderer
static TTF_Font* font = NULL;
static SDL_Renderer* renderer = NULL;

// Function prototypes for internal use
static SDL_Texture* create_text_texture(const char* string, SDL_Color color);
static int calculate_render_x(int x, TextAlignment alignment, int text_width);
static void render_text(SDL_Texture* texture, int x, int y, int width,
                        int height);

void initiate_user_interface(void) {
  renderer = get_renderer();  // Assuming get_renderer() is defined elsewhere

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n",
            TTF_GetError());
    exit(1);
  }

  // Load a font
  font = TTF_OpenFont("./assets/fonts/Silkscreen-Regular.ttf",
                      24);  // Specify your font path and size
  if (font == NULL) {
    fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    exit(1);
  }
}

void print_user_interface_with_outline(
    const char* string, int x, int y, TextAlignment horizontal_text_alignment) {
  if (!renderer || !font) {
    fprintf(stderr, "UI not initialized or font not loaded.\n");
    return;
  }

  SDL_Color outline_color = {80, 80, 80, 255};  // Dark gray outline
  int outline_size = 2;

  // Set the font outline
  TTF_SetFontOutline(font, outline_size);

  // Create texture for the outline
  SDL_Texture* outline_texture = create_text_texture(string, outline_color);
  if (!outline_texture) {
    return;
  }

  int text_width, text_height;
  SDL_QueryTexture(outline_texture, NULL, NULL, &text_width, &text_height);
  int render_x = calculate_render_x(x, horizontal_text_alignment, text_width);
  render_text(outline_texture, render_x - outline_size / 2,
              y - outline_size / 2, text_width, text_height);

  // Clean up
  SDL_DestroyTexture(outline_texture);

  // Set the font outline back to 0 for main text
  TTF_SetFontOutline(font, 0);

  print_user_interface(string, x, y, horizontal_text_alignment);
}

void print_user_interface(const char* string, int x, int y,
                          TextAlignment horizontal_text_alignment) {
  if (!renderer || !font) {
    fprintf(stderr, "UI not initialized or font not loaded.\n");
    return;
  }

  SDL_Color text_color = {255, 255, 255, 255};  // White color

  // Create texture from string
  SDL_Texture* text_texture = create_text_texture(string, text_color);
  if (!text_texture) {
    return;
  }

  int text_width, text_height;
  SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
  int render_x = calculate_render_x(x, horizontal_text_alignment, text_width);
  render_text(text_texture, render_x, y, text_width, text_height);

  // Clean up
  SDL_DestroyTexture(text_texture);
}

void cleanup_user_interface(void) {
  if (font) {
    TTF_CloseFont(font);
    font = NULL;
  }
  TTF_Quit();
}

static SDL_Texture* create_text_texture(const char* string, SDL_Color color) {
  SDL_Surface* text_surface = TTF_RenderText_Solid(font, string, color);
  if (!text_surface) {
    fprintf(stderr, "Unable to render text surface! SDL_ttf Error: %s\n",
            TTF_GetError());
    return NULL;
  }

  SDL_Texture* text_texture =
      SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);
  if (!text_texture) {
    fprintf(stderr,
            "Unable to create texture from rendered text! SDL Error: %s\n",
            SDL_GetError());
  }

  return text_texture;
}

static int calculate_render_x(int x, TextAlignment alignment, int text_width) {
  switch (alignment) {
    case TEXT_ALIGN_CENTER:
      return x - text_width / 2;
    case TEXT_ALIGN_RIGHT:
      return x - text_width;
    case TEXT_ALIGN_LEFT:
    default:
      return x;
  }
}

static void render_text(SDL_Texture* texture, int x, int y, int width,
                        int height) {
  SDL_Rect render_quad = {x, y, width, height};
  SDL_RenderCopy(renderer, texture, NULL, &render_quad);
}
