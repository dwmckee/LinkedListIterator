#ifndef TEST_INFRASTRUCTURE_H
#define TEST_INFRASTRUCTURE_H

#include <stdbool.h>
#include <stdio.h>

typedef const char* (*test_func)(void);

enum directive {
  NO_DIRECTIVE = 0,
  TODO_DIRECTIVE,
  SKIP_DIRECTIVE,
};

void initialize_tests();
void register_test(const char *desc, test_func func, int directive,
                   const char *d_explanation);
int run_tests(FILE *stream);

#define TEST_PASS
#define TEST_FAIL(MSG) do { return MSG; } while (0)

#define TEST_THAT(cond, MSG)			\
  do { if (!cond) { TEST_FAIL(MSG); } } while(0)

#define TEST_EQUAL_TYPE(A, B, TYPE)					\
  do {									\
    TYPE a = A;								\
    TYPE b = B;								\
    TEST_THAT((a==b), "Expected " #A " to equal " #B);			\
  } while (0);

#endif//TEST_INFRASTRUCTURE_H
