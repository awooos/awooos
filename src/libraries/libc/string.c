#include <string.h>
#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
    char *cs = (char*)s;

    for (size_t i = 0; i < n; i++) {
        cs[i] = 0;
    }

    return s;
}

// char *strcpy(char *dest, const char *src);
// char *strncpy(char *dest, const char *src, size_t n);

// char *strcat(char *dest, const char *src);
// char *strncat(char *dest, const char *src, size_t n);

int strcmp(const char *s1, const char *s2)
{
    size_t s1_len = strlen(s1),
           s2_len = strlen(s2),
           length = (s1_len > s2_len) ? s1_len : s2_len;

    return strncmp(s1, s2, length);
}


int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;

    while (i < n && s1[i] && s2[i]){
        if (s1[i] > s2[i]) {
            return s1[i] - s2[i];
        }
        if (s1[i] < s2[i]) {
            return s2[i] - s1[i];
        }

        i += 1;
    }

    return 0;
}

// char *strchr(const char *s, int c);
// char *strrchr(const char *s, int c);


size_t strlen(const char *str)
{
    char *str_ = (char*)str;
    size_t i = 0;

    // Increment `i` until `str_[i]` is a null byte.
    while(str_[i] != '\0') {
        i++;
    }

    return i;
}
