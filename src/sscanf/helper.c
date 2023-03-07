#include "s21_sscanf.h"

int len_hex(char *str, int width) {
  int i = 0;
  while ((isdigit(*str) || (*str >= 'A' && *str <= 'F') ||
          (*str >= 'a' && *str <= 'f')) &&
         width != 0) {
    i++;
    str++;
    width--;
  };
  return i;
}
