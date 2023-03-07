#include <check.h>
#include <string.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"

START_TEST(strcpy_test) {
  char src1[104] = "This is Sparta";
  char dest1[104] = {0};
  ck_assert_str_eq(s21_strcpy(dest1, ""), strcpy(dest1, ""));
  ck_assert_str_eq(s21_strcpy(dest1, src1), strcpy(dest1, src1));
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strcpy(d1, s1);
  ck_assert_msg(!strcmp(d1, s1), "1st  strcpy test failed");
  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strcpy(d2, s2);
  ck_assert_msg(!strcmp(d2, s2), "2nd strcpy test failed");
  char s3[50] = "";
  char d3[50] = "HELLO";
  s21_strcpy(d3, s3);
  ck_assert_msg(!strcmp(d3, s3), "3rd strcpy test failed");
  char s4[50] = "amogus";
  char d4[50] = "HELLO";
  s21_strcpy(d4, s4);
  ck_assert_msg(!strcmp(d4, s4), "4rth strcpy test failed");
  char s5[50] = "Shrek";
  char d5[50] = "what";
  s21_strcpy(d5, s5);
  ck_assert_msg(!strcmp(d5, s5), "5th strcpy test failed");
}
END_TEST

START_TEST(strncpy_test) {
  char src1[104] = "This is for strncpy";
  char dest1[104] = {0};
  ck_assert_str_eq(s21_strncpy(dest1, "", 7), strncpy(dest1, "", 7));
  ck_assert_str_eq(s21_strncpy(dest1, src1, 7), strncpy(dest1, src1, 7));
  char s1[50] = "Sample Text";
  char d1[50] = "";
  s21_strncpy(d1, s1, 2);
  ck_assert_msg(!strcmp(d1, "Sa"), "1st strncpy test failed");
  char s2[50] = "AAAAA";
  char d2[50] = "NO";
  s21_strncpy(d2, s2, 0);
  ck_assert_msg(!strcmp(d2, "NO"), "2nd strncpy test failed");
  char s3[50] = "H";
  char d3[50] = "fELLO";
  s21_strncpy(d3, s3, 1);
  ck_assert_msg(!strcmp(d3, "HELLO"), "3rd strncpy test failed");
  char s4[50] = "amo";
  char d4[50] = "qwegus";
  s21_strncpy(d4, s4, 3);
  ck_assert_msg(!strcmp(d4, "amogus"), "4rth strncpy test failed");
  char s5[50] = "shrek";
  char d5[50] = "s";
  s21_strncpy(d5, s5, 5);
  ck_assert_msg(!strcmp(d5, "shrek"), "5th strncpy test failed");
}
END_TEST

START_TEST(strcspn_test) {
  const char str1[] = "ABCDEF4960910";
  const char str2[] = "013";
  const char str3[] = "J";
  const char str4[] = "609";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn(str1, ""), strcspn(str1, ""));
  ck_assert_int_eq(s21_strcspn("", str2), strcspn("", str2));
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
  ck_assert_int_eq(s21_strcspn(str1, str4), strcspn(str1, str4));
}
END_TEST

START_TEST(strerror_test) {
  for (int i = 1; i <= 144; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  char *str1 = s21_strerror(20);
  char *str2 = strerror(20);
  ck_assert_str_eq(str1, str2);

  char *str3 = s21_strerror(12);
  char *str4 = strerror(12);
  ck_assert_str_eq(str3, str4);

  char *str5 = s21_strerror(1337);
  char *str6 = strerror(1337);
  ck_assert_str_eq(str5, str6);

  char *str7 = s21_strerror(1);
  char *str8 = strerror(1);
  ck_assert_str_eq(str7, str8);

  char *str9 = s21_strerror(25);
  char *str10 = strerror(25);
  ck_assert_str_eq(str9, str10);
}
END_TEST

START_TEST(strlen_test) {
  char str[6] = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
  ck_assert_int_eq(s21_strlen(str), 5);
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen(""), 0);
  ck_assert_int_eq(s21_strlen("Hola \n"), strlen("Hola \n"));
  ck_assert_int_eq(s21_strlen("Hola \0"), strlen("Hola \0"));
  char *s1 = "0123456789";
  ck_assert_msg(s21_strlen(s1) == strlen(s1), "1st strlen test failed");
  char *s2 = "";
  ck_assert_msg(s21_strlen(s2) == strlen(s2), "2nd strlen test failed");
  char *s3 = "amogus";
  ck_assert_msg(s21_strlen(s3) == strlen(s3), "3rd strlen test failed");
  char *s4 = "shrek";
  ck_assert_msg(s21_strlen(s4) == strlen(s4), "4rth strlen test failed");
  char *s5 = "is love";
  ck_assert_msg(s21_strlen(s5) == strlen(s5), "5th strlen test failed");
}
END_TEST

START_TEST(strpbrk_test) {
  const char str[] = "abcde2fghi3jk4l";
  const char *empty = "";
  ck_assert_ptr_eq(s21_strpbrk(str, "34"), strpbrk(str, "34"));
  ck_assert_ptr_eq(s21_strpbrk(str, "abcd"), strpbrk(str, "abcd"));
  ck_assert_ptr_eq(s21_strpbrk(str, "ABCD"), strpbrk(str, "ABCD"));
  ck_assert_ptr_eq(s21_strpbrk(str, "a"), strpbrk(str, "a"));
  ck_assert_ptr_eq(s21_strpbrk(str, "3"), strpbrk(str, "3"));
  ck_assert_ptr_eq(s21_strpbrk(str, "000"), strpbrk(str, "000"));
  ck_assert_ptr_eq(s21_strpbrk(str, empty), strpbrk(str, empty));
  ck_assert_ptr_eq(s21_strpbrk(empty, "34"), strpbrk(empty, "34"));
  ck_assert_ptr_eq(s21_strpbrk(empty, empty), strpbrk(empty, empty));
  char *str1 = "hello";
  char *str2 = "hel";
  char *res1, *res2;
  res1 = s21_strpbrk(str1, str2);
  res2 = strpbrk(str1, str2);
  ck_assert_str_eq(res1, res2);
  char *str4 = "ab";
  res1 = s21_strpbrk(str1, str4);
  res2 = strpbrk(str1, str4);
  ck_assert_ptr_eq(res1, res2);
  char *str5 = "o";
  res1 = s21_strpbrk(str1, str5);
  res2 = strpbrk(str1, str5);
  ck_assert_str_eq(res1, res2);
  char *str6 = "abcdefghjkl";
  char *str7 = "abcd";
  res1 = s21_strpbrk(str6, str7);
  res2 = strpbrk(str6, str7);
  ck_assert_str_eq(res1, res2);
  char *str8 = "amogus is shrek?";
  char *str9 = "is";
  res1 = s21_strpbrk(str8, str9);
  res2 = s21_strpbrk(str8, str9);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(strrchr_test) {
  const char str1[] = "Some.words.for.the.test";
  const char ch1 = '.';
  ck_assert_str_eq(s21_strrchr(str1, ch1), strrchr(str1, ch1));
  ck_assert_str_eq(s21_strrchr(str1, ch1), ".test");
  ck_assert_ptr_eq(s21_strrchr(str1, '-'), strrchr(str1, '-'));
  ck_assert_ptr_eq(s21_strrchr(str1, 0), strrchr(str1, 0));
  ck_assert_ptr_eq(s21_strrchr("", '-'), strrchr("", '-'));
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "amogus";
  ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'),
                "1st strrchr test failed");
  ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'),
                "2nd strrchr test failed");
  ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'),
                "3rd strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '),
                "4rth strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'),
                "5th strrchr test failed");
}
END_TEST

START_TEST(strspn_test) {
  const char str1[] = "ABCDEFG019874";
  ck_assert_int_eq(s21_strspn(str1, "ABCD"), strspn(str1, "ABCD"));
  ck_assert_int_eq(s21_strspn(str1, "19"), strspn(str1, "19"));
  ck_assert_int_eq(s21_strspn(str1, "Hola!"), strspn(str1, "Hola!"));
  ck_assert_int_eq(s21_strspn(str1, "F!"), strspn(str1, "F!"));
  ck_assert_int_eq(s21_strspn(str1, "\0"), strspn(str1, "\0"));
  ck_assert_int_eq(s21_strspn(str1, ""), strspn(str1, ""));
  ck_assert_int_eq(s21_strspn("", str1), strspn("", str1));
  ck_assert_int_eq(s21_strspn("", ""), strspn("", ""));
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";
  ck_assert_msg(s21_strspn(s1, s2) == strspn(s1, s2), "1st strspn test failed");
  ck_assert_msg(s21_strspn(s3, s2) == strspn(s3, s2), "2nd strspn test failed");
  ck_assert_msg(s21_strspn(s2, s3) == strspn(s2, s3), "3rd strspn test failed");
  ck_assert_msg(s21_strspn(s1, s3) == strspn(s1, s3),
                "4rth strspn test failed");
  ck_assert_msg(s21_strspn(s3, s1) == strspn(s3, s1), "5th strspn test failed");
}
END_TEST

START_TEST(strstr_test) {
  const char haystack1[30] = "TutorialsPointYouGotThePoint";
  const char needle1[10] = "Point";
  const char *empty = "";
  ck_assert_str_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
  ck_assert_str_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
  ck_assert_ptr_eq(s21_strstr(haystack1, needle1), strstr(haystack1, needle1));
  ck_assert_ptr_eq(s21_strstr(haystack1, empty), strstr(haystack1, empty));
  ck_assert_ptr_eq(s21_strstr(empty, haystack1), strstr(empty, haystack1));
  ck_assert_ptr_eq(s21_strstr(empty, empty), strstr(empty, empty));
  ck_assert_ptr_eq(s21_strstr(haystack1, "Something"),
                   strstr(haystack1, "Something"));
  ck_assert_ptr_eq(s21_strstr(haystack1, "\0"), strstr(haystack1, "\0"));
  char *s1 = "School-21";
  char *s2 = "ho";
  char *s3 = "";
  ck_assert_msg(s21_strstr(s1, s2) == strstr(s1, s2), "1st strstr test failed");
  ck_assert_msg(s21_strstr(s1, s3) == strstr(s1, s3), "2nd strstr test failed");
  ck_assert_msg(s21_strstr(s3, s2) == strstr(s3, s2), "3rd strstr test failed");
  ck_assert_msg(s21_strstr(s2, s3) == strstr(s2, s3),
                "4rth strstr test failed");
  ck_assert_msg(s21_strstr(s3, s1) == strstr(s3, s1), "5th strstr test failed");
}
END_TEST

