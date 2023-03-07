#include <stdlib.h>

#include "s21_sscanf.h"

specifiers itest_spec(char **c, bool *err) {
  specifiers p = {0};
  if (!*err) {
    *err = build_spec(&p, c);
  }
  return p;
}

int dispather(const char *str, char *format, va_list args) {
  int count = 0;
  bool err = FALSE;

  stac_list kwargs = {.str = (char *)str, .count = 0, .format = format};
  va_copy(kwargs.args, args);
  do {
    kwargs.spec_p = itest_spec(&kwargs.format, &err);
    kwargs = get_func(&kwargs.spec_p)(kwargs, &err);
    kwargs.count = kwargs.str - str;
    while (issep(*kwargs.str)) kwargs.str++;
    if (!(kwargs.spec_p.flag & STATIC || kwargs.spec_p.flag & WITH) && !err &&
        kwargs.spec_p.spec != '%' && kwargs.spec_p.spec != '\0' &&
        kwargs.spec_p.spec != 'n')
      count++;
  } while ((*kwargs.str && !err));
  va_end(kwargs.args);
  return count;
}

int s21_sscanf(const char *str, const char *format, ...) {
  int count_spec = 0;
  va_list args;
  if (*format == '\0' || *str == '\0') {
  } else {
    va_start(args, format);
    count_spec = dispather(str, (char *)format, args);
    va_end(args);
  }
  return count_spec;
}
