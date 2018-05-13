#include <ali/event.h>
#include "hal_keyboard.h"
#include "keysym_us.h"
#include "ports.h"
#include <stdlib.h>
#include <string.h>

#define IS_BREAK(x) (scancode & 0x80)
#define IS_MAKE(x)  (!IS_BREAK(x))

#define MAKE(x)  (scancode == x)
#define BREAK(x) (scancode == (x + 0x80))

#define SCANCODE(x) (MAKE(x) || BREAK(x))

#define ACTIVE(key, scancode) (MAKE(scancode) || (state->key && (!BREAK(scancode))))

static bool keyboard_initialized = false;
static KeyboardEvent *state = NULL;

void hal_keyboard_init()
{
    state = malloc(sizeof(KeyboardEvent));
    memset(state, 0, sizeof(KeyboardEvent));
    keyboard_initialized = true;
}

char hal_keyboard_resolve_scancode(char keysym[128], uint32_t scancode)
{
    return keysym[scancode & 0x7F];
}

void hal_keyboard_callback(void *data)
{
    if (!keyboard_initialized) {
        hal_keyboard_init();
    }

    uint32_t scancode = hal_inb(0x60);

    KeyboardEvent *event = malloc(sizeof(KeyboardEvent));
    memset(event, 0, sizeof(KeyboardEvent));

    event->Esc      = ACTIVE(Esc,   0x01);
    event->CtrlL    = ACTIVE(CtrlL, 0x1D);
    event->CtrlR    = false; //ACTIVE(CtrlR, ); // TODO: Add CtrlR support.
    event->AltL     = ACTIVE(AltL,  0x38);
    event->AltR     = false; //ACTIVE(AltR, );  // TODO: Add AltR support.
    event->GuiL     = false; //ACTIVE(GuiL, );  // TODO: Add GuiL support.
    event->GuiR     = false; //ACTIVE(GuiR, );  // TODO: Add GuiR support.
    event->ShiftL   = ACTIVE(ShiftL,    0x2A);
    event->ShiftR   = ACTIVE(ShiftR,    0x36);
    event->NumLock  = ACTIVE(NumLock,   0x45);
    event->CapsLock = ACTIVE(CapsLock,  0x3A);
    event->ScrollLock = ACTIVE(ScrollLock, 0x46);

    if (event->CapsLock) {
        state->CapsLock = !(state->CapsLock);
    }

    if (event->ShiftL || event->ShiftR) {
        event->c = hal_keyboard_resolve_scancode(keysym_us_shift, scancode);
    } else {
        event->c = hal_keyboard_resolve_scancode(keysym_us, scancode);
    }

    event->make = IS_MAKE(event->c);

    event_trigger("keyboard event", event, 0);
    free(event);
}
