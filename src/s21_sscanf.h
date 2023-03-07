#ifndef _S21_SSCANF_H_
#define _S21_SSCANF_H_
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

#define TRUE 1
#define FALSE 0

#define INIT (1 << 0)
#define STATIC (1 << 1)
#define WITH (1 << 2)

#define STATIC_C '-'
#define DEBUG TRUE
#define STOP_ITER 12

#define isdigit(c) ((unsigned)((c) - '0') < 10U)
#define islen(c) (c == 'h' || c == 'l' || c == 'L')
#define issep(c) (c == ' ' || c == '\n' || c == '\t')
#define issep_w(c) (c == L' ' || c == L'\n' || c == L'\t')

#define isspec(c)                                                          \
  (c == 'c' || c == 'd' || c == 'i' || c == 'e' || c == 'E' || c == 'f' || \
   c == 'g' || c == 'G' || c == 'o' || c == 's' || c == 'u' || c == 'x' || \
   c == 'X' || c == 'p' || c == 'n' || c == '%')

typedef unsigned short bool;

//%[*][ширина][длина]spec
typedef struct str_specifiers {
  bool flag;
  int with;
  char len;
  char spec;
} specifiers;

// Struct kwargs
typedef struct {
  int count;
  char *str;
  char *format;
  specifiers spec_p;
  va_list args;
} stac_list;

// func wrapper
typedef stac_list (*TWrapper)(stac_list, bool *);

// spec.c
// Convert  format to specifiers array.
bool build_spec(specifiers *p, char **orig_format);

// Mapping params and args
bool map_args(specifiers *p, va_list args);
void print_list_sep(specifiers *p);

int len_hex(char *str, int width);
// formater.c
// Return func via spec
TWrapper get_func(specifiers *spec);

// sscanf.c
// Return func via spec
int s21_sscanf(const char *str, const char *format, ...);

// symbol
stac_list static_f(stac_list kwargs, bool *err);
stac_list spec__(stac_list kwargs, bool *err);
stac_list spec_n(stac_list kwargs, bool *err);
stac_list spec_c(stac_list kwargs, bool *err);
stac_list spec_s(stac_list kwargs, bool *err);

// decimal
stac_list spec_d(stac_list kwargs, bool *err);
stac_list spec_i(stac_list kwargs, bool *err);
stac_list spec_p(stac_list kwargs, bool *err);

// floating
stac_list spec_f(stac_list kwargs, bool *err);
stac_list spec_e(stac_list kwargs, bool *err);
stac_list spec_E(stac_list kwargs, bool *err);
stac_list spec_g(stac_list kwargs, bool *err);
stac_list spec_G(stac_list kwargs, bool *err);

// unsignet
stac_list spec_o(stac_list kwargs, bool *err);
stac_list spec_u(stac_list kwargs, bool *err);
stac_list spec_x(stac_list kwargs, bool *err);
stac_list spec_X(stac_list kwargs, bool *err);
#endif