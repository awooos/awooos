# src/kernel

awooOS' `src/kernel` directory should exclusively include:

1. `0-start-*.asm` &mdash; platform-specific initialization code.
2. `main.c` &mdash; platform-agnostic initialization code, which is
   called by `0-start-*.asm`.

NOTE: `0-start-${TARGET}.asm` is prefixed with `0-` to guarantee it is
always the first linked item.
