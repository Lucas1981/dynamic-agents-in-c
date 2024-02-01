#ifndef SOUND_QUEUE_H
#define SOUND_QUEUE_H

#include "sound.h"

void init_sound_queue(void);
void stage_sound(SoundEnum sound);
void play_and_empty_sound_queue(void);
void cleanup_sound_queue(void);

#endif  // SOUND_QUEUE_H