START_TEST(strtok_test) {
  char str[20] = "Hello.World";
  char delim[20] = ".";
  char *empty = "";
  ck_assert_str_eq(s21_strtok(str, delim), strtok(str, delim));
  ck_assert_str_eq(s21_strtok(str, delim), "Hello");
  ck_assert_str_eq(s21_strtok(str, "\0"), strtok(str, "\0"));
  ck_assert_str_eq(s21_strtok(str, "asdf"), strtok(str, "asdf"));
  ck_assert_str_eq(s21_strtok(str, "1234"), strtok(str, "1234"));
  ck_assert_str_eq(s21_strtok(str, empty), strtok(str, empty));
  ck_assert_ptr_eq(s21_strtok(empty, delim), strtok(empty, delim));
  char dest[] = "Hell0 world\0";
  char orig[] = "Hell0 world\0";
  ck_assert_str_eq(s21_strtok(dest, " "), strtok(orig, " "));
  char dest2[] = "Hell0 world\n\0";
  char orig2[] = "Hell0 world\n\0";
  ck_assert_str_eq(s21_strtok(dest2, " "), strtok(orig2, " "));
  char dest3[] = "a\n\0";
  char orig3[] = "a\n\0";
  ck_assert_str_eq(s21_strtok(dest3, " "), strtok(orig3, " "));
  char dest4[] = " s\0";
  char orig4[] = " s\0";
  ck_assert_str_eq(s21_strtok(dest4, " "), strtok(orig4, " "));
  char dest5[] = " \0";
  char orig5[] = " \0";
  ck_assert_ptr_eq(s21_strtok(dest5, " "), strtok(orig5, " "));
  char dest6[] = "\n\0";
  char orig6[] = "\n\0";
  ck_assert_str_eq(s21_strtok(dest6, " "), strtok(orig6, " "));
  char dest7[] = "\0";
  char orig7[] = "\0";
  ck_assert_ptr_eq(s21_strtok(dest7, " "), strtok(orig7, " "));
}
END_TEST

