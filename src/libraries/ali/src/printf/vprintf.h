#ifndef ALI_VPRINTF_H
#define ALI_VPRINTF_H

typedef struct VprintFlags_s {
    char left_justified;
    char always_show_sign;
    char space_if_positive; // mutually exclusive with flag_always_show_sign
    char alt_form;
    char leading_zeros;
} VprintFlags;

typedef struct VprintLengthModifier_s {
    char hh;
    char h;
    char l;
    char ll;
    char j;
    char z;
    char t;
    char L;
} VprintLengthModifier;

typedef struct VprintConversionSpecifier_s {
    char d; char i;
    char o;
    char u;
    char x;
    char X;
    char f; char F;
    char e; char E;
    char g; char G;
    char a; char A;
    char c;
    char s;
    char p;
    char n;
    char C;
    char S;
    char percent;
} VprintConversionSpecifier;

#endif
