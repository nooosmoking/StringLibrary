#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  if (str) str[0] = '\0';
  int total = 0;
  if (str == s21_NULL) {
    total = 0;
  } else {
    va_list args;
    va_start(args, format);
    total = s21_handleParams(str, format, args);
    va_end(args);
  }
  return total;
}
int s21_handleParams(char *str, const char *format, va_list args) {
  int total = 0, i = 0, flag = 1;
  while (format[i] != '\0' && flag) {
    i = s21_convertStr(str, format, args, &flag, &total, i);
  }
  return total;
}

int s21_convertStr(char *str, const char *format, va_list args, int *flag,
                   int *total, int i) {
  s21_flags flags = {0};
  if (format[i] == '%') {
    i = s21_findFlags(&flags, format, i);
    if (format[i + 1] != ' ' && format[i + 1] != 0) {
      i++;
      *total = s21_calcChar(str, format, &i, args, *total, flags);
      i += 1;
    } else {
      *flag = 0;
    }
  } else {
    *total = s21_putChar(str, format[i], *total);
    i++;
  }
  s21_resetFlags(&flags);
  return i;
}

int s21_findFlags(s21_flags *flags, const char *format, int i) {
  while (s21_strchr("-+ #0", format[i + 1])) {
    s21_initFlags(format[i + 1], flags);
    i++;
  }
  return i;
}

int s21_calcChar(char *str, const char *format, int *i, va_list args, int total,
                 s21_flags flags) {
  flags.accuracy = -1;
  s21_findWidth(format, args, &flags, i);
  s21_findAccuracy(format, args, &flags, i);
  s21_findLength(format, &flags, i);
  if (flags.accuracy == -1) {
    s21_setDefAccuracy(&flags, format[*i]);
  }
  if (flags.space && !s21_strchr("goxXucfes", format[*i])) {
    total = s21_putChar(str, ' ', total);
  }
  total = s21_handleSpecs(str, format, args, &flags, total, i);
  return total;
}

void s21_findWidth(const char *format, va_list args, s21_flags *flags, int *i) {
  if (format[*i] != '.' && s21_strchr("0123456789*", format[*i])) {
    if (format[*i] == '*') {
      flags->width = va_arg(args, int);
      (*i)++;
    } else {
      flags->width = s21_atoib(format + *i, 10);
      (*i) += s21_intLen(flags->width, 10);
    }
  }
}

void s21_findAccuracy(const char *format, va_list args, s21_flags *flags,
                      int *i) {
  if (format[*i] == '.') {
    if (s21_strchr("*0123456789", format[*i + 1])) {
      (*i) += 1;
      if (format[*i] == '*') {
        flags->accuracy = va_arg(args, int);
      } else {
        flags->accuracy = s21_atoib(format + *i, 10);
        (*i) += s21_intLen(flags->accuracy, 10);
      }
    } else {
      flags->accuracy = 0;
    }
  }
  while (!s21_strchr("llLhcdieEfgGosuxXpn%", format[*i])) (*i)++;
}

void s21_findLength(const char *format, s21_flags *flags, int *i) {
  while (s21_strchr("lLh", format[*i])) {
    switch (format[*i]) {
      case 'h':
        flags->h += 1;
        break;
      case 'l':
        flags->l += 1;
        break;
      case 'L':
        flags->L += 1;
        break;
      default:
        break;
    }
    (*i)++;
  }
}

void s21_setDefAccuracy(s21_flags *flags, char symbol) {
  s21_strchr("diouxX", symbol) ? flags->accuracy = 1 : 0;
  s21_strchr("eEfgG", symbol) ? flags->accuracy = 6 : 0;
  s21_strchr("p", symbol) ? flags->accuracy = 16 : 0;
}

void s21_initFlags(char ch, s21_flags *flags) {
  switch (ch) {
    case '-':
      flags->alignment += 1;
      break;
    case '+':
      flags->plus += 1;
      break;
    case '#':
      flags->grid += 1;
      break;
    case '0':
      flags->zero += 1;
      break;
    case ' ':
      flags->space += 1;
      break;
    default:
      break;
  }
  if (flags->alignment && flags->zero) {
    flags->zero = 0;
  }
  if (flags->space && flags->plus) {
    flags->space = 0;
  }
}

