#include "game.h"

#include "agent_pool.h"
#include "animations.h"
#include "clock.h"
#include "frames.h"
#include "global_state.h"
#include "graphics.h"
#include "input.h"
#include "load_spritesheet.h"
#include "screens.h"
#include "sound.h"
#include "sound_queue.h"
#include "state_handlers.h"
#include "user_interface.h"

// Variable to hold the current game state
static Spritesheet* sheet;

// Forward declarations
static void init_game();
static void cleanup_game();

void run_game() {
  KeyState* key_state = get_key_state();

  init_game();
  srand((unsigned int)time(NULL));

  while (!key_state->escape && !get_quit()) {
    set_time();
    Uint32 now = get_now();
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
      case PAUSE:
        handle_pause_state();
        break;
    }

    render_graphics();
    play_and_empty_queue();
  }

  cleanup_game();
  printf("Goodbye!\n");
}

static void init_game() {
  printf("Starting initiation.\n");
  // Initialization code here
  if (init_graphics(SCREEN_WIDTH, SCREEN_HEIGHT) != 0) {  // Window size 800x600
    exit(1);
  }
  printf("Graphics done.\n");
  SDL_Renderer* renderer = get_renderer();
  printf("Renderer done.\n");
  sheet = load_spritesheet("./assets/images/spritesheet.png", renderer, 64, 64);
  printf("Spritesheet done.\n");
  init_frames(sheet);
  printf("Frames done.\n");
  init_animations();
  printf("Animations done.\n");
  init_sounds();
  init_sound_queue();
  printf("Sound initiation done\n");
  initiate_user_interface();
  printf("User interface initiation done\n");
  init_agent_pool();
  printf("Loading screens\n");
  load_screens();
  set_game_state(TITLE);
  set_time();
  printf("Initiation complete.\n\n");
}

static void cleanup_game() {
  printf("Cleaning up...\n");
  // Cleanup code here, run in reverse order as initiation
  cleanup_screens();
  cleanup_user_interface();
  cleanup_sound_queue();
  cleanup_sounds();
  cleanup_animations();
  cleanup_frames();
  free_spritesheet(sheet);
  cleanup_graphics();
  printf("Cleanup done.\n");
}
