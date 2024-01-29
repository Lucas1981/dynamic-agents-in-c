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
  KeyState* keyState = get_key_state();

  init_game();
  srand((unsigned int)time(NULL));

  while (!keyState->escape && !get_quit()) {
    set_time();
    Uint32 now = get_now();
    handle_inputs();
    const GlobalGameState* globalGameState = getGlobalGameState();
    switch (globalGameState->currentState) {
      case TITLE:
        handleTitleState();
        break;
      case READY:
        handleReadyState();
        break;
      case PLAYING:
        handlePlayingState();
        break;
      case DEAD:
        handleDeadState();
        break;
      case GAME_OVER:
        handleGameOverState();
        break;
      case WON:
        handleWonState();
        break;
      case FINISHED:
        handleFinishedState();
        break;
      case PAUSE:
        handlePauseState();
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
  sheet = loadSpritesheet("./assets/images/spritesheet.png", renderer, 64, 64);
  printf("Spritesheet done.\n");
  initFrames(sheet);
  printf("Frames done.\n");
  initAnimations();
  printf("Animations done.\n");
  init_sounds();
  init_sound_queue();
  printf("Sound initiation done\n");
  initiate_user_interface();
  printf("User interface initiation done\n");
  initAgentPool();
  printf("Loading screens\n");
  load_screens();
  setGameState(TITLE);
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
  cleanupAnimations();
  cleanupFrames();
  freeSpritesheet(sheet);
  cleanup_graphics();
  printf("Cleanup done.\n");
}
