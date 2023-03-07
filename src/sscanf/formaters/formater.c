#include "s21_sscanf.h"
typedef struct {
  const char c;
  TWrapper fun;
} reg_point;

TWrapper get_func(specifiers *spec) {
  static reg_point reg[] = {
      {'c', &spec_c}, {'d', &spec_d},        {'i', &spec_i}, {'e', &spec_e},
      {'E', &spec_E}, {'f', &spec_f},        {'g', &spec_g}, {'G', &spec_G},
      {'o', &spec_o}, {'s', &spec_s},        {'u', &spec_u}, {'x', &spec_x},
      {'u', &spec_u}, {'X', &spec_x},        {'p', &spec_p}, {'n', &spec_n},
      {'%', &spec__}, {STATIC_C, &static_f}, {'\0', 0}};
  reg_point *p = reg;
  TWrapper func = s21_NULL;
  if (spec->flag & STATIC)
    func = &static_f;
  else {
    while (p[1].c != '\0' && p->c != spec->spec) p++;
    func = p->fun;
  }
  return func;
}
