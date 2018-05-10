#ifndef ALI__ALI_STR_H
#define ALI__ALI_STR_H

typedef struct ShellSplitResult_s {
    char **pieces;
    size_t num_pieces;
} ShellSplitResult;

char **shellsplit(char *str);
ShellSplitResults *charsplit(char *str, char token);

#endif
