#include "sound_queue.h"

#define SOUND_QUEUE_SIZE 32

// Sound queue
static SoundEnum sound_queue[SOUND_QUEUE_SIZE];
static int sound_queue_count = 0;

void init_sound_queue(void) { sound_queue_count = 0; }

void stage_sound(SoundEnum sound) {
  if (sound_queue_count < SOUND_QUEUE_SIZE) {
    sound_queue[sound_queue_count++] = sound;
  }
  // Optionally handle the case where the queue is full
}

void play_and_empty_sound_queue(void) {
  for (int i = 0; i < sound_queue_count; ++i) {
    play_sound(sound_queue[i]);
  }
  sound_queue_count = 0;  // Reset the queue
}

void cleanup_sound_queue(void) {
  // No specific cleanup needed for the static queue
  // If dynamic memory were used, it would be freed here
}
