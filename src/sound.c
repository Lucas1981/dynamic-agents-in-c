// sound.c

#include "sound.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

#define MAX_VOLUME MIX_MAX_VOLUME

// Array to hold sound effect pointers
static Mix_Chunk *sound_effects[NUM_SOUNDS];

void init_sounds() {
  // Initialize SDL_mixer, set up channels, etc.
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
           Mix_GetError());
    exit(1);
  }

  // Load sound files
  sound_effects[SCREAM] = Mix_LoadWAV("./assets/sounds/scream.mp3");
  sound_effects[GUNSHOT] = Mix_LoadWAV("./assets/sounds/gunshot.mp3");

  // Check for errors
  for (int i = 0; i < NUM_SOUNDS; ++i) {
    if (!sound_effects[i]) {
      printf("Failed to load sound effect! SDL_mixer Error: %s\n",
             Mix_GetError());
      exit(1);
    }
  }

  // Set volume (optional)
  Mix_Volume(-1, MAX_VOLUME);
}

void play_sound(SoundEnum sound) {
  if (sound >= 0 && sound < NUM_SOUNDS) {
    Mix_PlayChannel(-1, sound_effects[sound], 0);
  }
}

void cleanup_sounds() {
  // Free sound effects
  for (int i = 0; i < NUM_SOUNDS; ++i) {
    if (sound_effects[i]) {
      Mix_FreeChunk(sound_effects[i]);
      sound_effects[i] = NULL;
    }
  }

  // Close SDL_mixer
  Mix_CloseAudio();
}
