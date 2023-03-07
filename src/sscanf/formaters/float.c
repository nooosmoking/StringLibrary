#include "s21_sscanf.h"

stac_list spec_f(stac_list kwargs, bool *err) {
  long double value = 0;
  int digit = 0;
  int positive = 0;
  int size = -1;
  int power = 0;
  if (*kwargs.str == '-') {
    positive = -1;
    kwargs.str++;
    kwargs.spec_p.with--;
  } else if (*kwargs.str == '+') {
    positive = 1;
    kwargs.str++;
    kwargs.spec_p.with--;
  } else
    positive = 1;

  if (isdigit(*kwargs.str)) {
    for (; isdigit(*kwargs.str) && kwargs.spec_p.with != 0;
         kwargs.str++, kwargs.spec_p.with--) {
      digit = *kwargs.str - '0';
      value = (10 * value) + (double)digit;
    }

    if ((*kwargs.str == '.' || *kwargs.str == ',') && kwargs.spec_p.with != 0) {
      kwargs.str++;
      kwargs.spec_p.with--;
    }
    for (; isdigit(*kwargs.str) && kwargs.spec_p.with != 0;
         kwargs.str++, kwargs.spec_p.with--) {
      digit = *kwargs.str - '0';
      value += powl(10, size) * digit;
      size--;
    }
    if (*kwargs.str == 'e') {
      kwargs.str++;
      kwargs.spec_p.with--;
      for (; isdigit(*kwargs.str) && kwargs.spec_p.with != 0;
           kwargs.str++, kwargs.spec_p.with--) {
        digit = *kwargs.str - '0';
        power = (10 * power) + digit;
        size--;
      }
    }
    if (!(kwargs.spec_p.flag & WITH)) {
      switch (kwargs.spec_p.len) {
        case 'L':
          *va_arg(kwargs.args, long double *) =
              powl(10., (long double)power) * positive * value;
          break;
        default:
          *va_arg(kwargs.args, float *) =
              powf(10., (float)power) * positive * (float)value;
          break;
      }
    }

  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}

stac_list spec_e(stac_list kwargs, bool *err) { return spec_f(kwargs, err); }
stac_list spec_E(stac_list kwargs, bool *err) { return spec_f(kwargs, err); }
stac_list spec_g(stac_list kwargs, bool *err) { return spec_f(kwargs, err); }
stac_list spec_G(stac_list kwargs, bool *err) { return spec_f(kwargs, err); }
