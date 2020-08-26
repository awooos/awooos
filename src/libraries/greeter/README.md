# Greeter

AwooOS's Greeter library listens for the `"greeter display"` event,
expecting to get a `char**`, and prints each string.

## Usage

Simplified example, based on how awooOS' HAL uses it:

```c
char *os_name = "awooOS";

const char *greeting[] = {
    os_name,
    "\r\n",
    "Compiled with: ",
    &kernel_comment_start,
    NULL
};

event_trigger("greeter display", &greeting);
```
