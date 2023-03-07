#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *sc;
  for (sc = str; *sc != '\0'; ++sc) {
  }
  return sc - str;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest != src) {
    char *tmp = (char *)dest;
    char *c_s = (char *)src;
    while (n--) *tmp++ = *c_s++;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *tmp;
  const char *c_s;
  if (dest <= src) {
    tmp = (char *)dest;
    c_s = src;
    while (n--) *tmp++ = *c_s++;
  } else {
    tmp = (char *)dest;
    tmp += n;
    c_s = src;
    c_s += n;
    while (n--) *--tmp = *--c_s;
  }
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t ret = s21_strlen(src);
  if (ret) {
    s21_memcpy(dest, src, ret);
  }
  dest[ret] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  int len = 0;
  while (*dest) {
    dest++;
    len++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
    len++;
  }
  *dest = '\0';
  dest -= len;
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int strLength = s21_strlen(src);

  for (s21_size_t x = 0; x < n && src[x] != '\0'; x += 1) {
    dest[strLength + x] = src[x];
    dest[strLength + x + 1] = '\0';
  }

  for (s21_size_t x = 0, strLength = s21_strlen(src); x < n && src[x] != '\0';
       x += 1) {
    dest[strLength + x] = src[x];
    dest[strLength + x + 1] = '\0';
  }

  return dest;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t count) {
  unsigned char *sc1, *sc2;
  int res = 0;
  for (sc1 = (unsigned char *)str1, sc2 = (unsigned char *)str2; 0 < count;
       ++sc1, ++sc2, count--)
    if ((res = *sc1 - *sc2) != 0) break;
  return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  unsigned char c1, c2;
  int r = 0;
  while (n && !r) {
    c1 = *str1++;
    c2 = *str2++;
    if (c1 != c2) r = c1 < c2 ? -1 : 1;
    if (!c1) break;
    n--;
  }
  return r;
}

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  for (int x = 0; result == 0 && str1[x] != '\0' && str2[x] != '\0'; x += 1)
    if (str1[x] != str2[x]) result = str1[x] - str2[x];

  return result == 0 ? 0 : (result > 0 ? 1 : (-1));
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  while (n-- != 0) {
    if ((unsigned char)c == *p++) {
      return (void *)(p - 1);
    }
  }
  return s21_NULL;
}

char *s21_strchr(const char *str, int c) {
  for (; *str != (char)c; ++str)
    if (*str == '\0') return s21_NULL;
  return (char *)str;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p;

  for (p = str1; *p != '\0'; ++p) {
    if (s21_strchr(str2, *p)) break;
  }
  return p - str1;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *p;

  for (p = str1; *p != '\0'; ++p) {
    if (s21_strchr(str2, *p)) break;
  }
  if (*str1 && *str2 && *p)
    return (char *)p;
  else
    return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  const char *last = s21_NULL;
  do {
    if (*str == (char)c) last = str;
  } while (*str++);
  return (char *)last;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *p;

  for (p = str1; *p != '\0'; ++p) {
    if (!s21_strchr(str2, *p)) break;
  }
  return p - str1;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t l1, l2;

  l2 = s21_strlen(needle);
  if (!l2) return (char *)haystack;
  l1 = s21_strlen(haystack);
  while (l1 >= l2) {
    l1--;
    if (!s21_memcmp(haystack, needle, l2)) return (char *)haystack;
    haystack++;
  }
  return s21_NULL;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t x = 0; x < n; x += 1) {
    ((char *)str)[x] = c;
  }
  return str;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  register int ch;

  if (str == 0) {
    str = last;
  }
  do {
    if ((ch = *str++) == '\0') {
      str = s21_NULL;
    }
  } while (str != s21_NULL && s21_strchr(delim, ch));
  if (str != s21_NULL) {
    --str;
    last = str + s21_strcspn(str, delim);
    if (*last != 0) {
      *last++ = 0;
    }
  }
  return str;
}

void *s21_to_upper(const char *str) {
  char *str_copy = s21_NULL;

  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);

    str_copy = (char *)malloc(sizeof(char) * (len + 1));

    if (str_copy) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          str_copy[i] = (str[i] - 'a') + 'A';
        } else {
          str_copy[i] = str[i];
        }
      }
      str_copy[len] = '\0';
    }
  }

  return str_copy;
}

void *s21_to_lower(const char *str) {
  char *str_copy = s21_NULL;

  if (str != s21_NULL) {
    s21_size_t len = s21_strlen(str);

    str_copy = (char *)malloc(sizeof(char) * (len + 1));

    if (str_copy) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          str_copy[i] = (str[i] - 'A') + 'a';
        } else {
          str_copy[i] = str[i];
        }
      }
      str_copy[len] = '\0';
    }
  }

  return str_copy;
}
