#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

typedef enum {
  TEXT_ALIGN_LEFT,
  TEXT_ALIGN_CENTER,
  TEXT_ALIGN_RIGHT
} TextAlignment;

void initiate_user_interface(void);
void print_user_interface_with_outline(const char* string, int x, int y,
                                       TextAlignment horizontal_text_alignment);
void print_user_interface(const char* string, int x, int y,
                          TextAlignment horizontal_text_alignment);
void cleanup_user_interface(void);

#endif  // USER_INTERFACE_H
