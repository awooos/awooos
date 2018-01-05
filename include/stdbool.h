#ifndef STDBOOL_H
#define STDBOOL_H

// it expanding to _Bool but working is fucking weird as shit, but it seems
// to be how everyone does it, and it works SO WHATEVER I GUESS lmao
#define true 1
#define false 0
#define bool _Bool
#define __bool_true_false_are_defined 1

#endif