START_TEST(sprintf_test1) {
  char str1[500] = {0};
  char str2[500] = {0};
  void *p = (void *)0x3456;
  int n1 = 0, n2 = 0;
  int r1 =
      sprintf(str1,
              "[%d] [%o] [%s] [%c] [%i] [%e] [%f] [%E] [%g] [%u] [%x] "
              "[%G] [%X] [%n] [%p] [%%] [%s]",
              25, 342, "aboba", 'a', 123, 25.34, 4325.23434, 0.0000000123,
              2.12345, 12345u, 8342, 3.12345, 1235, &n1, p, "hello my friend");
  int r2 = s21_sprintf(str2,
                       "[%d] [%o] [%s] [%c] [%i] [%e] [%f] [%E] [%g] [%u] "
                       "[%x] [%G] [%X] [%n] [%p] [%%] [%s]",
                       25, 342, "aboba", 'a', 123, 25.34, 4325.23434,
                       0.0000000123, 2.12345, 12345u, 8342, 3.12345, 1235, &n2,
                       p, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test2) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  int r2 =
      s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test3) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "% d%#+34.10g%#.10x%#15.1o%25.10s", 5, 25.3456, 1234,
                   4567, "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "% d%#+34.10g%#.10x%#15.1o%25.10s", 5, 25.3456,
                       1234, 4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test4) {
  char str1[510] = {0};
  char str2[510] = {0};
  void *p = (void *)43252342;
  int r1 = sprintf(str1, "%*.006d%#24.e%-15.20i%20p%020u", 7, 894,
                   43253242.4342, 4567899, p, 43252342u);
  int r2 = s21_sprintf(str2, "%*.006d%#24.e%-15.20i%20p%020u", 7, 894,
                       43253242.4342, 4567899, p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[510] = {0};
  char str4[510] = {0};
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(sprintf_test_d) {
  char str1[510] = {0};
  char str2[510] = {0};
  short h = 34;
  int r1 = sprintf(
      str1,
      "%03d%.*d%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2,
      "%03d%.*d%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_i) {
  char str1[510] = {0};
  char str2[510] = {0};
  short h = 34;
  int r1 = sprintf(
      str1,
      "%03i%.*i%-25.10i%-30.2i%10.12i%11i%*i%*.*i%+-25.*i%+10.2li%-11.*hi", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2,
      "%03i%.*i%-25.10i%-30.2i%10.12i%11i%*i%*.*i%+-25.*i%+10.2li%-11.*hi", 5,
      8, 7, 253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_c) {
  char str1[510] = {0};
  char str2[510] = {0};
  wchar_t c1 = 'T', c2 = 'Z';
  int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                   'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                       'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_e) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 =
      sprintf(str1, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
              2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
              11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int r2 = s21_sprintf(
      str2, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_E) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                   3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2,
                   53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                   2345678.23453242);
  int r2 = s21_sprintf(str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                       3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432,
                       10, 2, 53242.4242, 10, 456789.43242, 25,
                       1111122222.34567899, 2345678.23453242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_f) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1,
                   "%+-10.5f %+10.2f %15.15f %+*.10f %*.16f %-10.*f %25.*f "
                   "%25.f %#+10.f %*.*f",
                   2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10,
                   3456789123.43245, 2, 12345.6788, 1, 34.4325432,
                   4325678.43242, 34567.2345432, 10, 2, 34567.43244);
  int r2 = s21_sprintf(str2,
                       "%+-10.5f %+10.2f %15.15f %+*.10f %*.16f %-10.*f %25.*f "
                       "%25.f %#+10.f %*.*f",
                       2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10,
                       3456789123.43245, 2, 12345.6788, 1, 34.4325432,
                       4325678.43242, 34567.2345432, 10, 2, 34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_o) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                   12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 =
      s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_x) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20."
                   "*x%#10.*x%*.5hx%10.25lx",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*."
                       "10x%20.*x%#10.*x%*.5hx%10.25lx",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_X) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 = sprintf(str1,
                   "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*"
                   "X%#12.*X%*.8hx%14.12lX",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                       "21.*X%#12.*X%*.8hx%14.12lX",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_u) {
  char str1[510] = {0};
  char str2[510] = {0};
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu%u",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, l, h, 4294967295u);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu%u", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
      h, 4294967295u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_s) {
  char str1[510] = {0};
  char str2[510] = {0};
  wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
  int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                   "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                   "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  int r2 =
      s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                  "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_p) {
  char str1[510] = {0};
  char str2[510] = {0};
  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                   10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                       p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_percent) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_g) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(
      str1,
      "[%g] [%25g] [%-10g] [%#-15g] [%017g] [%#05.5g] [%#010.16g] "
      "[%+#8.6g] [%*.8g] [%#-10.*g] [%+#12.16g] [%*.*g] [%015g] [%0#15.10g]",
      43242.43242, 123432.43242, 1234.234242, 0001.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 7.342, 3456.3424, -324234.234);
  int r2 = s21_sprintf(
      str2,
      "[%g] [%25g] [%-10g] [%#-15g] [%017g] [%#05.5g] [%#010.16g] "
      "[%+#8.6g] [%*.8g] [%#-10.*g] [%+#12.16g] [%*.*g] [%015g] [%0#15.10g]",
      43242.43242, 123432.43242, 1234.234242, 0001.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 7.342, 3456.3424, -324234.234);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_test_G) {
  char str1[510] = {0};
  char str2[510] = {0};
  int r1 = sprintf(str1,
                   "[%G] [%25G] [%#-15G] [%017G] [%#05.5G] [%#010.16G] "
                   "[%+#8.6G] [%*.8G] [%#-10.*G] [%+#12.16G] [%*.*G]",
                   43242.43242, 123432.43242, 0001.1234, -34252.43242, 1234.5,
                   111.432534243243242, 4324.43242, 25, -3213.43242, 16,
                   -43.43242353242342, 111.24324242, 25, 5, 7.342);
  int r2 = s21_sprintf(str2,
                       "[%G] [%25G] [%#-15G] [%017G] [%#05.5G] [%#010.16G] "
                       "[%+#8.6G] [%*.8G] [%#-10.*G] [%+#12.16G] [%*.*G]",
                       43242.43242, 123432.43242, 0001.1234, -34252.43242,
                       1234.5, 111.432534243243242, 4324.43242, 25, -3213.43242,
                       16, -43.43242353242342, 111.24324242, 25, 5, 7.342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

// strrchr->
START_TEST(strrchr_normal) {
  char str1[] = "no go low";
  char str2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_find_zero) {
  char str1[] = "no go low";
  char str2 = '\0';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_with_zero) {
  char str1[] = "n g\0 low";
  char str2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_with_zero_repeated) {
  char str1[] = "no go\0 low";
  char str2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_wrong) {
  char str1[] = "dd";
  char str2 = 'n';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_zero) {
  char str1[] = "\0";
  char str2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST
// // strrchr <-

// strpbrk->
START_TEST(strpbrk_normal) {
  char str1[] = "no go low";
  char str2[] = "go";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_replace) {
  char str1[] = "no go low";
  char str2[] = "og";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_all_empty) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_find_empty) {
  char str1[] = "no go low";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_empty) {
  char str1[] = "";
  char str2[] = "no go low";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_find_zero) {
  char str1[] = "no go low";
  char str2[] = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_with_zero) {
  char str1[] = "no \0go low";
  char str2[] = "lg";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_fail) {
  char str1[] = "no go low";
  char str2[] = "z";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_zero) {
  char str1[] = "\0";
  char str2[] = "go";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST
// strpbrk <-

// strstr->
START_TEST(strstr_normal) {
  char haystack[] = "no go low";
  char needle[] = "low";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_all_empty) {
  char haystack[] = "";
  char needle[] = "";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_empty) {
  char haystack[] = "";
  char needle[] = "no go low";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_find_empty) {
  char haystack[] = "no go low";
  char needle[] = "";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_find_wrong) {
  char haystack[] = "no go low";
  char needle[] = "gsbfghgf";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_with_zero) {
  char haystack[] = "no go\0 low";
  char needle[12] = "ow";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_zero) {
  char haystack[] = "\0";
  char needle[] = "low";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST
// strstr <-

// strncpy->
START_TEST(strncpy_normal) {
  char src[] = "na ga law";
  char res[] = "ooooooooooo";
  char exp[] = "ooooooooooo";
  s21_size_t num = 5;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_empty) {
  char src[] = "";
  char res[] = "";
  char exp[] = "";
  s21_size_t num = 0;
  s21_strncpy(res, src, num);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_zero_num) {
  char src[] = "na ga law";
  char res[] = "ooooooooooo";
  char exp[] = "ooooooooooo";
  s21_size_t num = 0;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_empty_src) {
  char src[] = "";
  char res[] = "ooooooooooo";
  char exp[] = "ooooooooooo";
  s21_size_t num = 2;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
  ck_assert_int_eq(res[num - 1], 0);
}
END_TEST

START_TEST(strncpy_src_with_zero) {
  char src[] = "na \0ga law";
  char res[] = "oooooooo";
  char exp[] = "oooooooo";
  s21_size_t num = 7;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
  ck_assert_int_eq(res[num - 1], 0);
}
END_TEST

START_TEST(strncpy_res_with_zero) {
  char src[] = "na ga law";
  char res[] = "oo\0ooooooo";
  char exp[] = "oo\0ooooooo";
  s21_size_t num = 7;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_src_small) {
  char src[] = "na";
  char res[] = "oooooooo";
  char exp[] = "oooooooo";
  s21_size_t num = 7;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
  ck_assert_int_eq(res[num - 1], 0);
}
END_TEST

START_TEST(strncpy_zero) {
  char src[] = "\0";
  char res[] = "ooooooooooo";
  char exp[] = "ooooooooooo";
  s21_size_t num = 5;
  ck_assert_pstr_ne(s21_strncpy(res, src, num), s21_NULL);
  strncpy(exp, src, num);
  ck_assert_str_eq(res, exp);
}
END_TEST

// strncpy <-

// strchr->
START_TEST(strchr_normal) {
  char src[] = "no go low";
  char find = 'g';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_with_zero) {
  char src[] = "no go\0 low";
  char find = 'w';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_repeat_simb) {
  char src[] = "no go low";
  char find = 'o';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_empty) {
  char src[] = "";
  char find = 'o';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_zero) {
  char src[] = "\0";
  char find = 'o';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// strchr <-

// strcpy->
START_TEST(strcpy_normal) {
  char src[] = "no go low";
  char res[] = "zzzzzzzzz";
  char expected[] = "zzzzzzzzz";
  ck_assert_pstr_ne(s21_strcpy(res, src), s21_NULL);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
  int n = strlen(src);
  ck_assert_int_eq(res[n], 0);
}
END_TEST

START_TEST(strcpy_src_empty) {
  char src[] = "";
  char res[] = "no go low";
  char expected[] = "no go low";
  ck_assert_pstr_ne(s21_strcpy(res, src), s21_NULL);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
  int n = strlen(src);
  ck_assert_int_eq(res[n], 0);
}
END_TEST

START_TEST(strcpy_src_with_zero) {
  char src[] = "no\0go low";
  char res[] = "zzzzzzzzzzzzzz";
  char expected[] = "zzzzzzzzzzzzzz";
  ck_assert_pstr_ne(s21_strcpy(res, src), s21_NULL);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
  int n = strlen(src);
  ck_assert_int_eq(res[n], 0);
}
END_TEST

START_TEST(strcpy_res_with_zero) {
  char src[] = "no go low";
  char res[] = "zz\0zzzzzzzzzzzz";
  char expected[] = "zz\0zzzzzzzzzzzz";
  ck_assert_pstr_ne(s21_strcpy(res, src), s21_NULL);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
  int n = strlen(src);
  ck_assert_int_eq(res[n], 0);
}
END_TEST

START_TEST(strcpy_zero) {
  char src[] = "\0";
  char res[] = "zzzzzzzzz";
  char expected[] = "zzzzzzzzz";
  ck_assert_pstr_ne(s21_strcpy(res, src), s21_NULL);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
  int n = strlen(src);
  ck_assert_int_eq(res[n], 0);
}
END_TEST
// strcpy <-

// to_lower ->
START_TEST(to_lower_normal) {
  char str[] = "NORMAL";
  char expected[] = "normal";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(to_lower_low) {
  char str[] = "normal";
  char expected[] = "normal";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(to_lower_num) {
  char str[] = "1234567890?!)(&$@&*@";
  char expected[] = "1234567890?!)(&$@&*@";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(to_lower_with_zero) {
  char str[] = "NO\0RMAL";
  char expected[] = "no";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

// to_lower <-

// to_upper ->
START_TEST(to_upper_normal) {
  char str[] = "normal";
  char expected[] = "NORMAL";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(to_upper_up) {
  char str[] = "NORMAL";
  char expected[] = "NORMAL";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

START_TEST(to_upper_num) {
  char str[] = "1234567890?!)(&$@&*@";
  char expected[] = "1234567890?!)(&$@&*@";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  free(got);
}
END_TEST

// to_upper <-

// memcpy->
START_TEST(memcpy_normal) {
  char src[] = "no go low";
  s21_size_t size = 2;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memcpy(res, src, size), s21_NULL);
  memcpy(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memcpy_zero_size) {
  char src[] = "gogogog";
  s21_size_t size = 0;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memcpy(res, src, size), s21_NULL);
  memcpy(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memcpy_zero) {
  char src[] = "\0";
  s21_size_t size = 2;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memcpy(res, src, size), s21_NULL);
  memcpy(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST
// memcpy <-

// memset->
START_TEST(memset_normal) {
  char res[] = "no go lo";
  char expected[] = "no go lo";
  char replace = 's';
  s21_size_t size = 5;
  ck_assert_pstr_ne(s21_memset(res, replace, size), s21_NULL);
  memset(expected, replace, size);
  ck_assert_str_eq(res, expected);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memset_zero_size) {
  char res[] = "no go low";
  char expected[] = "no go low";
  char replace = 's';
  s21_size_t size = 0;
  ck_assert_pstr_ne(s21_memset(res, replace, size), s21_NULL);
  memset(expected, replace, size);
  ck_assert_str_eq(res, expected);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

// memset <-

// memchr->
START_TEST(memchr_normal) {
  s21_size_t size = 9;
  char str[] = "no go low";
  int find = 'g';
  ck_assert_ptr_eq(s21_memchr(str, find, size), memchr(str, find, size));
}
END_TEST

START_TEST(memchr_wrong) {
  s21_size_t size = 9;
  char str[] = "no go low";
  int find = 'z';
  ck_assert_ptr_eq(s21_memchr(str, find, size), memchr(str, find, size));
}
END_TEST

START_TEST(memchr_repeated) {
  s21_size_t size = 9;
  char str[] = "no go low";
  int find = 'o';
  ck_assert_ptr_eq(s21_memchr(str, find, size), memchr(str, find, size));
}
END_TEST

START_TEST(memchr_empty) {
  s21_size_t size = 0;
  char str[] = "";
  int find = 'o';
  ck_assert_ptr_eq(s21_memchr(str, find, size), memchr(str, find, size));
}
END_TEST

START_TEST(memchr_end) {
  s21_size_t size = 9;
  char str[] = "no go low";
  int find = 'w';
  ck_assert_ptr_eq(s21_memchr(str, find, size), memchr(str, find, size));
}
END_TEST

START_TEST(memchr_in_float) {
  float array[] = {1, 2, 3, 666, 5, 99, 100};
  s21_size_t size = sizeof(float) * 7;
  int find = 666;
  ck_assert_ptr_eq(s21_memchr(array, find, size), memchr(array, find, size));
}
END_TEST
// memchr <-

// memmove->
START_TEST(memmove_normal) {
  char src[] = "no go low";
  s21_size_t size = 2;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memmove(res, src, size), s21_NULL);
  memmove(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memmove_zero) {
  char src[] = "\0";
  s21_size_t size = 2;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memmove(res, src, size), s21_NULL);
  memmove(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memmove_zero_size) {
  char src[] = "gogogog";
  s21_size_t size = 0;
  char res[] = "aaaaaaaaaaaaa";
  char expected[] = "aaaaaaaaaaaaa";
  ck_assert_pstr_ne(s21_memmove(res, src, size), s21_NULL);
  memmove(expected, src, size);
  ck_assert_mem_eq(res, expected, size);
  ck_assert_int_ne((int)res[size], 0);
}
END_TEST

START_TEST(memmove_same) {
  char s21_src[] = "no go low";
  s21_size_t size = 2;
  char orig_src[] = "no go low";
  ck_assert_pstr_ne(s21_memmove(s21_src + 1, s21_src, size), s21_NULL);
  memmove(orig_src + 1, orig_src, size);
  ck_assert_mem_eq(s21_src, orig_src, size);
  ck_assert_int_ne((int)s21_src[size], 0);
}
END_TEST

// sscanf ->

// i

START_TEST(sscanf_i) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2, j = 2,
      k = 2, l = 2, m = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  long int al = 2, bl = 2;
  short int as = 2, bs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2, i1 = 2,
      j1 = 2, k1 = 2, l1 = 2, m1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  long int al1 = 2, bl1 = 2;
  short int as1 = 2, bs1 = 2;
  char str1[] = "0 1 562 0562 x";
  char str2[] = "582 0582 0x572 Ff 0ff";
  char str3[] = "0xff 0x zz";
  char str4[] = "0xff 666666 66 ffffff ff ";
  char str5[] = "066 0xf 066 0xf";
  int res1 = sscanf(str1, "%i%i%i%i%i", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%i%i%i%i%i", &a1, &b1, &c1, &d1, &e1);

  int res3 = sscanf(str2, "%i%i%i%i%i", &f, &g, &h, &i, &j);
  int res4 = s21_sscanf(str2, "%i%i%i%i%i", &f1, &g1, &h1, &i1, &j1);

  int res5 = sscanf(str3, "%i%i%i", &k, &l, &m);
  int res6 = s21_sscanf(str3, "%i%i%i", &k1, &l1, &m1);

  int res7 = sscanf(str4, "%6i%5i%6i%2i%6i", &p, &q, &r, &s, &t);
  int res8 = s21_sscanf(str4, "%6i%5i%6i%2i%6i", &p1, &q1, &r1, &s1, &t1);

  int res9 = sscanf(str5, "%li%li%hi%hi", &al, &bl, &as, &bs);
  int res10 = s21_sscanf(str5, "%li%li%hi%hi", &al1, &bl1, &as1, &bs1);
  //  printf("%i %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i !!!! %i %i %i %i %i
  //  !!! %i %i  %i %i\n", k, l, m, p, q, r, s, t, al, bl, as, bs); printf("%i
  //  %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i !!!! %i %i %i %i %i  !!! %i %i
  //  %i %i\n", k1, l1, m1,  p1, q1, r1, s1, t1,al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(k, k1);
  ck_assert_int_eq(l, l1);
  ck_assert_int_eq(m, m1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
  ck_assert_int_eq(res7, res8);
  ck_assert_int_eq(res9, res10);
}
END_TEST

START_TEST(sscanf_i_plus) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2, j = 2,
      k = 2, l = 2, m = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  long int al = 2, bl = 2;
  short int as = 2, bs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2, i1 = 2,
      j1 = 2, k1 = 2, l1 = 2, m1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  long int al1 = 2, bl1 = 2;
  short int as1 = 2, bs1 = 2;
  char str1[] = "+0 +1 +562 +0562 +x";
  char str2[] = "+582 +0582 +0x572 +ff +0ff";
  char str3[] = "+0xff +0x +zz";
  char str4[] = "+0xff +666666 +66 +ffffff +ff";
  char str5[] = "+66 +0xf +66 +0xf";
  int res1 = sscanf(str1, "%i%i%i%i%i", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%i%i%i%i%i", &a1, &b1, &c1, &d1, &e1);
  int res3 = sscanf(str2, "%i%i%i%i%i", &f, &g, &h, &i, &j);
  int res4 = s21_sscanf(str2, "%i%i%i%i%i", &f1, &g1, &h1, &i1, &j1);
  int res5 = sscanf(str3, "%i%i%i", &k, &l, &m);
  int res6 = s21_sscanf(str3, "%i%i%i", &k1, &l1, &m1);
  int res7 = sscanf(str4, "%6i%5i%6i%2i%6i", &p, &q, &r, &s, &t);
  int res8 = s21_sscanf(str4, "%6i%5i%6i%2i%6i", &p1, &q1, &r1, &s1, &t1);
  int res9 = sscanf(str5, "%li%li%hi%hi", &al, &bl, &as, &bs);
  int res10 = s21_sscanf(str5, "%li%li%hi%hi", &al1, &bl1, &as1, &bs1);
  //  printf("%i %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i !!!! %i %i %i %i %i
  //  !!! %i %i  %i %i\n", a, b, c, d, e, f, g, h, i, j, k, l, m, p, q, r, s,
  //  t,al, bl, as, bs); printf("%i %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i
  //  !!!! %i %i %i %i %i  !!! %i %i  %i %i\n", a1, b1, c1, d1, e1, f1, g1, h1,
  //  i1, j1, k1, l1, m1,  p1, q1, r1, s1, t1,al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(k, k1);
  ck_assert_int_eq(l, l1);
  ck_assert_int_eq(m, m1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
  ck_assert_int_eq(res7, res8);
  ck_assert_int_eq(res9, res10);
}
END_TEST

START_TEST(sscanf_i_min) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2, j = 2,
      k = 2, l = 2, m = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  long int al = 2, bl = 2;
  short int as = 2, bs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2, i1 = 2,
      j1 = 2, k1 = 2, l1 = 2, m1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  long int al1 = 2, bl1 = 2;
  short int as1 = 2, bs1 = 2;
  char str1[] = "-0 -1 -562 -0562 -x";
  char str2[] = "-582 -0582 -0x572 -ff -0ff";
  char str3[] = "-0xff -0x -zz";
  char str4[] = "-0xff -666666 -66 -ffffff -ff";
  char str5[] = "-66 -0xf -66 -0xf";
  int res1 = sscanf(str1, "%i%i%i%i%i", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%i%i%i%i%i", &a1, &b1, &c1, &d1, &e1);

  int res3 = sscanf(str2, "%i%i%i%i%i", &f, &g, &h, &i, &j);
  int res4 = s21_sscanf(str2, "%i%i%i%i%i", &f1, &g1, &h1, &i1, &j1);

  int res5 = sscanf(str3, "%i%i%i", &k, &l, &m);
  int res6 = s21_sscanf(str3, "%i%i%i", &k1, &l1, &m1);
  int res7 = sscanf(str4, "%6i%5i%6i%2i%6i", &p, &q, &r, &s, &t);
  int res8 = s21_sscanf(str4, "%6i%5i%6i%2i%6i", &p1, &q1, &r1, &s1, &t1);

  int res9 = sscanf(str5, "%li%li%hi%hi", &al, &bl, &as, &bs);
  int res10 = s21_sscanf(str5, "%li%li%hi%hi", &al1, &bl1, &as1, &bs1);
  //  printf("%i %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i !!!! %i %i %i %i %i
  //  !!! %i %i  %i %i\n", a, b, c, d, e, f, g, h, i, j, k, l, m, p, q, r, s, t,
  //  al, bl, as, bs); printf("%i %i %i %i %i !!! %i %i %i %i %i !!! %i %i %i
  //  !!!! %i %i %i %i %i  !!! %i %i  %i %i\n", a1, b1, c1, d1, e1, f1, g1, h1,
  //  i1, j1, k1, l1, m1,  p1, q1, r1, s1, t1,al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(k, k1);
  ck_assert_int_eq(l, l1);
  ck_assert_int_eq(m, m1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
  ck_assert_int_eq(res7, res8);
  ck_assert_int_eq(res9, res10);
}
END_TEST

// x

START_TEST(sscanf_x) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2,
               j = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2,
               i1 = 2, j1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "0 1 562 0562 0x572 ff 0xff 0x z 0xz";
  int res1 = sscanf(str1, "%x%x%x%x%x%x%x%x%x%x", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%x%x%x%x%x%x%x%x%x%x", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);

  char str2[] = "0xff 666666 66 ffffff ff";
  int res3 = sscanf(str2, "%6x%5x%6x%2x%6x", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6x%5x%6x%2x%6x", &p1, &q1, &r1, &s1, &t1);

  char str3[] = "66 0xf 66 0xf";
  int res5 = sscanf(str3, "%lx%lx%hx%hx", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str3, "%lx%lx%hx%hx", &al1, &bl1, &as1, &bs1);

  //  printf("%x %x %x %x %x !!! %x %x %x %x %x !!! %x %x %x %x %x  !!! %x %x %x
  //  %x\n", a, b, c, d, e, f, g, h, i, j, p, q, r, s, t, al, bl, as, bs);
  //  printf("%x %x %x %x %x !!! %x %x %x %x %x !!! %x %x %x %x %x  !!! %x %x %x
  //  %x\n", a1, b1, c1, d1, e1, f1, g1, h1, i1, j1,  p1, q1, r1, s1, t1,al1,
  //  bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_x_plus) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2,
               j = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2,
               i1 = 2, j1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "+0 +1 +562 +0562 +0x572 +ff +0xff +0x +z +0xz";
  int res1 = sscanf(str1, "%x%x%x%x%x%x%x%x%x%x", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%x%x%x%x%x%x%x%x%x%x", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);

  char str2[] = "+0xff +666666 +66 +ffffff +ff";
  int res3 = sscanf(str2, "%6x%5x%6x%2x%6x", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6x%5x%6x%2x%6x", &p1, &q1, &r1, &s1, &t1);

  char str3[] = "+66 +0xf +66 +0xf";
  int res5 = sscanf(str3, "%lx%lx%hx%hx", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str3, "%lx%lx%hx%hx", &al1, &bl1, &as1, &bs1);

  //  printf("%x %x %x %x %x !!! %x %x %x %x %x !!! %x %x %x %x %x  !!! %x %x %x
  //  %x\n", a, b, c, d, e, f, g, h, i, j, p, q, r, s, t, al, bl, as, bs);
  //  printf("%x %x %x %x %x !!! %x %x %x %x %x !!! %x %x %x %x %x  !!! %x %x %x
  //  %x\n", a1, b1, c1, d1, e1, f1, g1, h1, i1, j1,  p1, q1, r1, s1, t1,al1,
  //  bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

// X

START_TEST(sscanf_X) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, i = 2,
               j = 2, p = 2, q = 2, r = 2, s = 2, t = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2,
               i1 = 2, j1 = 2, p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "0 1 562 0562 0x572 ff 0xff 0x z 0xz";
  int res1 = sscanf(str1, "%X%X%X%X%X%X%X%X%X%X", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%X%X%X%X%X%X%X%X%X%X", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);
  char str2[] = "0xff 666666 66 ffffff ff";
  int res3 = sscanf(str2, "%6X%5X%6X%2X%6X", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6X%5X%6X%2X%6X", &p1, &q1, &r1, &s1, &t1);
  char str3[] = "66 0xf 66 0xf";
  int res5 = sscanf(str3, "%lX%lX%hX%hX", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str3, "%lX%lX%hX%hX", &al1, &bl1, &as1, &bs1);

  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

// u

START_TEST(sscanf_u) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, p = 2, q = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, q1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "0 1 562 0562 ff";
  int res1 = sscanf(str1, "%u%u%u%u%u", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%u%u%u%u%u", &a1, &b1, &c1, &d1, &e1);

  char str2[] = "66 66666 6 55555";
  int res3 = sscanf(str2, "%6u%2u%*u%*u", &p, &q);
  int res4 = s21_sscanf(str2, "%6u%2u%*u%*u", &p1, &q1);

  char str3[] = "66 66 0xf 0xf";
  int res5 = sscanf(str3, "%lu%hu%lu%hu", &al, &as, &bl, &bs);
  int res6 = s21_sscanf(str3, "%lu%hu%lu%hu", &al1, &as1, &bl1, &bs1);

  //  printf("%u %u %u %u %u !!! %u %u %u %u!!! %u %u %u %u \n", a, b, c, d, e,
  //  p, q, r,s, al, bl, as, bs); printf("%u %u %u %u %u !!! %u %u %u %u!!! %u
  //  %u %u %u \n", a1, b1, c1, d1, e1,  p1, q1, r1, s1, al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_u_plus) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, p = 2, q = 2, r = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, q1 = 2, r1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "+0 +1 +562 +0562 +ff";
  int res1 = sscanf(str1, "%u%u%u%u%u", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%u%u%u%u%u", &a1, &b1, &c1, &d1, &e1);

  char str2[] = "+66 +66666 +6";
  int res3 = sscanf(str2, "%6u%2u%9u", &p, &q, &r);
  int res4 = s21_sscanf(str2, "%6u%2u%9u", &p1, &q1, &r1);

  char str3[] = "+66 +0xf +66 +0xf";
  int res5 = sscanf(str3, "%lu%lu%hu%hu", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str3, "%lu%lu%hu%hu", &al1, &bl1, &as1, &bs1);

  //  printf("%u %u %u %u %u !!! %u %u %u !!! %u %u %u %u \n", a, b, c, d, e, p,
  //  q, r, al, bl, as, bs); printf("%u %u %u %u %u !!! %u %u %u !!! %u %u %u %u
  //  \n", a1, b1, c1, d1, e1,  p1, q1, r1, al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

// o
START_TEST(sscanf_o) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, p = 2,
               q = 2, r = 2, s = 2, t = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2,
               p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "0 1 562 0562 582 0582 0x zz";
  char str2[] = "66 66666666 88 88888888";
  char str5[] = "66 06 66 06";
  int res1 = sscanf(str1, "%o%o%o%o%o%o%o%o", &a, &b, &c, &d, &e, &f, &g, &h);
  int res2 = s21_sscanf(str1, "%o%o%o%o%o%o%o%o", &a1, &b1, &c1, &d1, &e1, &f1,
                        &g1, &h1);

  int res3 = sscanf(str2, "%6o%2o%6o%2o%10o", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6o%2o%6o%2o%10o", &p1, &q1, &r1, &s1, &t1);

  int res5 = sscanf(str5, "%lo%lo%ho%ho", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str5, "%lo%lo%ho%ho", &al1, &bl1, &as1, &bs1);
  // printf("%o %o %o %o %o %o %o %o  !!! %o %o %o %o %o!!!! %o %o %o %o\n", a,
  // b, c, d, e, f, g, h,p, q, r, s,t, al, bl, as, bs); printf("%o %o %o %o %o
  // %o %o %o  !!! %o %o %o %o %o!!!! %o %o %o %o\n\n", a1, b1, c1, d1, e1, f1,
  // g1, h1,  p1, q1, r1, s1,t1,al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_o_plus) {
  unsigned int a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, h = 2, p = 2,
               q = 2, r = 2, s = 2, t = 2;
  unsigned long int al = 2, bl = 2;
  unsigned short int as = 2, bs = 2;
  unsigned int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, h1 = 2,
               p1 = 2, q1 = 2, r1 = 2, s1 = 2, t1 = 2;
  unsigned long int al1 = 2, bl1 = 2;
  unsigned short int as1 = 2, bs1 = 2;
  char str1[] = "+0 +1 +562 +0562 +582 +0582 +0x +zz";
  char str2[] = "+66 +66666 +88 +88888888";
  char str5[] = "+66 +06 +66 +06";
  int res1 = sscanf(str1, "%o%o%o%o%o%o%o%o", &a, &b, &c, &d, &e, &f, &g, &h);
  int res2 = s21_sscanf(str1, "%o%o%o%o%o%o%o%o", &a1, &b1, &c1, &d1, &e1, &f1,
                        &g1, &h1);

  int res3 = sscanf(str2, "%6o%2o%8o%2o%9o", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6o%2o%8o%2o%9o", &p1, &q1, &r1, &s1, &t1);

  int res5 = sscanf(str5, "%lo%lo%ho%ho", &al, &bl, &as, &bs);
  int res6 = s21_sscanf(str5, "%lo%lo%ho%ho", &al1, &bl1, &as1, &bs1);
  // printf("%o %o %o %o %o %o %o %o  !!! %o %o %o %o %o!!!! %o %o %o %o\n", a,
  // b, c, d, e, f, g, h,p, q, r, s,t, al, bl, as, bs); printf("%o %o %o %o %o
  // %o %o %o  !!! %o %o %o %o %o!!!! %o %o %o %o\n\n", a1, b1, c1, d1, e1, f1,
  // g1, h1,  p1, q1, r1, s1,t1,al1, bl1, as1, bs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(f, f1);
  ck_assert_int_eq(g, g1);
  ck_assert_int_eq(h, h1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(s, s1);
  ck_assert_int_eq(t, t1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

// d

START_TEST(sscanf_d) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, p = 2, q = 2, r = 2;
  long int al = 2, bl = 2, cl = 2;
  short int as = 2, bs = 2, cs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, q1 = 2, r1 = 2;
  long int al1 = 2, bl1 = 2, cl1 = 2;
  short int as1 = 2, bs1 = 2, cs1 = 2;
  char str1[] = "0 1 562 0562 ff";
  int res1 = sscanf(str1, "%d%d%d%d%d", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%d%d%d%d%d", &a1, &b1, &c1, &d1, &e1);

  char str2[] = "66 66666 6";
  int res3 = sscanf(str2, "%6d%2d%9d", &p, &q, &r);
  int res4 = s21_sscanf(str2, "%6d%2d%9d", &p1, &q1, &r1);

  char str3[] = "66 66 0 0 c c";
  int res5 = sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al, &as, &bl, &bs, &cl, &cs);
  int res6 = s21_sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al1, &as1, &bl1, &bs1,
                        &cl1, &cs1);

  //  printf("%d %d %d %d %d !!! %d %d %d !!! %d %d %d %d %d %d\n", a, b, c, d,
  //  e, p, q, r, al, bl, cl, as, bs, cs); printf("%d %d %d %d %d !!! %d %d %d
  //  !!! %d %d %d %d %d %d\n", a1, b1, c1, d1, e1,  p1, q1, r1, al1, bl1, cl1,
  //  as1, bs1, cs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);
  ck_assert_int_eq(cl, cl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);
  ck_assert_int_eq(cs, cs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_d_plus) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, p = 2, q = 2, r = 2;
  long int al = 2, bl = 2, cl = 2;
  short int as = 2, bs = 2, cs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, q1 = 2, r1 = 2;
  long int al1 = 2, bl1 = 2, cl1 = 2;
  short int as1 = 2, bs1 = 2, cs1 = 2;
  char str1[] = "+0 +1 +562 +0562 +ff";
  int res1 = sscanf(str1, "%d%d%d%d%d", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%d%d%d%d%d", &a1, &b1, &c1, &d1, &e1);

  char str2[] = "+66 +66666 +6";
  int res3 = sscanf(str2, "%6d%2d%9d", &p, &q, &r);
  int res4 = s21_sscanf(str2, "%6d%2d%9d", &p1, &q1, &r1);

  char str3[] = "+66 +66 +0 +0 +c +c";
  int res5 = sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al, &as, &bl, &bs, &cl, &cs);
  int res6 = s21_sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al1, &as1, &bl1, &bs1,
                        &cl1, &cs1);

  //  printf("%d %d %d %d %d !!! %d %d %d !!! %d %d %d %d %d %d\n", a, b, c, d,
  //  e, p, q, r, al, bl, cl, as, bs, cs); printf("%d %d %d %d %d !!! %d %d %d
  //  !!! %d %d %d %d %d %d\n", a1, b1, c1, d1, e1,  p1, q1, r1, al1, bl1, cl1,
  //  as1, bs1, cs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);
  ck_assert_int_eq(cl, cl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);
  ck_assert_int_eq(cs, cs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_d_min) {
  int a = 2, b = 2, c = 2, d = 2, e = 2, p = 2, q = 2, r = 2;
  long int al = 2, bl = 2, cl = 2;
  short int as = 2, bs = 2, cs = 2;
  int a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, q1 = 2, r1 = 2;
  long int al1 = 2, bl1 = 2, cl1 = 2;
  short int as1 = 2, bs1 = 2, cs1 = 2;
  char str1[] = "-0 -1 -562 -0562 -ff";
  int res1 = sscanf(str1, "%d%d%d%d%d", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str1, "%d%d%d%d%d", &a1, &b1, &c1, &d1, &e1);

  char str2[] = "-66 -66666 -6";
  int res3 = sscanf(str2, "%6d%2d%9d", &p, &q, &r);
  int res4 = s21_sscanf(str2, "%6d%2d%9d", &p1, &q1, &r1);

  char str3[] = "-66 -66 -0 -0 -c -c";
  int res5 = sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al, &as, &bl, &bs, &cl, &cs);
  int res6 = s21_sscanf(str3, "%ld%hd%ld%hd%ld%hd", &al1, &as1, &bl1, &bs1,
                        &cl1, &cs1);

  //  printf("%d %d %d %d %d !!! %d %d %d !!! %d %d %d %d %d %d\n", a, b, c, d,
  //  e, p, q, r, al, bl, cl, as, bs, cs); printf("%d %d %d %d %d !!! %d %d %d
  //  !!! %d %d %d %d %d %d\n", a1, b1, c1, d1, e1,  p1, q1, r1, al1, bl1, cl1,
  //  as1, bs1, cs1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(p, p1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(r, r1);

  ck_assert_int_eq(al, al1);
  ck_assert_int_eq(bl, bl1);
  ck_assert_int_eq(cl, cl1);

  ck_assert_int_eq(as, as1);
  ck_assert_int_eq(bs, bs1);
  ck_assert_int_eq(cs, cs1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST
// sscanf ->

// p

START_TEST(sscanf_p) {
  void *a = (void *)2;
  void *b = (void *)2;
  void *c = (void *)2;
  void *d = (void *)2;
  void *e = (void *)2;
  void *f = (void *)2;
  void *g = (void *)2;
  void *h = (void *)2;
  void *i = (void *)2;
  void *j = (void *)2;
  void *p = (void *)2;
  void *q = (void *)2;
  void *r = (void *)2;
  void *s = (void *)2;
  void *t = (void *)2;

  void *a1 = (void *)2;
  void *b1 = (void *)2;
  void *c1 = (void *)2;
  void *d1 = (void *)2;
  void *e1 = (void *)2;
  void *f1 = (void *)2;
  void *g1 = (void *)2;
  void *h1 = (void *)2;
  void *i1 = (void *)2;
  void *j1 = (void *)2;
  void *p1 = (void *)2;
  void *q1 = (void *)2;
  void *r1 = (void *)2;
  void *s1 = (void *)2;
  void *t1 = (void *)2;

  char str1[] = "0 1 562 0562 0x572 0xff ff 0x z 0xz";
  int res1 = sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);

  char str2[] = "0xff 666666 66 ffffff ff";
  int res3 = sscanf(str2, "%6p%5p%6p%2p%6p", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6p%5p%6p%2p%6p", &p1, &q1, &r1, &s1, &t1);

  ck_assert_ptr_eq(a, a1);
  ck_assert_ptr_eq(b, b1);
  ck_assert_ptr_eq(c, c1);
  ck_assert_ptr_eq(d, d1);
  ck_assert_ptr_eq(e, e1);

  ck_assert_ptr_eq(f, f1);
  ck_assert_ptr_eq(g, g1);
  ck_assert_ptr_eq(h, h1);
  ck_assert_ptr_eq(i, i1);
  ck_assert_ptr_eq(j, j1);

  ck_assert_ptr_eq(p, p1);
  ck_assert_ptr_eq(q, q1);
  ck_assert_ptr_eq(r, r1);
  ck_assert_ptr_eq(s, s1);
  ck_assert_ptr_eq(t, t1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
}
END_TEST

START_TEST(sscanf_p_plus) {
  void *a = (void *)2;
  void *b = (void *)2;
  void *c = (void *)2;
  void *d = (void *)2;
  void *e = (void *)2;
  void *f = (void *)2;
  void *g = (void *)2;
  void *h = (void *)2;
  void *i = (void *)2;
  void *j = (void *)2;
  void *p = (void *)2;
  void *q = (void *)2;
  void *r = (void *)2;
  void *s = (void *)2;
  void *t = (void *)2;

  void *a1 = (void *)2;
  void *b1 = (void *)2;
  void *c1 = (void *)2;
  void *d1 = (void *)2;
  void *e1 = (void *)2;
  void *f1 = (void *)2;
  void *g1 = (void *)2;
  void *h1 = (void *)2;
  void *i1 = (void *)2;
  void *j1 = (void *)2;
  void *p1 = (void *)2;
  void *q1 = (void *)2;
  void *r1 = (void *)2;
  void *s1 = (void *)2;
  void *t1 = (void *)2;

  char str1[] = "+0 +1 +562 +0562 +0x572 +0xff +ff +0x +z +0xz";
  int res1 = sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);

  char str2[] = "+0xff +666666 +66 +ffffff +ff";
  int res3 = sscanf(str2, "%6p%5p%6p%2p%6p", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6p%5p%6p%2p%6p", &p1, &q1, &r1, &s1, &t1);

  //  printf("%p %p %p %p %p !!! %p %p %p %p %p !!! %p %p %p %p %p \n", a, b, c,
  //  d, e, f, g, h, i, j, p, q, r, s, t); printf("%p %p %p %p %p !!! %p %p %p
  //  %p %p !!! %p %p %p %p %p \n", a1, b1, c1, d1, e1, f1, g1, h1, i1, j1,  p1,
  //  q1, r1, s1, t1);
  ck_assert_ptr_eq(a, a1);
  ck_assert_ptr_eq(b, b1);
  ck_assert_ptr_eq(c, c1);
  ck_assert_ptr_eq(d, d1);
  ck_assert_ptr_eq(e, e1);

  ck_assert_ptr_eq(f, f1);
  ck_assert_ptr_eq(g, g1);
  ck_assert_ptr_eq(h, h1);
  ck_assert_ptr_eq(i, i1);
  ck_assert_ptr_eq(j, j1);

  ck_assert_ptr_eq(p, p1);
  ck_assert_ptr_eq(q, q1);
  ck_assert_ptr_eq(r, r1);
  ck_assert_ptr_eq(s, s1);
  ck_assert_ptr_eq(t, t1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
}
END_TEST

START_TEST(sscanf_p_min) {
  void *a = (void *)2;
  void *b = (void *)2;
  void *c = (void *)2;
  void *d = (void *)2;
  void *e = (void *)2;
  void *f = (void *)2;
  void *g = (void *)2;
  void *h = (void *)2;
  void *i = (void *)2;
  void *j = (void *)2;
  void *p = (void *)2;
  void *q = (void *)2;
  void *r = (void *)2;
  void *s = (void *)2;
  void *t = (void *)2;

  void *a1 = (void *)2;
  void *b1 = (void *)2;
  void *c1 = (void *)2;
  void *d1 = (void *)2;
  void *e1 = (void *)2;
  void *f1 = (void *)2;
  void *g1 = (void *)2;
  void *h1 = (void *)2;
  void *i1 = (void *)2;
  void *j1 = (void *)2;
  void *p1 = (void *)2;
  void *q1 = (void *)2;
  void *r1 = (void *)2;
  void *s1 = (void *)2;
  void *t1 = (void *)2;

  char str1[] = "-0 -1 -562 -0562 -0x572 -0xff -ff -0x -z -0xz";
  int res1 = sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a, &b, &c, &d, &e, &f, &g,
                    &h, &i, &j);
  int res2 = s21_sscanf(str1, "%p%p%p%p%p%p%p%p%p%p", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1, &h1, &i1, &j1);

  char str2[] = "-0xff -666666 -66 -ffffff -ff";
  int res3 = sscanf(str2, "%6p%5p%6p%2p%6p", &p, &q, &r, &s, &t);
  int res4 = s21_sscanf(str2, "%6p%5p%6p%2p%6p", &p1, &q1, &r1, &s1, &t1);

  ck_assert_ptr_eq(a, a1);
  ck_assert_ptr_eq(b, b1);
  ck_assert_ptr_eq(c, c1);
  ck_assert_ptr_eq(d, d1);
  ck_assert_ptr_eq(e, e1);

  ck_assert_ptr_eq(f, f1);
  ck_assert_ptr_eq(g, g1);
  ck_assert_ptr_eq(h, h1);
  ck_assert_ptr_eq(i, i1);
  ck_assert_ptr_eq(j, j1);

  ck_assert_ptr_eq(p, p1);
  ck_assert_ptr_eq(q, q1);
  ck_assert_ptr_eq(r, r1);
  ck_assert_ptr_eq(s, s1);
  ck_assert_ptr_eq(t, t1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
}
END_TEST

// %

START_TEST(sscanf_percent) {
  int a = 0, c = 0;
  char str1[] = "% %2";
  int res1 = sscanf(str1, "%%%%%d", &a);
  int res2 = s21_sscanf(str1, "%%%%%d", &c);
  ck_assert_int_eq(a, c);

  ck_assert_int_eq(res1, res2);
}
END_TEST

// e

START_TEST(sscanf_e) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, p = 2, q = 2, r = 2,
        s = 2, o = 2;
  long double al = 2, bl = 2, cl = 2, dl = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, p1 = 2, q1 = 2,
        r1 = 2, s1 = 2, o1 = 2;
  long double al1 = 2, bl1 = 2, cl1 = 2, dl1 = 2;

  char str1[] = "0 0.0 0.1e1 0.0001 562.0 0562.1 ff";
  int res1 = sscanf(str1, "%e%e%e%e%e%e%e", &a, &b, &c, &d, &e, &f, &g);
  int res2 =
      s21_sscanf(str1, "%e%e%e%e%e%e%e", &a1, &b1, &c1, &d1, &e1, &f1, &g1);

  char str2[] = "66.77 66666.6 6.1 f.1";
  int res3 = sscanf(str2, "%6e%2e%9e%2e%2e", &p, &q, &r, &s, &o);
  int res4 = s21_sscanf(str2, "%6e%2e%9e%2e%2e", &p1, &q1, &r1, &s1, &o1);

  char str3[] = "66.767 0.56 6.0 c";
  int res5 = sscanf(str3, "%Le%Le%Le%Le", &al, &bl, &cl, &dl);
  int res6 = s21_sscanf(str3, "%Le%Le%Le%Le", &al1, &bl1, &cl1, &dl1);

  //  printf("%f %f %f %f %f !!! %f %f %f !!! %f %f %f %f %f %f\n", a, b, c, d,
  //  e, f, g, p, q, r, s, o, al, bl, cl, dl); printf("%f %f %f %f %f !!! %f %f
  //  %f !!! %f %f %f %f %f %f\n", a1, b1, c1, d1, e1, f1, g1, p1, q1, r1, s1,
  //  o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_float_eq(p, p1);
  ck_assert_float_eq(q, q1);
  ck_assert_float_eq(r, r1);
  ck_assert_float_eq(s, s1);
  ck_assert_float_eq(o, o1);

  ck_assert_ldouble_eq((int)al * 1000, (int)al1 * 1000);
  ck_assert_ldouble_eq(bl, bl1);
  ck_assert_ldouble_eq(cl, cl1);
  ck_assert_ldouble_eq(dl, dl1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_e_min) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, p = 2, q = 2, r = 2,
        s = 2;
  long double al = 2, bl = 2, cl = 2, dl = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, p1 = 2, q1 = 2,
        r1 = 2, s1 = 2;
  long double al1 = 2, bl1 = 2, cl1 = 2, dl1 = 2;

  char str1[] = "-0 -0.0 -0.1e1 -0.0001 -562.0 -0562.1 -ff";
  int res1 = sscanf(str1, "%e%e%e%e%e%e%e", &a, &b, &c, &d, &e, &f, &g);
  int res2 =
      s21_sscanf(str1, "%e%e%e%e%e%e%e", &a1, &b1, &c1, &d1, &e1, &f1, &g1);

  char str2[] = "-66.77 -66666.6 -6";
  int res3 = sscanf(str2, "%6e%2e%9e%2e", &p, &q, &r, &s);
  int res4 = s21_sscanf(str2, "%6e%2e%9e%2e", &p1, &q1, &r1, &s1);

  char str3[] = "-66.767 -0.56 -6.0 -c";
  int res5 = sscanf(str3, "%Le%Le%Le%Le", &al, &bl, &cl, &dl);
  int res6 = s21_sscanf(str3, "%Le%Le%Le%Le", &al1, &bl1, &cl1, &dl1);

  // printf("%f %f %f %f %f !!! %f %f %f !!! %f %f %f %f %f %f\n", a, b, c, d,
  // e, f, g, p, q, r, s, o, al, bl, cl, dl);
  //  printf("%f %f %f %f %f !!! %f %f %f !!! %f %f %f %f %f %f\n", a1, b1, c1,
  //  d1, e1, f1, g1, p1, q1, r1, s1, o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_float_eq(p, p1);
  ck_assert_float_eq(q, q1);
  ck_assert_float_eq(r, r1);
  ck_assert_float_eq(s, s1);

  ck_assert_ldouble_eq((int)al * 1000, (int)al1 * 1000);
  ck_assert_ldouble_eq(bl, bl1);
  ck_assert_ldouble_eq(cl, cl1);
  ck_assert_ldouble_eq(dl, dl1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_e_plus) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2, p = 2, q = 2, r = 2,
        s = 2;
  long double al = 2, bl = 2, cl = 2, dl = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2, p1 = 2, q1 = 2,
        r1 = 2, s1 = 2;
  long double al1 = 2, bl1 = 2, cl1 = 2, dl1 = 2;

  char str1[] = "+0 +0.0 +0.1e1 +0.0001 +562.0 +0562.1 +ff";
  int res1 = sscanf(str1, "%e%e%e%e%e%e%e", &a, &b, &c, &d, &e, &f, &g);
  int res2 =
      s21_sscanf(str1, "%e%e%e%e%e%e%e", &a1, &b1, &c1, &d1, &e1, &f1, &g1);

  char str2[] = "+66.77 +66666.6 +6";
  int res3 = sscanf(str2, "%6e%2e%9e%2e", &p, &q, &r, &s);
  int res4 = s21_sscanf(str2, "%6e%2e%9e%2e", &p1, &q1, &r1, &s1);

  char str3[] = "+66.767 +0.56 +6.0 +c";
  int res5 = sscanf(str3, "%Le%Le%Le%Le", &al, &bl, &cl, &dl);
  int res6 = s21_sscanf(str3, "%Le%Le%Le%Le", &al1, &bl1, &cl1, &dl1);

  //  printf("%e %e %e %e %e !!! %e %e %e !!! %e %e %e %e %e %e\n", a, b, c, d,
  //  e, f, g, p, q, r, s, o, al, bl, cl, dl); printf("%e %e %e %e %e !!! %e %e
  //  %e !!! %e %e %e %e %e %e\n", a1, b1, c1, d1, e1, f1, g1, p1, q1, r1, s1,
  //  o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_float_eq(p, p1);
  ck_assert_float_eq(q, q1);
  ck_assert_float_eq(r, r1);
  ck_assert_float_eq(s, s1);

  ck_assert_ldouble_eq((int)al * 1000, (int)al1 * 1000);
  ck_assert_ldouble_eq(bl, bl1);
  ck_assert_ldouble_eq(cl, cl1);
  ck_assert_ldouble_eq(dl, dl1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
  ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(sscanf_E) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2;

  char str1[] = "0 0.0 0.1f1 0.0001 562.0 0562.1 ff";
  int res1 = sscanf(str1, "%E%E%E%E%E%E%E", &a, &b, &c, &d, &e, &f, &g);
  int res2 =
      s21_sscanf(str1, "%E%E%E%E%E%E%E", &a1, &b1, &c1, &d1, &e1, &f1, &g1);

  //  printf("%e %e %e %e %e !!! %e %e %e !!! %e %e %e %e %e %e\n", a, b, c, d,
  //  e, f, g, p, q, r, s, o, al, bl, cl, dl); printf("%e %e %e %e %e !!! %e %e
  //  %e !!! %e %e %e %e %e %e\n", a1, b1, c1, d1, e1, f1, g1, p1, q1, r1, s1,
  //  o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_f) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2;

  char str1[] = "0 0.0 0.1e1 0.0001 562.0 0562.1 ff";
  int res1 = sscanf(str1, "%f %f   %f %f %f%f%f", &a, &b, &c, &d, &e, &f, &g);
  int res2 = s21_sscanf(str1, "%f %f   %f %f %f%f%f", &a1, &b1, &c1, &d1, &e1,
                        &f1, &g1);

  //  printf("%e %e %e %e %e !!! %e %e %e !!! %e %e %e %e %e %e\n", a, b, c, d,
  //  e, f, g, p, q, r, s, o, al, bl, cl, dl); printf("%e %e %e %e %e !!! %e %e
  //  %e !!! %e %e %e %e %e %e\n", a1, b1, c1, d1, e1, f1, g1, p1, q1, r1, s1,
  //  o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_g_n) {
  float a = 2, f = 2, c = 2, d = 2, e = 2, p = 2, g = 2;
  int b = 2;

  float a1 = 2, f1 = 2, c1 = 2, d1 = 2, e1 = 2, p1 = 2, g1 = 2;
  int b1 = 2;

  char str1[] = "0 0.0 0.1e1 0.0001 562.0 0562.1 ff";
  int res1 = sscanf(str1, "%g%n%g%g%g%g%g%g", &a, &b, &c, &d, &e, &f, &g, &p);
  int res2 = s21_sscanf(str1, "%g%n%g%g%g%g%g%g", &a1, &b1, &c1, &d1, &e1, &f1,
                        &g1, &p1);

  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_int_eq(b, b1);
  ck_assert_float_eq(g, g1);
  ck_assert_float_eq(p, p1);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_G) {
  float a = 2, b = 2, c = 2, d = 2, e = 2, f = 2, g = 2;

  float a1 = 2, b1 = 2, c1 = 2, d1 = 2, e1 = 2, f1 = 2, g1 = 2;

  char str1[] = "0 0.0 0.1e1 0.0001 562.0 0562.1 ff";
  int res1 = sscanf(str1, "%G%G%G%G%G%G%G", &a, &b, &c, &d, &e, &f, &g);
  int res2 =
      s21_sscanf(str1, "%G%G%G%G%G%G%G", &a1, &b1, &c1, &d1, &e1, &f1, &g1);

  //  printf("%e %e %e %e %e !!! %e %e %e !!! %e %e %e %e %e %e\n", a, b, c, d,
  //  e, f, g, p, q, r, s, o, al, bl, cl, dl); printf("%e %e %e %e %e !!! %e %e
  //  %e !!! %e %e %e %e %e %e\n", a1, b1, c1, d1, e1, f1, g1, p1, q1, r1, s1,
  //  o1, al1, bl1, cl1, dl1);
  ck_assert_float_eq(a, a1);
  ck_assert_float_eq(b, b1);
  ck_assert_float_eq(c, c1);
  ck_assert_float_eq(d, d1);
  ck_assert_float_eq(e, e1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(g, g1);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_c) {
  char a = 110, b = 110, c = 110, d = 110, e = 110;
  char a1 = 110, b1 = 110, c1 = 110, d1 = 110, e1 = 110;
  char str[] = "g.3!b";
  int res1 = sscanf(str, "%c %c %c %c %c", &a, &b, &c, &d, &e);
  int res2 = s21_sscanf(str, "%c %c %c %c %c", &a1, &b1, &c1, &d1, &e1);

  //  printf("%c %c %c %c %c \n", a, b, c, d, e);
  //  printf("%c %c %c %c %c \n", a1, b1, c1, d1, e1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(e, e1);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_c_w) {
  wchar_t a = L'\0';
  wchar_t a1 = L'\0';
  wchar_t str[3] = L"ts";
  int res1 = sscanf((char *)str, "%lc", &a);
  int res2 = s21_sscanf((char *)str, "%lc", &a1);

  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_s) {
  wchar_t test[12] = {0};
  char a[20] = {0};
  char *p = a;
  char c[20] = {0};
  char str[] = "g.3-bb";
  int res1 = sscanf(str, "%s", p);
  int res2 = s21_sscanf(str, "%s", &c);
  ck_assert_str_eq(a, c);
  s21_sscanf((char *)L"t", "%ls", &test);
  ck_assert_int_eq(*test, L't');

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(strcmp_test) {
  char str2[4] = "Kek";
  int res1, res2;

  res1 = s21_strcmp("Lol", str2);
  res2 = strcmp("Lol", str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(strncmp_test) {
  char str1[4] = "Lol";
  char str2[4] = "Kek";
  int res1, res2;

  res1 = s21_strncmp(str1, str2, 2);
  res2 = strncmp(str1, str2, 2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(strcat_test) {
  char str1[10] = "Lol";
  char str2[10] = "Lol";
  char str3[4] = "kek";
  char *result, *result2;

  result = s21_strcat(str1, str3);
  result2 = strcat(str2, str3);
  ck_assert_str_eq(result, result2);
}
END_TEST

START_TEST(strncat_test) {
  char str[8] = "Lol";
  char str2[4] = "Kek";
  char str1[8] = "Lol";
  char *result, *result2;

  result = s21_strncat(str, str2, 2);
  result2 = strncat(str, str2, 2);
  ck_assert_str_eq(result, result2);

  result = s21_strncat(str1, str2, 2);
  result2 = strncat(str1, str2, 2);
  ck_assert_str_eq(result, result2);
}
END_TEST

START_TEST(trim_test) {
  char *str1 = "aboba";
  char *str3 = "ao";
  char *result;

  result = s21_trim(str1, str3);
  ck_assert_str_eq(result, "bob");
  free(result);
}
END_TEST

START_TEST(insert_test) {
  char *str1 = "Aboba";
  char *str2 = "kek";
  char *result = NULL;

  result = s21_insert(str1, str2, 2);
  ck_assert_str_eq(result, "Abkekoba");
  free(result);
}
END_TEST

Suite *suite_griffinp(void) {
  Suite *s = suite_create("suite");
  TCase *tc = tcase_create("griffinp_tc");

  tcase_add_test(tc, strcpy_test);
  tcase_add_test(tc, strncpy_test);
  tcase_add_test(tc, strcspn_test);
  tcase_add_test(tc, strerror_test);
  tcase_add_test(tc, strlen_test);
  tcase_add_test(tc, strpbrk_test);
  tcase_add_test(tc, strrchr_test);
  tcase_add_test(tc, strspn_test);
  tcase_add_test(tc, strstr_test);
  tcase_add_test(tc, strtok_test);
  tcase_add_test(tc, sprintf_test1);
  tcase_add_test(tc, sprintf_test2);
  tcase_add_test(tc, sprintf_test3);
  tcase_add_test(tc, sprintf_test4);
  tcase_add_test(tc, sprintf_test_d);
  tcase_add_test(tc, sprintf_test_i);
  tcase_add_test(tc, sprintf_test_c);
  tcase_add_test(tc, sprintf_test_e);
  tcase_add_test(tc, sprintf_test_E);
  tcase_add_test(tc, sprintf_test_f);
  tcase_add_test(tc, sprintf_test_o);
  tcase_add_test(tc, sprintf_test_x);
  tcase_add_test(tc, sprintf_test_X);
  tcase_add_test(tc, sprintf_test_u);
  tcase_add_test(tc, sprintf_test_s);
  tcase_add_test(tc, sprintf_test_p);
  tcase_add_test(tc, sprintf_test_percent);
  tcase_add_test(tc, sprintf_test_g);
  tcase_add_test(tc, sprintf_test_G);
  tcase_add_test(tc, strcmp_test);
  tcase_add_test(tc, strncmp_test);
  tcase_add_test(tc, strcat_test);
  tcase_add_test(tc, strncat_test);
  tcase_add_test(tc, trim_test);
  tcase_add_test(tc, insert_test);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_sscanf(void) {
  Suite *s = suite_create("suite");
  TCase *sscanf_tc = tcase_create("sscanf_tc");

  tcase_add_test(sscanf_tc, sscanf_i);
  tcase_add_test(sscanf_tc, sscanf_i_plus);
  tcase_add_test(sscanf_tc, sscanf_i_min);
  tcase_add_test(sscanf_tc, sscanf_x);
  tcase_add_test(sscanf_tc, sscanf_x_plus);
  tcase_add_test(sscanf_tc, sscanf_X);
  tcase_add_test(sscanf_tc, sscanf_u);
  tcase_add_test(sscanf_tc, sscanf_u_plus);
  tcase_add_test(sscanf_tc, sscanf_o);
  tcase_add_test(sscanf_tc, sscanf_o_plus);
  tcase_add_test(sscanf_tc, sscanf_d);
  tcase_add_test(sscanf_tc, sscanf_d_plus);
  tcase_add_test(sscanf_tc, sscanf_d_min);
  tcase_add_test(sscanf_tc, sscanf_p);
  tcase_add_test(sscanf_tc, sscanf_p_plus);
  tcase_add_test(sscanf_tc, sscanf_p_min);
  tcase_add_test(sscanf_tc, sscanf_percent);
  tcase_add_test(sscanf_tc, sscanf_e);
  tcase_add_test(sscanf_tc, sscanf_e_min);
  tcase_add_test(sscanf_tc, sscanf_e_plus);
  tcase_add_test(sscanf_tc, sscanf_E);
  tcase_add_test(sscanf_tc, sscanf_g_n);
  tcase_add_test(sscanf_tc, sscanf_G);
  tcase_add_test(sscanf_tc, sscanf_f);
  tcase_add_test(sscanf_tc, sscanf_c);
  tcase_add_test(sscanf_tc, sscanf_c_w);
  tcase_add_test(sscanf_tc, sscanf_s);

  suite_add_tcase(s, sscanf_tc);
  return s;
}

Suite *suite_memmove(void) {
  Suite *s = suite_create("suite");
  TCase *memmove_tc = tcase_create("memmove_tc");

  tcase_add_test(memmove_tc, memmove_same);
  tcase_add_test(memmove_tc, memmove_zero);
  tcase_add_test(memmove_tc, memmove_zero_size);
  tcase_add_test(memmove_tc, memmove_normal);

  suite_add_tcase(s, memmove_tc);
  return s;
}

Suite *suite_memchr(void) {
  Suite *s = suite_create("suite");
  TCase *memchr_tc = tcase_create("memchr_tc");

  tcase_add_test(memchr_tc, memchr_normal);
  tcase_add_test(memchr_tc, memchr_wrong);
  tcase_add_test(memchr_tc, memchr_repeated);
  tcase_add_test(memchr_tc, memchr_empty);
  tcase_add_test(memchr_tc, memchr_end);
  tcase_add_test(memchr_tc, memchr_in_float);

  suite_add_tcase(s, memchr_tc);
  return s;
}

Suite *suite_memcpy(void) {
  Suite *s = suite_create("suite");
  TCase *memcpy_tc = tcase_create("memcpy_tc");

  tcase_add_test(memcpy_tc, memcpy_zero_size);
  tcase_add_test(memcpy_tc, memcpy_zero);
  tcase_add_test(memcpy_tc, memcpy_normal);

  suite_add_tcase(s, memcpy_tc);
  return s;
}

Suite *suite_memset(void) {
  Suite *s = suite_create("suite");
  TCase *memset_tc = tcase_create("memset_tc");

  tcase_add_test(memset_tc, memset_normal);
  tcase_add_test(memset_tc, memset_zero_size);

  suite_add_tcase(s, memset_tc);
  return s;
}

Suite *suite_strcpy(void) {
  Suite *s = suite_create("suite");
  TCase *strcpy_tc = tcase_create("strcpy_tc");

  tcase_add_test(strcpy_tc, strcpy_res_with_zero);
  tcase_add_test(strcpy_tc, strcpy_src_with_zero);
  tcase_add_test(strcpy_tc, strcpy_src_empty);
  tcase_add_test(strcpy_tc, strcpy_normal);
  tcase_add_test(strcpy_tc, strcpy_zero);

  suite_add_tcase(s, strcpy_tc);
  return s;
}

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite");
  TCase *strchr_tc = tcase_create("strchr_tc");

  tcase_add_test(strchr_tc, strchr_normal);
  tcase_add_test(strchr_tc, strchr_with_zero);
  tcase_add_test(strchr_tc, strchr_repeat_simb);
  tcase_add_test(strchr_tc, strchr_empty);
  tcase_add_test(strchr_tc, strchr_zero);

  suite_add_tcase(s, strchr_tc);
  return s;
}

Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite");
  TCase *strncpy_tc = tcase_create("strncpy_tc");

  tcase_add_test(strncpy_tc, strncpy_normal);
  tcase_add_test(strncpy_tc, strncpy_empty);
  tcase_add_test(strncpy_tc, strncpy_zero_num);
  tcase_add_test(strncpy_tc, strncpy_empty_src);
  tcase_add_test(strncpy_tc, strncpy_src_with_zero);
  tcase_add_test(strncpy_tc, strncpy_res_with_zero);
  tcase_add_test(strncpy_tc, strncpy_src_small);
  tcase_add_test(strncpy_tc, strncpy_zero);

  suite_add_tcase(s, strncpy_tc);
  return s;
}

Suite *suite_strpbrk(void) {
  Suite *s = suite_create("suite");
  TCase *strpbrk_tc = tcase_create("strpbrk_tc");

  tcase_add_test(strpbrk_tc, strpbrk_normal);
  tcase_add_test(strpbrk_tc, strpbrk_replace);
  tcase_add_test(strpbrk_tc, strpbrk_all_empty);
  tcase_add_test(strpbrk_tc, strpbrk_find_empty);
  tcase_add_test(strpbrk_tc, strpbrk_empty);
  tcase_add_test(strpbrk_tc, strpbrk_find_zero);
  tcase_add_test(strpbrk_tc, strpbrk_with_zero);
  tcase_add_test(strpbrk_tc, strpbrk_fail);
  tcase_add_test(strpbrk_tc, strpbrk_zero);

  suite_add_tcase(s, strpbrk_tc);
  return s;
}

Suite *suite_strrchr(void) {
  Suite *s = suite_create("suite");
  TCase *strrchr_tc = tcase_create("strrchr_tc");

  tcase_add_test(strrchr_tc, strrchr_normal);
  tcase_add_test(strrchr_tc, strrchr_find_zero);
  tcase_add_test(strrchr_tc, strrchr_with_zero);
  tcase_add_test(strrchr_tc, strrchr_with_zero_repeated);
  tcase_add_test(strrchr_tc, strrchr_wrong);
  tcase_add_test(strrchr_tc, strrchr_zero);

  suite_add_tcase(s, strrchr_tc);
  return s;
}

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite");
  TCase *strstr_tc = tcase_create("strstr_tc");

  tcase_add_test(strstr_tc, strstr_normal);
  tcase_add_test(strstr_tc, strstr_all_empty);
  tcase_add_test(strstr_tc, strstr_empty);
  tcase_add_test(strstr_tc, strstr_find_empty);
  tcase_add_test(strstr_tc, strstr_find_wrong);
  tcase_add_test(strstr_tc, strstr_with_zero);
  tcase_add_test(strstr_tc, strstr_zero);

  suite_add_tcase(s, strstr_tc);
  return s;
}

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite");
  TCase *to_upper_tc = tcase_create("to_upper_tc");

  tcase_add_test(to_upper_tc, to_upper_normal);
  tcase_add_test(to_upper_tc, to_upper_up);
  tcase_add_test(to_upper_tc, to_upper_num);

  suite_add_tcase(s, to_upper_tc);
  return s;
}

Suite *suite_to_lower(void) {
  Suite *s = suite_create("suite");
  TCase *to_lower_tc = tcase_create("to_lower_tc");

  tcase_add_test(to_lower_tc, to_lower_normal);
  tcase_add_test(to_lower_tc, to_lower_low);
  tcase_add_test(to_lower_tc, to_lower_num);
  tcase_add_test(to_lower_tc, to_lower_with_zero);

  suite_add_tcase(s, to_lower_tc);
  return s;
}

int main(void) {
  int counter_failed;
  SRunner *sr = srunner_create(suite_memchr());
  srunner_add_suite(sr, suite_memmove());
  srunner_add_suite(sr, suite_memcpy());
  srunner_add_suite(sr, suite_memset());
  srunner_add_suite(sr, suite_strcpy());
  srunner_add_suite(sr, suite_strchr());
  srunner_add_suite(sr, suite_strncpy());
  srunner_add_suite(sr, suite_strpbrk());
  srunner_add_suite(sr, suite_strrchr());
  srunner_add_suite(sr, suite_strstr());
  srunner_add_suite(sr, suite_to_upper());
  srunner_add_suite(sr, suite_to_lower());
  srunner_add_suite(sr, suite_sscanf());
  srunner_add_suite(sr, suite_griffinp());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  counter_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return counter_failed == 0 ? 0 : 1;
}
