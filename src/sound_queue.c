#include "sound_queue.h"

#include <SDL_mixer.h>
#include <stdbool.h>

#define SOUND_QUEUE_SIZE 32

// Sound queue
static SoundEnum soundQueue[SOUND_QUEUE_SIZE];
static int soundQueueCount = 0;

void init_sound_queue() { soundQueueCount = 0; }

void stage_sound(SoundEnum sound) {
  if (soundQueueCount < SOUND_QUEUE_SIZE) {
    soundQueue[soundQueueCount++] = sound;
  }
  // Optionally handle the case where the queue is full
}

void play_and_empty_queue() {
  for (int i = 0; i < soundQueueCount; ++i) {
    play_sound(soundQueue[i]);
  }
  soundQueueCount = 0;  // Reset the queue
}

void cleanup_sound_queue() {
  // No specific cleanup needed for the static queue
  // If dynamic memory were used, it would be freed here
}
