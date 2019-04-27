/* str.h: string utilities library */

#pragma once

#include <stdbool.h>
#include <stdlib.h>

/* Case */
char *  str_lower(char *s);
char *  str_upper(char *s);

/* Strip */
char *  str_chomp(char *s);
char *  str_strip(char *s);

/* Reverse */
char *  str_reverse(char *s);

/* Translation */
char * str_translate(char *s, char *from, char *to);

/* Integer Conversion */
int str_to_int(const char *s, int base);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
