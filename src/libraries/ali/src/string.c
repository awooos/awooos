#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *udest = (uint8_t*)dest;
    uint8_t *usrc = (uint8_t*)src;

    for (size_t i = 0; i < n; i++) {
        udest[i] = usrc[i];
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t tmp[n];
    memcpy(&tmp, src, n);
    memcpy(dest, &tmp, n);

    return dest;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char *buf = (unsigned char*)s;

    for (size_t i = 0; i < n; i++) {
        buf[i] = (unsigned char)c;
    }

    return s;
}

void *memchr(const void *s, int c, size_t n)
{
    unsigned char *buf = (unsigned char*)s;
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == c) {
            return (void*)(buf + i);
        }
    }

    return NULL;
}

char *strcpy(char *dest, const char *src)
{
    return strncpy(dest, src, strlen(src));
}

char *strncpy(char *dest, const char *src, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (src[i]) {
            dest[i] = src[i];
        }
    }

    return dest;
}

// char *strcat(char *dest, const char *src);
// char *strncat(char *dest, const char *src, size_t n);

int memcmp(const void *s1, const void *s2, size_t n)
{
    return strncmp((const char*)s1, (const char*)s2, n);
}

int strcmp(const char *s1, const char *s2)
{
    size_t s1_len = strlen(s1),
           s2_len = strlen(s2),
           length = (s1_len > s2_len) ? s1_len : s2_len;

    return strncmp(s1, s2, length);
}


int strncmp(const char *s1, const char *s2, size_t n)
{
    const char *a = s1;
    const char *b = s2;

    while ( n && *a && (*a == *b) ) {
        ++a;
        ++b;
        --n;
    }

    if (n == 0) {
        return 0;
    } else {
        return *a - *b;
    }
}

// char *strchr(const char *s, int c);
// char *strrchr(const char *s, int c);

char *strdup(const char *str)
{
    return strndup(str, strlen(str));
}

char *strndup(const char *str, size_t n)
{
    char *duplicate = malloc(strlen(str) + 1);
    if (!duplicate) {
        return NULL;
    }
    strncpy(duplicate, str, n);
    duplicate[n] = 0;
    return duplicate;
}

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

size_t strnlen(const char *str, size_t maxlen)
{
    // Find the first instance of a null byte within maxlen bytes, if it exists.
    char *found = memchr(str, '\0', maxlen);
    if (found) {
        // If one was found, subtractiong the pointers gives us the length.
        return (size_t)(found - str);
    } else {
        // If one was not found, strnlen is capped at maxlen.
        return maxlen;
    }
}

char *strrev(char *str)
{
    size_t length = strlen(str);
    size_t half_length = length / 2;

    for (size_t idx = 0; idx < half_length; idx++) {
        char tmp = str[idx];
        str[idx] = str[length - idx - 1];
        str[length - idx - 1] = tmp;
    }

    return str;
}
