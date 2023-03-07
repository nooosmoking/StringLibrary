#include "s21_sscanf.h"

stac_list spec_d(stac_list kwargs, bool *err) {
  int positive = 0;
  long int value = 0;
  if (*kwargs.str == '-') {
    positive = -1;
    kwargs.str++;
    kwargs.spec_p.with--;
  } else if (*kwargs.str == '+') {
    positive = 1;
    kwargs.str++;
    kwargs.spec_p.with--;
  } else {
    positive = 1;
  }

  if (isdigit(*kwargs.str)) {
    do {
      value = (value * 10) + (*kwargs.str - '0');
      kwargs.str++;
      kwargs.spec_p.with--;
    } while (isdigit(*kwargs.str) && kwargs.spec_p.with != 0);

    value = positive * value;

    if (!(kwargs.spec_p.flag & WITH)) {
      switch (kwargs.spec_p.len) {
        case 'l':
          *va_arg(kwargs.args, long int *) = value;
          break;
        case 'h':
          *va_arg(kwargs.args, short int *) = (short int)value;
          break;
        default:
          *va_arg(kwargs.args, int *) = (int)value;
          break;
      }
    }
  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}

stac_list spec_i(stac_list kwargs, bool *err) {
  int positive = 1;
  int digit_flag = 0;
  long int value = 0;
  int digit = 0;
  int len = 0;
  if (*kwargs.str == '-') {
    positive = -1;
    kwargs.str++;
    digit_flag++;
  } else if (*kwargs.str == '+') {
    kwargs.str++;
    digit_flag++;
  }
  if (*kwargs.str == '0' && kwargs.str[1] != ' ') {
    kwargs.str++;
    if (*kwargs.str == 'x') {
      kwargs.str++;
      if (isdigit(*kwargs.str) || (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
          (*kwargs.str >= 'a' && *kwargs.str <= 'f') || *kwargs.str == '+' ||
          (*kwargs.str == '0' && *(kwargs.str + 1) == 'x')) {
        if (kwargs.spec_p.with == 0)
          kwargs.spec_p.with = -1;
        else
          kwargs.spec_p.with -= 3;
        len = len_hex(kwargs.str, kwargs.spec_p.with) - 1;
        do {
          digit = 0;
          if (isdigit(*kwargs.str))
            digit = *kwargs.str - '0';
          else if (*kwargs.str >= 'A' && *kwargs.str <= 'F')
            digit = *kwargs.str - 55;
          else if (*kwargs.str >= 'a' && *kwargs.str <= 'f')
            digit = *kwargs.str - 87;
          value = value + digit * pow(16, len);
          len--;
          kwargs.str++;
          kwargs.spec_p.with--;
        } while ((isdigit(*kwargs.str) ||
                  (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
                  (*kwargs.str >= 'a' && *kwargs.str <= 'f') ||
                  *kwargs.str == '+' ||
                  (*kwargs.str == '0' && *(kwargs.str + 1) == 'x')) &&
                 kwargs.spec_p.with != 0);

        if (!(kwargs.spec_p.flag & WITH)) {
          switch (kwargs.spec_p.len) {
            case 'l':
              *va_arg(kwargs.args, long int *) = value * positive;
              break;
            case 'h':
              *va_arg(kwargs.args, short int *) = (short int)value * positive;
              break;
            default:
              *va_arg(kwargs.args, int *) = (int)value * positive;
              break;
          }
        }
      } else {
        *va_arg(kwargs.args, int *) = 0;
      }
    } else if (isdigit(*kwargs.str)) {
      if (kwargs.spec_p.with == 0)
        kwargs.spec_p.with = -1;
      else
        kwargs.spec_p.with -= 1;
      do {
        value = (value * 8) + (*kwargs.str - '0');
        kwargs.str++;
        kwargs.spec_p.with--;
      } while (isdigit(*kwargs.str) && kwargs.spec_p.with != 0 &&
               *kwargs.str < '8');

      if (!(kwargs.spec_p.flag & WITH)) {
        switch (kwargs.spec_p.len) {
          case 'l':
            *va_arg(kwargs.args, long int *) = value * positive;
            break;
          case 'h':
            *va_arg(kwargs.args, short int *) = (short int)(value * positive);
            break;
          default:
            *va_arg(kwargs.args, int *) = (int)(value * positive);
            break;
        }
      }
    } else {
      kwargs = spec_d(kwargs, err);
    }
  } else if (isdigit(*kwargs.str)) {
    if (digit_flag) kwargs.str--;
    return spec_d(kwargs, err);
  } else
    *err = STOP_ITER;
  return kwargs;
}

stac_list spec_p(stac_list kwargs, bool *err) {
  long int value = 0;
  int positive = 1;
  int len = 0;
  int digit = 0;
  if (*kwargs.str == '-') {
    positive = -1;
    kwargs.str++;
    kwargs.spec_p.with--;
  }
  if (*kwargs.str == '+') {
    kwargs.str++;
    kwargs.spec_p.with--;
  }
  if (*kwargs.str == '0' && *(kwargs.str + 1) == 'x') {
    kwargs.str += 2;
    if (*kwargs.str == ' ') *va_arg(kwargs.args, long int *) = value;
  }
  if (isdigit(*kwargs.str) || (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
      (*kwargs.str >= 'a' && *kwargs.str <= 'f')) {
    if (kwargs.spec_p.with == 0) kwargs.spec_p.with = -1;
    len = len_hex(kwargs.str, kwargs.spec_p.with) - 1;
    do {
      digit = 0;
      if (isdigit(*kwargs.str))
        digit = *kwargs.str - '0';
      else if (*kwargs.str >= 'A' && *kwargs.str <= 'F')
        digit = *kwargs.str - 55;
      else if (*kwargs.str >= 'a' && *kwargs.str <= 'f')
        digit = *kwargs.str - 87;
      value = value + digit * pow(16, len);
      len--;
      kwargs.str++;
      kwargs.spec_p.with--;
    } while ((isdigit(*kwargs.str) ||
              (*kwargs.str >= 'A' && *kwargs.str <= 'F') ||
              (*kwargs.str >= 'a' && *kwargs.str <= 'f')) &&
             kwargs.spec_p.with != 0);

    if (!(kwargs.spec_p.flag & WITH)) {
      *va_arg(kwargs.args, long int *) = value * positive;
    }
  } else if (!issep(*kwargs.str))
    *err = STOP_ITER;
  return kwargs;
}
