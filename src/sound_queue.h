#ifndef SOUND_QUEUE_H
#define SOUND_QUEUE_H

#include "sound.h"

// Function to initialize the sound queue
void init_sound_queue();

// Function to stage a sound in the queue
void stage_sound(SoundEnum sound);

// Function to play all staged sounds and empty the queue
void play_and_empty_queue();

// Function to cleanup the sound queue
void cleanup_sound_queue();

#endif // SOUND_QUEUE_H
