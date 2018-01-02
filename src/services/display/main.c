#include <awoo/modifiers.h>

// Prints '?!?!?!' to the screen.
int main(UNUSED int argc, UNUSED char **argv)
{
    char *video = (char*)0xB8000;

    for (int i = 0; i < 12; i += 2) {
        video[i] = (i % 4 == 0) ? '!' : '?';
        video[i + 1] = 0x07;
    }

    return 0;
}
