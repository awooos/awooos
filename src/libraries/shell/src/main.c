#include <ali/event.h>
#include <ali/str.h>
#include <ali/text.h>
#include <keyboard.h>
#include <stdlib.h>
#include <string.h>

#include <ali/number.h>

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
    print("\n");
    if (COMMAND("echo")) {
        for (size_t i = 1; i < result->num_pieces; i++) {
            print(result->pieces[i]);
            if (i < result->num_pieces) {
                print(" ");
            } else {
                print("\n");
            }
        }
    } else {
        print("Error: Unknown command: ");
        println(result->pieces[0]);
    }
}

void shell_keyboard_callback(void *data)
{
    // Shell buffer + 1 for trailing NULL byte.
    static char buf[SHELL_BUFFER_SIZE + 1] = {0,};
    static size_t idx = 0;
    static char *buffer = (char*)&buf;

    KeyboardEvent *event = (KeyboardEvent*)data;

    if (event->c == '\0') {
        // Not a printable character.
        return;
    }

    if ((event->c == '\n') && (idx == 0)) {
        // No command to run.
        print("\n");
        shell_print_prompt();
        return;
    }

    if (event->c == '\n') {
        // Try runing a command.
        shell_run(buffer);
        memset(buffer, 0, SHELL_BUFFER_SIZE);
        idx = 0;
        return;
    }

    if (!event->make) {
        // We don't need to care about break events.
        return;
    }

    if (idx >= SHELL_BUFFER_SIZE) {
        // Command too long for buffer.
        // TODO: Show some sort of indication that there is a problem.
        return;
    }

    // TODO: Don't hard-code the value for backspace.
    if (event->c == '\x08') {
        // Delete the last character.
        buffer[idx] = 0;
        if (idx > 0) {
            idx--;
        }

        // HACK: Oh my god this is a horrible way to clear the line.
        print("\r");
        for (int i = 0; i < 79; i++) { print(" "); }
        print("\r");
        shell_print_prompt();
        print(buffer);
    } else {
        // Store the character.
        buffer[idx] = event->c;
        idx++;
        print(buffer + idx - 1);
    }
}

__attribute__((constructor))
void shell_register_events()
{
    event_watch("keyboard event", shell_keyboard_callback);
}

void shell_init()
{
    println("AwooOS Interactive Shell.");
    shell_print_prompt();
}
