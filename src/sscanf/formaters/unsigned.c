#include "s21_sscanf.h"

stac_list spec_o(stac_list kwargs, bool *err) {
  unsigned long int value = 0;
  if (*kwargs.str == '-') {
    do {
      kwargs.str++;
    } while (*kwargs.str != 0 && *kwargs.str != ' ');
    *va_arg(kwargs.args, unsigned long int *) = value;
  } else if ((isdigit(*kwargs.str) && *kwargs.str < '8') ||
             (*kwargs.str == '+' &&
              (isdigit(kwargs.str[1]) && kwargs.str[1] < '8')) ||
             *kwargs.str == '0') {
    if (*kwargs.str == '+') {
      kwargs.str++;
      kwargs.spec_p.with--;
    }
    if (*kwargs.str == '0') kwargs.str++;
    if (kwargs.spec_p.with == 0) kwargs.spec_p.with = -1;
    while (isdigit(*kwargs.str) && kwargs.spec_p.with != 0 &&
           *kwargs.str < '8') {
      value = (value * 8) + (*kwargs.str - '0');
      kwargs.str++;
      kwargs.spec_p.with--;
    }
    if (!(kwargs.spec_p.flag & WITH)) {
      switch (kwargs.spec_p.len) {
        case 'l':
          *va_arg(kwargs.args, unsigned long int *) = value;
          break;
        case 'h':
          *va_arg(kwargs.args, unsigned short int *) =
              (unsigned short int)value;
          break;
        default:
          *va_arg(kwargs.args, unsigned int *) = (unsigned int)value;
          break;
      }
    }
  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}

stac_list spec_u(stac_list kwargs, bool *err) {
  unsigned long int value = 0;
  if (*kwargs.str == '-') {
    do {
      kwargs.str++;
    } while (*kwargs.str != 0 && *kwargs.str != ' ');
    *va_arg(kwargs.args, unsigned long int *) = value;
  } else if (isdigit(*kwargs.str) ||
             (*kwargs.str == '+' && isdigit(kwargs.str[1]))) {
    if (*kwargs.str == '+') {
      kwargs.str++;
      kwargs.spec_p.with--;
    }
    if (kwargs.spec_p.with == 0) kwargs.spec_p.with = -1;
    do {
      value = (value * 10) + (*kwargs.str - '0');
      kwargs.str++;
      kwargs.spec_p.with--;
    } while (isdigit(*kwargs.str) && kwargs.spec_p.with != 0);

    if (!(kwargs.spec_p.flag & WITH)) {
      switch (kwargs.spec_p.len) {
        case 'l':
          *va_arg(kwargs.args, unsigned long int *) = value;
          break;
        case 'h':
          *va_arg(kwargs.args, unsigned short int *) =
              (unsigned short int)value;
          break;
        default:
          *va_arg(kwargs.args, unsigned int *) = (unsigned int)value;
          break;
      }
    }
  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}

stac_list spec_x(stac_list kwargs, bool *err) {
  unsigned long int value = 0;
  if (*kwargs.str == '-') {
    do {
      kwargs.str++;
    } while (*kwargs.str != 0 && *kwargs.str != ' ');
    *va_arg(kwargs.args, unsigned long int *) = value;
  } else if (isdigit(*kwargs.str) ||
             (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
             (*kwargs.str >= 'a' && *kwargs.str <= 'f') ||
             ((*kwargs.str == '+' && isdigit(kwargs.str[1])) ||
              (kwargs.str[1] >= 'A' && kwargs.str[1] <= 'F') ||
              (kwargs.str[1] >= 'a' && kwargs.str[1] <= 'f')) ||
             (*kwargs.str == '0' && *(kwargs.str + 1) == 'x')) {
    if (*kwargs.str == '+') {
      kwargs.str++;
      kwargs.spec_p.with--;
    }
    if (*kwargs.str == '0' && *(kwargs.str + 1) == 'x') kwargs.str += 2;
    if (kwargs.spec_p.with == 0) kwargs.spec_p.with = -1;
    int len = len_hex(kwargs.str, kwargs.spec_p.with) - 1;
    do {
      int digit = -1;
      if (isdigit(*kwargs.str))
        digit = *kwargs.str - '0';
      else if (*kwargs.str >= 'A' && *kwargs.str <= 'F')
        digit = *kwargs.str - 55;
      else if (*kwargs.str >= 'a' && *kwargs.str <= 'f')
        digit = *kwargs.str - 87;
      if (digit != (-1)) value = value + digit * pow(16, len);
      len--;
      kwargs.str++;
      kwargs.spec_p.with--;
    } while ((isdigit(*kwargs.str) ||
              (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
              (*kwargs.str >= 'a' && *kwargs.str <= 'f')) &&
             kwargs.spec_p.with != 0);
    if (!(kwargs.spec_p.flag & WITH)) {
      switch (kwargs.spec_p.len) {
        case 'l':
          *va_arg(kwargs.args, unsigned long int *) = value;
          break;
        case 'h':
          *va_arg(kwargs.args, unsigned short int *) =
              (unsigned short int)value;
          break;
        default:
          *va_arg(kwargs.args, unsigned int *) = (unsigned int)value;
          break;
      }
    }
  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}