int s21_handleSpecs(char *str, const char *format, va_list args,
                    s21_flags *flags, int total, int *i) {
  int *size = 0;
  switch (format[*i]) {
    case 'c':
      total = s21_handleChar(args, *flags, str, total);
      break;
    case 'i':
    case 'd':
      total = s21_handleInt(args, *flags, str, total);
      break;
    case 's':
      total = s21_handleStr(args, *flags, str, total);
      break;
    case 'u':
      total = s21_handleUnsInt(args, *flags, str, total);
      break;
    case '%':
      total = s21_putChar(str, '%', total);
      break;
    case 'x':
    case 'X':
      total = s21_handleHexOct(args, *flags, str, total, format, *i);
      break;
    case 'p':
      total = s21_hexPoint(str, va_arg(args, s21_size_t), total, *flags);
      break;
    case 'o':
      total = s21_handleHexOct(args, *flags, str, total, format, *i);
      break;
    case 'n':
      size = va_arg(args, int *);
      *size = (int)s21_strlen(str);
      break;
    case 'e':
    case 'E':
      total = s21_handleSNot(
          str, format[*i],
          flags->L ? va_arg(args, long double) : va_arg(args, double), total,
          *flags);
      break;
    case 'f':
      total = s21_doubleToString(
          str, 'f', flags->L ? va_arg(args, long double) : va_arg(args, double),
          total, *flags);
      break;
    case 'g':
    case 'G':
      total = s21_doubleToStringShort(
          str, format[*i],
          flags->L ? va_arg(args, long double) : va_arg(args, double), total,
          *flags);
      break;
    default:
      break;
  }
  return total;
}

int s21_handleChar(va_list args, s21_flags flags, char *str, int total) {
  unsigned int len = 1;
  char ch = (char)va_arg(args, int);
  if (flags.l) ch = (wchar_t)ch;
  if (flags.alignment) {
    total = s21_putChar(str, ch, total);
    total = s21_handleAlignmentChar(str, flags, total, len);
  } else {
    total = s21_handleAlignmentChar(str, flags, total, len);
    total = s21_putChar(str, ch, total);
  }
  return total;
}

