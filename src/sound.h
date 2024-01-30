#ifndef SOUND_H
#define SOUND_H

typedef enum {
  SCREAM,
  GUNSHOT,
  NUM_SOUNDS  // Keep this as the last element to count the number of sounds
} SoundEnum;

void init_sounds(void);
void play_sound(SoundEnum sound);
void cleanup_sounds(void);

#endif  // SOUND_H
