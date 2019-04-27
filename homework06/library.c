/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char * str_lower(char * s) {
    for (char * c = s; *c; c++)
        *c = tolower(*c);
    return s;
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char * str_upper(char * s) {
    for (char * c = s; *c; c++)
        *c = toupper(*c);
    return s;
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char * str_chomp(char * s) {
    if ( *(s + strlen(s) - 1) == '\n' ) *(s + strlen(s) - 1) = 0;
    return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char * str_strip(char *s) {
    char * f = s;
    char * r = s + strlen(s) - 1;
    while ( isspace(*f)  && f < r) {
        *f = 0;
        s++;
        f++;
    }
    while ( isspace(*r) && r >= f) {
        *r = 0;
        r--;
    }
    return s;
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 * @return          Pointer to beginning of modified string
 **/
char * str_reverse(char *s) {
    char * f = s;
    char * r = s + strlen(s) - 1;
    char temp = 0;
    while (f < r) {
        temp = *f;
        *f = *r;
        *r = temp;
        f++;
        r--;
    }
    return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 * @return          Pointer to beginning of modified string
 **/
char * str_translate(char * s, char * from, char * to) {
    char table[256] = {0};
    if (strlen(from) != strlen(to)) return s;
    for (char * c = from; *c; c++)
        table[(int)*c] = (*(to + (int)(c - from)));
    for (char * c = s; *c; c++) {
        if (table[(int)(*c)] != 0)
            *c = table[(int)*c];
    }
    return s;
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int str_to_int(const char * s, int base) {
    int number = 0;
    int multiple = 1;
    int input = 0;
    for (const char * c = s; *c; c++) {
        multiple = 1;
        if ((int)(tolower(*c)) > 57) {
            input = (int)(tolower(*c)) - 87;
        } else {
            input = (int)*c - 48;
        }
        for (int i = 0; i < (int)(s + strlen(s) - c - 1); i++)
            multiple *= base;
        number += input * multiple;
    }
    return number;
}

//  vim: set sts=4 sw=4 ts=8 expandtab ft=c:
