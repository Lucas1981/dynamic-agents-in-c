#include "game.h"

#include <stdio.h>   // for printf, NULL
#include <stdlib.h>  // for exit, srand
#include <time.h>    // for time

#include "agent_pool.h"      // for init_agent_pool
#include "animations.h"      // for cleanup_animations, init_animations
#include "clock.h"           // for set_time
#include "frames.h"          // for cleanup_frames, init_frames
#include "global_state.h"    // for TITLE, get_global_game_state, set_game_s...
#include "graphics.h"        // for cleanup_graphics, init_graphics, render_...
#include "input.h"           // for get_key_state, get_quit, handle_inputs
#include "screens.h"         // for cleanup_screens, load_screens
#include "sound.h"           // for cleanup_sounds, init_sounds
#include "sound_queue.h"     // for cleanup_sound_queue, init_sound_queue
#include "state_handlers.h"  // for handle_dead_state, handle_finished_state
#include "user_interface.h"  // for cleanup_user_interface, initiate_user_in...

// Forward declarations
static void init_game(void);
static void cleanup_game(void);

void run_game(void) {
  KeyState* key_state = get_key_state();

  init_game();
  srand((unsigned int)time(NULL));

  while (!key_state->escape && !get_quit()) {
    set_time();
    handle_inputs();
    const GlobalGameState* global_game_state = get_global_game_state();
    switch (global_game_state->current_state) {
      case TITLE:
        handle_title_state();
        break;
      case READY:
        handle_ready_state();
        break;
      case PLAYING:
        handle_playing_state();
        break;
      case DEAD:
        handle_dead_state();
        break;
      case GAME_OVER:
        handle_game_over_state();
        break;
      case WON:
        handle_won_state();
        break;
      case FINISHED:
        handle_finished_state();
        break;
      default:
        break;
    }

    render_graphics();
    play_and_empty_queue();
  }

  cleanup_game();
  printf("Goodbye!\n");
}

static void init_game(void) {
  printf("Starting initiation.\n");
  // Initialization code here
  if (init_graphics(SCREEN_WIDTH, SCREEN_HEIGHT) != 0) {  // Window size 800x600
    exit(1);
  }
  printf("Graphics done.\n");
  init_frames();
  printf("Frames done.\n");
  init_animations();
  printf("Animations done.\n");
  init_sounds();
  printf("Sounds done.\n");
  init_sound_queue();
  printf("Sounds queue.\n");
  initiate_user_interface();
  printf("User interface done.\n");
  init_agent_pool();
  printf("Agent pool done.\n");
  load_screens();
  printf("Loading screens done.\n");
  set_game_state(TITLE);
  set_time();
  printf("Initiation complete.\n\n");
}

static void cleanup_game(void) {
  printf("Cleaning up...\n");
  // Cleanup code here, run in reverse order as initiation
  cleanup_screens();
  cleanup_user_interface();
  cleanup_sound_queue();
  cleanup_sounds();
  cleanup_animations();
  cleanup_frames();
  cleanup_graphics();
  printf("Cleanup done.\n");
}
