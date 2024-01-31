#ifndef INPUT_H
#define INPUT_H

// Structure to hold key states
typedef struct {
  int left;
  int right;
  int space;
  int enter;
  int escape;
} KeyState;

KeyState *get_key_state(void);
void handle_inputs(void);
int get_quit(void);

#endif
