#ifndef KEYBOARD_H
#define KEYBOARD_H

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
    bool make;
} KeyboardEvent;

#endif
