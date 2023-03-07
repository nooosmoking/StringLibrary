#ifndef _S21_SPRINTF_H
#define _S21_SPRINTF_H
#include <stdarg.h>

#include "s21_string.h"

typedef struct s21_flags {
  int accuracy;
  int width;
  int alignment;
  int plus;
  int zero;
  int grid;
  int space;
  int h;
  int l;
  int L;
} s21_flags;

int s21_sprintf(char *str, const char *format, ...);
int s21_handleParams(char *str, const char *format, va_list args);
int s21_convertStr(char *str, const char *format, va_list args, int *flag,
                   int *total, int i);
int s21_calcChar(char *str, const char *format, int *i, va_list args, int total,
                 s21_flags flags);
void s21_findWidth(const char *format, va_list args, s21_flags *flags, int *i);
void s21_findAccuracy(const char *format, va_list args, s21_flags *flags,
                      int *i);
void s21_findLength(const char *format, s21_flags *flags, int *i);
int s21_handleSpecs(char *str, const char *format, va_list args,
                    s21_flags *flags, int total, int *i);

int s21_putChar(char *str, const char ch, int total);
int s21_putStr(char *str, const char *adstr, int total, int accuracy);
int s21_putNbr(char *str, long long value, int total);
int s21_putUNbr(char *str, unsigned long long value, int total);
int s21_handleInt(va_list args, s21_flags flags, char *str, int total);
int s21_handleChar(va_list args, s21_flags flags, char *str, int total);
int s21_handleStr(va_list args, s21_flags flags, char *str, int total);
int s21_handleUnsInt(va_list args, s21_flags flags, char *str, int total);
int s21_handleHexOct(va_list args, s21_flags flags, char *str, int total,
                     const char *format, int i);
int s21_handleSNot(char *str, const char ch, long double value, int total,
                   s21_flags flags);
int s21_handleAlignmentChar(char *str, s21_flags flags, int total, int len);
int s21_handleAlignmentStr(char *str, char *tmp, s21_flags flags, int total,
                           int *len);

int s21_hexOctDecimal(char *str, char c, unsigned long long i, int total);
void s21_puthexOctDecimal(char *str, unsigned long n, char *base,
                          unsigned long baselen);
int s21_intLen(unsigned long n, unsigned long baselen);
int s21_hexPoint(char *str, unsigned long arg, int total, s21_flags flags);

int s21_findFlags(s21_flags *flags, const char *format, int i);
void s21_initFlags(char ch, s21_flags *flags);
int s21_doubleToString(char *str, const char ch, long double value, int total,
                       s21_flags flags);
int s21_doubleToStringShort(char *str, char ch, double value, int total,
                            s21_flags flags);
unsigned int s21_findDegree(long double *value);
double s21_round(double value, int accuracy);
unsigned int s21_findZeros(long double value);
void s21_setDefAccuracy(s21_flags *flags, char symbol);
int s21_fractionalToStr(double value, char *str, int accuracy);
int s21_atoib(const char *format, int base);
void s21_resetFlags(s21_flags *flags);
s21_size_t s21_wcslen(const wchar_t *s);
int s21_sprintf(char *str, const char *format, ...);
#endif  // _S21_SPRINTF_H