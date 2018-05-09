#ifndef HAL__KEYBOARD_H
#define HAL__KEYBOARD_H

#include <stdbool.h>

typedef struct KeyboardEvent_s {
    bool Esc,
         CtrlL,
         CtrlR,
         AltL,
         AltR,
         GuiL,
         GuiR,
         ShiftL,
         ShiftR,
         NumLock,
         CapsLock,
         ScrollLock;
    bool F[25];
    char c;
} KeyboardEvent;

void keyboard_callback(void *data);

#endif
