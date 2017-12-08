#include <string.h>
#include <stddef.h>

#include <kernel.h>
void *memset(void *s, int c, size_t n)
{
    int *cs = (int*)s;

    for (size_t i = 0; i < n; i++) {
        cs[i] = c;
    }

    return s;
}

char *strcpy(char *dest, const char *src)
{
    size_t len = strlen(src);
    for (size_t i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
    return dest;
}
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

char *strrev(char *str)
{
    size_t length = strlen(str);
    size_t half_length = length / 2;
    char tmp;

    for (size_t idx = 0; idx < half_length; idx++) {
        tmp = str[idx];
        str[idx] = str[length - idx - 1];
        str[length - idx - 1] = tmp;
    }

    return str;
}
