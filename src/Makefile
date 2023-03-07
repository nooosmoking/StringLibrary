GCC = gcc 
CFLAGS = -I.
LDFLAGS = -c
SOURCE := $(shell find . \( -iname "*.c" ! -iname "s21_string_test.c" \))

ifeq ($(shell uname -s),Darwin)
	LINK_LIBS  = -lcheck -lpthread -lm
else
	LINK_LIBS  = -lcheck -lgcov -lpthread -lm -lsubunit
endif

all: clean s21_string.a test

s21_string.a: ${SOURCE} clean
	$(GCC) $(CFLAGS) $(LDFLAGS) $(SOURCE) -lm
	ar rc $@  *.o
	ranlib $@

test: s21_string.a
	$(GCC) $(CFLAGS)  -fprofile-arcs -ftest-coverage --coverage ${SOURCE}  s21_string_test.c -o $@ ${LINK_LIBS}
	./$@

gcov_report: test
	gcov $(SOURCE) s21_string_test.c
	rm -rf s21_string_test.gcda s21_string_test.gcno
	find ./ -type f -iname '*.gcda'
	lcov --directory ./ --capture --output-file postgresql.info
	mkdir cov-report
	genhtml -o ./cov-report/ postgresql.info

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif
cpplint:
	python3 ../materials/linters/cpplint.py --extensions=c *.c

leaks: test
	leaks -atExit -- ./test

cppcheck:
	cppcheck *.c sscanf/*.c ssprintf/*.c sscanf/formaters/*.c;

format:
	cp .././materials/linters/.clang-format .
	clang-format  -i *.c sscanf/*.c ssprintf/*.c sscanf/formaters/*.c *.h ;

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./cov-report
	-rm -rf ./report/ && rm -rf test.dSYM
	-rm -rf s21_test
