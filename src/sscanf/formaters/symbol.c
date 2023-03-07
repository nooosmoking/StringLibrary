#include "s21_sscanf.h"

stac_list static_f(stac_list kwargs, bool *err) {
  if (kwargs.spec_p.spec == *kwargs.str) {
    kwargs.str++;
  } else {
    *err = STOP_ITER;
  }
  return kwargs;
}

stac_list spec__(stac_list kwargs, bool *err) { return static_f(kwargs, err); }

stac_list spec_n(stac_list kwargs, bool *err) {
  if (kwargs.count) kwargs.count = +1;
  *va_arg(kwargs.args, int *) = kwargs.count;
  *err = FALSE;
  return kwargs;
}

stac_list spec_c(stac_list kwargs, bool *err) {
  wchar_t *ex = s21_NULL;
  switch (kwargs.spec_p.len) {
    case 'l':
      ex = (wchar_t *)kwargs.str;
      if (!(kwargs.spec_p.flag & WITH)) *(va_arg(kwargs.args, wchar_t *)) = *ex;
      kwargs.str += sizeof(wchar_t);
      *err = FALSE;
      kwargs.str = (char *)ex++;
      break;
    default:
      if (!(kwargs.spec_p.flag & WITH))
        *(va_arg(kwargs.args, char *)) = *kwargs.str;
      kwargs.str++;
      *err = FALSE;
      break;
  }
  return kwargs;
}

stac_list spec_s(stac_list kwargs, bool *err) {
  char *dst = s21_NULL;
  char buff[5] = {0};
  wchar_t *w_ex = (wchar_t *)&buff;
  wchar_t *w_dst = s21_NULL;

  switch (kwargs.spec_p.len) {
    case 'l':
      if (!(kwargs.spec_p.flag & WITH)) w_dst = va_arg(kwargs.args, wchar_t *);

      do {
        for (int i = 0; i < 4 && kwargs.str[i]; i++, kwargs.str += 4) {
          buff[i] = kwargs.str[i];
        }
        if (!(kwargs.spec_p.flag & WITH)) {
          *w_dst = *w_ex;
          w_dst++;
        }
      } while (!issep_w(*w_ex) && *(w_ex) != L'\0' && *kwargs.str);
      *err = FALSE;
      kwargs.str++;
      break;
    default:
      if (!(kwargs.spec_p.flag & WITH)) dst = (va_arg(kwargs.args, char *));
      for (; !issep(*kwargs.str) && kwargs.str[0]; kwargs.str++) {
        if (!(kwargs.spec_p.flag & WITH)) {
          *dst = *kwargs.str;
          dst++;
        }
      }
      if (!(kwargs.spec_p.flag & WITH)) *dst = '\0';
      *err = FALSE;
      break;
  }
  return kwargs;
}
