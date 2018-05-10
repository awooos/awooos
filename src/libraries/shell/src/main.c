#include <ali/event.h>
#include <ali/str.h>
#include <ali/text.h>
#include <keyboard.h>
#include <string.h>

// A 1KB buffer for command input should be enough.
// If it's not, please rethink some life choices.
// Or change this magic number. Either works.
#define SHELL_BUFFER_SIZE 1024

#define COMMAND(name) (strcmp(result->pieces[0], name) == 0)

void shell_print_prompt()
{
    print("# ");
}

void shell_run(char *buffer)
{
    ShellSplitResult *result = shellsplit(buffer);
    if (COMMAND("echo")) {
        for (size_t i = 0; i < result->num_pieces; i++) {
            print(result->pieces[i]);
            if (i < (result->num_pieces - 1)) {
                print(" ");
            } else {
                print("\n");
            }
        }
    } else {
        print("Error: Unkown command: ");
        println(result->pieces[0]);
    }
}

void shell_keyboard_callback(void *data)
{
    // Shell buffer + 1 for trailing NULL byte.
    static char buffer[SHELL_BUFFER_SIZE + 1] = {0,};
    static size_t idx = 0;

    KeyboardEvent *event = (KeyboardEvent*)data;

    if (event->c != '\0') {
        print(event->c);
    }

    if (event->c == '\n') {
        shell_run((char*)&buffer);
        memset(buffer, 0, SHELL_BUFFER_SIZE + 1);
        idx = 0;
    } else if (idx >= SHELL_BUFFER_SIZE) {
        // TODO: Show some sort of indication that there is a problem.
    } else {
        buffer[idx] = event->c;
        idx++;
    }
}

void shell_register_events()
{
    event_watch("keyboard event", shell_keyboard_callback);
}

void shell_init()
{
    shell_register_events();

    println("AwooOS Interactive Shell.");
    shell_print_prompt();
}