int s21_handleInt(va_list args, s21_flags flags, char *str, int total) {
  int len = 0;
  long long number = 0;
  if (flags.h) {
    number = (short int)va_arg(args, int);
  } else if (flags.l == 1) {
    number = (long int)va_arg(args, long int);
  } else if (flags.l == 2) {
    number = (unsigned long)va_arg(args, unsigned long);
  } else
    number = va_arg(args, int);
  len += s21_intLen(number, 10);
  char *result = (char *)calloc(flags.accuracy + flags.width + 8, sizeof(char));
  if (result != s21_NULL) {
    if (number < 0) {
      total = s21_putChar(result, '-', total);
      number = -number;
      flags.accuracy++;
      len++;
      flags.width++;
    } else if (number > 0 && flags.plus) {
      total = s21_putChar(result, '+', total);
      flags.accuracy++;
      len++;
    }
    while (len < flags.accuracy) {
      total = s21_putChar(result, '0', total);
      len++;
    }
    total = s21_putNbr(result, number, total);
    if ((flags.width - flags.accuracy) > 0) {
      total = s21_handleAlignmentStr(str, result, flags, total, &len);
    }
    if (flags.accuracy != 0 || number != 0)
      s21_putStr(str, result, total, len);
    else
      total = 0;
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_handleStr(va_list args, s21_flags flags, char *str, int total) {
  char *pstr = (char *)calloc(8, sizeof(char));
  char *mystr = s21_NULL;
  wchar_t *pwcs = s21_NULL;
  s21_size_t n = 0;
  unsigned int len = 0;
  if (pstr != s21_NULL) {
    void *tmp = s21_NULL;
    if (flags.l) {
      pwcs = va_arg(args, wchar_t *);
      n = s21_wcslen(pwcs);
      tmp = realloc(pstr, (n + 10) * sizeof(wchar_t));
      if (s21_NULL == tmp) {
        printf("Memory isn't allocated");
      } else {
        pstr = tmp;
      }
      wcstombs(pstr, pwcs, n);
    } else {
      mystr = va_arg(args, char *);
      n = s21_strlen(mystr);
      tmp = realloc(pstr, (n + 10) * sizeof(char));
      if (s21_NULL == tmp) {
        printf("Memory isn't allocated");
      } else {
        pstr = tmp;
      }
      s21_strcpy(pstr, mystr);
    }
    if (flags.accuracy == -1) flags.accuracy = s21_strlen(pstr);
    char *result =
        (char *)calloc(flags.accuracy + flags.width + 50, sizeof(char));
    if (result != s21_NULL) {
      if (flags.alignment) {
        total = s21_putStr(str, pstr, total, flags.accuracy);
        len = flags.accuracy;
        total = s21_handleAlignmentChar(str, flags, total, len);
      } else {
        s21_putStr(result, pstr, total, flags.accuracy);
        len = s21_strlen(result);
        total = s21_handleAlignmentChar(str, flags, total, len);
        total = s21_putStr(str, result, total, len);
      }
      free(tmp);
      free(result);
      return total;
    } else {
      free(result);
      return 0;
    }
  } else {
    free(pstr);
    return 0;
  }
}

int s21_handleUnsInt(va_list args, s21_flags flags, char *str, int total) {
  int len = 0;
  char *result =
      (char *)calloc(flags.accuracy + flags.width + 50, sizeof(char));
  if (result != s21_NULL) {
    unsigned long long number = 0;
    if (flags.h) {
      number = (unsigned short)va_arg(args, unsigned);
    } else if (flags.l == 1) {
      number = (unsigned long)va_arg(args, unsigned long);
    } else if (flags.l == 2) {
      number = (unsigned long long)va_arg(args, unsigned long long);
    } else
      number = (unsigned int)va_arg(args, unsigned);
    len += s21_intLen(number, 10);
    while (len < flags.accuracy) {
      total = s21_putChar(result, '0', total);
      len++;
    }
    total = s21_putUNbr(result, number, total);
    if ((flags.width - flags.accuracy) > 0) {
      total = s21_handleAlignmentStr(str, result, flags, total, &len);
    }
    s21_putStr(str, result, total, s21_strlen(result));
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_handleHexOct(va_list args, s21_flags flags, char *str, int total,
                     const char *format, int i) {
  char *result =
      (char *)calloc(flags.accuracy + flags.width + 50, sizeof(char));
  if (result != s21_NULL) {
    unsigned long long number = 0;
    if (flags.h) {
      number = (unsigned long long)va_arg(args, unsigned);
    } else if (flags.l == 1) {
      number = (unsigned long long)va_arg(args, unsigned long);
    } else if (flags.l == 2) {
      number = (unsigned long long)va_arg(args, unsigned long long);
    } else
      number = (unsigned long long)va_arg(args, unsigned);
    int len = s21_intLen(number, format[i] == 'o' ? 8 : 16);
    if (flags.grid && number != 0) {
      switch (format[i]) {
        case 'o':
          s21_putChar(result, '0', total);
          len++;
          break;
        case 'x':
          s21_putStr(result, "0x", total, 2);
          break;
        case 'X':
          s21_putStr(result, "0X", total, 2);
          break;
        default:
          break;
      }
    }
    while (len < flags.accuracy) {
      s21_putChar(result, '0', total);
      len++;
    }
    total = s21_hexOctDecimal(result, format[i], number, total);
    len = s21_strlen(result);
    total = s21_handleAlignmentStr(str, result, flags, total, &len);
    s21_putStr(str, result, total, len);
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_handleSNot(char *str, const char ch, long double value, int total,
                   s21_flags flags) {
  unsigned int degree = 0;
  long double tmp = value;
  int len = 7 + flags.accuracy;
  char *result = (char *)calloc(len + 50, sizeof(char));

  if (result != s21_NULL) {
    if (value < 0.0) {
      value = -value;
      tmp = value;
      degree = s21_findDegree(&value);
      value = -value;
    } else {
      degree = s21_findDegree(&value);
    }
    s21_doubleToString(result, ch, value, total, flags);
    if (ch == 'e' || ch == 'g') {
      if (tmp == 0.0)
        s21_putStr(result, "e+", total, 2);
      else
        s21_putStr(result, tmp < 1.0 ? "e-" : "e+", total, 2);
    } else {
      if (tmp == 0.0)
        s21_putStr(result, "E+", total, 2);
      else
        s21_putStr(result, tmp < 1.0 ? "E-" : "E+", total, 2);
    }
    if (degree < 10) {
      s21_putChar(result, '0', total);
    }
    s21_putNbr(result, degree, total);
    len = s21_strlen(result);
    unsigned int cnt = 0;
    while (len < flags.width) {
      total = s21_putChar(flags.alignment ? result : str,
                          flags.zero ? '0' : ' ', total);
      len++;
      cnt++;
    }
    if (flags.alignment) total -= cnt;
    total = s21_putStr(str, result, total, len);
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_doubleToString(char *str, const char ch, long double value, int total,
                       s21_flags flags) {
  long double tmp = value;
  if (flags.space && value >= 0.0) total = s21_putChar(str, ' ', total);
  char *result =
      (char *)calloc(flags.accuracy + flags.width + 50, sizeof(char));
  if (result != s21_NULL) {
    if (value < 0.0) {
      s21_putChar(result, '-', total);
      value = -value;
    } else if (value > 0.0 && flags.plus) {
      s21_putChar(result, '+', total);
    }
    unsigned long main_part = 0;
    if (ch == 'g') value += 5 * 1 / powl(10, flags.accuracy);
    main_part = value;
    if (flags.accuracy != 0) {
      s21_putNbr(result, main_part, total);
      s21_putChar(result, '.', 1);
      value = value - main_part;
      int i = s21_strlen(result);
      value += 5 * 1 / powl(10, flags.accuracy + 1);
      flags.accuracy += i;
      for (; i < flags.accuracy; i++) {
        value = modfl(value *= 10, &tmp);
        result[i] = tmp + '0';
      }
    } else {
      value = s21_round(value, 0);
      s21_putNbr(result, (int)value, total);
      if (flags.grid) s21_putChar(result, '.', total);
    }
    int len = s21_strlen(result);
    if (ch == 'f') {
      if (!flags.alignment)
        total = s21_handleAlignmentChar(str, flags, total, len);
      else
        s21_handleAlignmentChar(result, flags, total, len);
    }
    len = s21_strlen(result);
    if (ch == 'g' || ch == 'G') {
      if (!flags.grid) {
        unsigned int i = len - 2;
        if (flags.accuracy == 0) i = 0;
        while ((result[i] == '0' || result[i] == '.') && i != 0) {
          result[i] = 0;
          i--;
        }
      }
    }
    total = s21_putStr(str, result, total, len);
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_doubleToStringShort(char *str, char ch, double value, int total,
                            s21_flags flags) {
  int flag = 1;
  if (flags.accuracy == 0) {
    flags.accuracy = 6;
    flag = 0;
  }
  char *result =
      (char *)calloc(flags.width + flags.accuracy + 50, sizeof(char));
  if (result != s21_NULL) {
    int zeros = s21_findZeros(value);
    if (value < 0.0) {
      if (!flags.zero) {
        s21_putChar(result, '-', total);
      } else
        total = s21_putChar(str, '-', total);
      value = -value;
      flags.width--;
      if (!flags.zero) {
        flags.accuracy++;
        flags.width++;
      }
    }
    if (value == 0.0) {
      total = s21_putChar(str, '0', total);
    } else if (value < 1.0 && zeros < 4) {
      s21_doubleToString(result, 'g', value, total, flags);
      flags.accuracy++;
    } else if (value < 1.0 && zeros >= 4) {
      s21_handleSNot(result, ch, value, total, flags);
    } else if (value >= 1.0) {
      s21_doubleToString(result, 'g', value, total, flags);
      flags.accuracy += 1;
      if (flags.plus) flags.accuracy++;
      result[flags.accuracy] = 0;
    }
    int len = s21_strlen(result);
    if (result[len - 1] == '.') len--;
    result[len] = '\0';
    if (flags.alignment) {
      flags.accuracy += s21_handleAlignmentChar(result, flags, total, len);
    } else {
      total = s21_handleAlignmentChar(str, flags, total, len);
    }
    if (flag == 0) {
      int i = 0;
      while (*(result + i) != '.') i++;
      i++;
      while (result[i] == '0') i++;
      result[i + 1] = '\0';
    }
    total = s21_putStr(str, result, total, flags.accuracy);
    free(result);
    return total;
  } else {
    free(result);
    return 0;
  }
}

int s21_hexPoint(char *str, unsigned long arg, int total, s21_flags flags) {
  char *result =
      (char *)calloc(flags.accuracy + flags.width + 50, sizeof(char));
  if (result != s21_NULL) {
    s21_putStr(result, "0x", total, 2);
    s21_puthexOctDecimal(result, arg, "0123456789abcdef", 16);
    unsigned int len = s21_strlen(result);
    result[len] = '\0';
    if (flags.alignment)
      s21_handleAlignmentChar(result, flags, total, len);
    else
      total = s21_handleAlignmentChar(str, flags, total, len);
    len = s21_strlen(result);
    total = s21_putStr(str, result, total, len);
    free(result);
    return (total);
  } else {
    free(result);
    return 0;
  }
}

int s21_putChar(char *str, const char ch, int total) {
  while (*str != '\0') {
    str++;
  }
  *str = ch;
  str++;
  *str = '\0';
  total++;
  return total;
}

int s21_putStr(char *str, const char *adstr, int total, int accuracy) {
  if (!adstr) {
    total = s21_putStr(str, "(null)", total, 6);
  } else {
    for (int i = 0; i < accuracy && i < (int)s21_strlen(adstr); i++) {
      total = s21_putChar(str, adstr[i], total);
    }
  }
  return total;
}

int s21_putNbr(char *str, long long value, int total) {
  if (value == -2147483648) {
    total = s21_putChar(str, '2', total);
    total = s21_putNbr(str, 147483648, total);
  } else if (value >= 10) {
    total = s21_putNbr(str, value / 10, total);
    total = s21_putChar(str, value % 10 + '0', total);
  } else {
    total = s21_putChar(str, value % 10 + '0', total);
  }
  return total;
}

int s21_putUNbr(char *str, unsigned long long value, int total) {
  if (value >= 10) {
    total = s21_putNbr(str, value / 10, total);
    total = s21_putChar(str, value % 10 + '0', total);
  } else {
    total = s21_putChar(str, value % 10 + '0', total);
  }
  return total;
}

int s21_hexOctDecimal(char *str, char c, unsigned long long i, int total) {
  if (c == 'x')
    s21_puthexOctDecimal(str, i, "0123456789abcdef", 16);
  else if (c == 'X')
    s21_puthexOctDecimal(str, i, "0123456789ABCDEF", 16);
  else if (c == 'o')
    s21_puthexOctDecimal(str, i, "01234567", 8);
  total += s21_strlen(str);
  return total;
}

void s21_puthexOctDecimal(char *str, unsigned long n, char *base,
                          unsigned long baselen) {
  if (n >= baselen) s21_puthexOctDecimal(str, n / baselen, base, baselen);
  s21_putChar(str, base[n % baselen], 1);
}

int s21_intLen(unsigned long n, unsigned long baselen) {
  int i;
  i = 1;
  while (n >= baselen) {
    n /= baselen;
    i++;
  }
  return i;
}

double s21_round(double value, int accuracy) {
  int degree = pow(10, accuracy + 1);
  value *= degree;
  if ((int)value % 10 >= 5) value += (int)value % 10;
  value /= degree;
  return value;
}

unsigned int s21_findDegree(long double *value) {
  unsigned int i = 0;
  if (*value != 0.0) {
    while (*value < 1.0) {
      *value *= 10;
      i++;
    }
    while (*value >= 1.0) {
      *value /= 10;
      i++;
    }
    i--;
    *value *= 10;
  }
  return i;
}

unsigned int s21_findZeros(long double value) {
  unsigned int i = 0;
  if (value == 0) {
    i = 6;
  } else if (value < 1.0) {
    while ((int)value % 10 == 0) {
      value *= 10;
      i++;
    }
    i -= 1;
  } else {
    value *= 10;
    while ((int)value % 10 == 0) {
      value *= 10;
      i++;
    }
  }
  return i;
}

int s21_atoib(const char *format, int base) {
  const char *str = format;
  int n = 0;
  while (*str >= '0' && *str <= '9') {
    n *= base;
    n += *str++;
    n -= '0';
  }
  return n;
}

void s21_resetFlags(s21_flags *flags) {
  flags->accuracy = 0;
  flags->alignment = 0;
  flags->grid = 0;
  flags->h = 0;
  flags->L = 0;
  flags->l = 0;
  flags->plus = 0;
  flags->space = 0;
  flags->width = 0;
  flags->zero = 0;
}

int s21_handleAlignmentChar(char *str, s21_flags flags, int total, int len) {
  while (len < flags.width) {
    total = s21_putChar(str, flags.zero ? '0' : ' ', total);
    len++;
  }
  return total;
}

int s21_handleAlignmentStr(char *str, char *result, s21_flags flags, int total,
                           int *len) {
  while (*len < flags.width) {
    total = s21_putChar(flags.alignment ? result : str, flags.zero ? '0' : ' ',
                        total);
    (*len)++;
  }
  return total;
}

s21_size_t s21_wcslen(const wchar_t *s) {
  s21_size_t len = 0;
  while (s[len] != L'\0') {
    ++len;
  }
  return len;
}
