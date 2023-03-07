#include "s21_sscanf.h"

void init_spec(specifiers *p) {
  p->flag = 0;
  p->spec = '\0';
  p->len = '\0';
  p->with = -1;
}

long int spec_construct(specifiers *p, const char *format) {
  char *start = (char *)format;
  int value = 0;
  if ('*' == *format) {
    p->flag |= WITH;
    format++;
  }
  if (isdigit(*format)) {
    p->with = 0;
    while (isdigit(*format)) {
      value = (value * 10) + (*format - '0');
      p->with = value;
      format++;
    }
  }

  if (islen(*format)) {
    p->len = *format;
    format++;
  }

  if (isspec(*format)) {
    p->spec = *format;
    format++;
  }

  return format - start;
}

bool build_spec(specifiers *p, char **orig_format) {
  bool err = FALSE;
  int shift = 0;
  char *format = *orig_format;
  init_spec(p);

  while (issep(*format) && *format) format++;

  if (format[0] && format[1]) {
    if (*format == '%') {
      format++;
      shift = spec_construct(p, format);
      if (shift < 0) {
        err = TRUE;
      } else {
        format += shift;
        p->flag |= INIT;
      }
    } else {
      p->flag = INIT | STATIC;
      p->spec = *format;
      format++;
    }
  }
  *orig_format = format;
  return err;
}
