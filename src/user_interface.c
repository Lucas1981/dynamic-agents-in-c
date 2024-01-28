#include "user_interface.h"

#include "graphics.h"

// Assuming global variables for font and renderer
static TTF_Font* font = NULL;
static SDL_Renderer* renderer = NULL;

// Function prototypes for internal use
static SDL_Texture* create_text_texture(const char* string, SDL_Color color);
static int calculate_render_x(int x, TextAlignment alignment, int textWidth);
static void render_text(SDL_Texture* texture, int x, int y, int width,
                        int height);

void initiate_user_interface() {
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

void print_user_interface_with_outline(const char* string, int x, int y,
                                       TextAlignment horizontalTextAlignment) {
  if (!renderer || !font) {
    fprintf(stderr, "UI not initialized or font not loaded.\n");
    return;
  }

  SDL_Color outlineColor = {80, 80, 80};  // Dark gray outline
  int outlineSize = 2;

  // Set the font outline
  TTF_SetFontOutline(font, outlineSize);

  // Create texture for the outline
  SDL_Texture* outlineTexture = create_text_texture(string, outlineColor);
  if (!outlineTexture) {
    return;
  }

  int textWidth, textHeight;
  SDL_QueryTexture(outlineTexture, NULL, NULL, &textWidth, &textHeight);
  int render_x = calculate_render_x(x, horizontalTextAlignment, textWidth);
  render_text(outlineTexture, render_x - outlineSize / 2, y - outlineSize / 2,
              textWidth, textHeight);

  // Clean up
  SDL_DestroyTexture(outlineTexture);

  // Set the font outline back to 0 for main text
  TTF_SetFontOutline(font, 0);

  print_user_interface(string, x, y, horizontalTextAlignment);
}

void print_user_interface(const char* string, int x, int y,
                          TextAlignment horizontalTextAlignment) {
  if (!renderer || !font) {
    fprintf(stderr, "UI not initialized or font not loaded.\n");
    return;
  }

  SDL_Color textColor = {255, 255, 255};  // White color

  // Create texture from string
  SDL_Texture* textTexture = create_text_texture(string, textColor);
  if (!textTexture) {
    return;
  }

  int textWidth, textHeight;
  SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
  int render_x = calculate_render_x(x, horizontalTextAlignment, textWidth);
  render_text(textTexture, render_x, y, textWidth, textHeight);

  // Clean up
  SDL_DestroyTexture(textTexture);
}

void cleanup_user_interface() {
  if (font) {
    TTF_CloseFont(font);
    font = NULL;
  }
  TTF_Quit();
}

static SDL_Texture* create_text_texture(const char* string, SDL_Color color) {
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, string, color);
  if (!textSurface) {
    fprintf(stderr, "Unable to render text surface! SDL_ttf Error: %s\n",
            TTF_GetError());
    return NULL;
  }

  SDL_Texture* textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);
  if (!textTexture) {
    fprintf(stderr,
            "Unable to create texture from rendered text! SDL Error: %s\n",
            SDL_GetError());
  }

  return textTexture;
}

static int calculate_render_x(int x, TextAlignment alignment, int textWidth) {
  switch (alignment) {
    case TEXT_ALIGN_CENTER:
      return x - textWidth / 2;
    case TEXT_ALIGN_RIGHT:
      return x - textWidth;
    case TEXT_ALIGN_LEFT:
    default:
      return x;
  }
}

static void render_text(SDL_Texture* texture, int x, int y, int width,
                        int height) {
  SDL_Rect renderQuad = {x, y, width, height};
  SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
