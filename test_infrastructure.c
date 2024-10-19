#include "test_infrastructure.h"

#include <stdlib.h>

static const char *directive_strings[] = {"", "# TODO ", "# SKIP "};

typedef struct test_record {
  const char *desc;
  test_func func;
  int directive;
  const char *d_explanation;
} test_record;

typedef struct darray {
  size_t capacity;
  size_t count;
  test_record *data;
} darray;

void darray_clear(darray *dary)
{
  if (dary->data)
    {
      free(dary->data);
  }
  dary->capacity = 0;
  dary->count = 0;
  dary->data = NULL;
}

darray *darray_init(darray *dary) {
  if (dary == NULL)
    dary = malloc(sizeof(darray));
  dary->capacity = 0;
  dary->count = 0;
  dary->data = NULL;
  return dary;
}

size_t darray_size(const darray *dary)
{
  return dary->count;
}

void darray_append_copy(const test_record *tr, darray* dary)
{
  if (dary->count == dary->capacity)
    {
      int newSize = (dary->capacity<10) ? 10 : 1.4*dary->capacity;
      dary->data = realloc(dary->data, sizeof(test_record)*newSize);
      dary->capacity = newSize;
    }
  dary->data[dary->count++] = *tr;
  }

test_record *darray_item(size_t n, darray *dary)
{
  return dary->data+n;
}

static darray tests;

void initialize_tests()
{
 darray_init(&tests);
}

void register_test(const char *desc, test_func func, int directive,
                   const char *d_explanation)
{
  test_record tr = {desc, func, directive, d_explanation};
  darray_append_copy(&tr, &tests);
}

int run_tests(FILE *stream)
{
  int fail_count = 0;
  //int skip_count = 0; // Counts both SKIP and TODO
  if (stream) {
    fprintf(stream, "1..%zu\n", darray_size(&tests));
    }
  for (size_t i = 0; i < darray_size(&tests); ++i)
    {
      test_record tr = *darray_item(i, &tests);
      const char *fail_msg = NULL;
      if (tr.directive == NO_DIRECTIVE)
      {
	fail_msg = tr.func();
      }
      if (fail_msg)
        {
	  ++fail_count;
	}
      if (stream)
	{
        fprintf(stream, "%-6s %2zu - %s %s%s\n", (fail_msg ? "not ok" : "ok"),
                i, tr.desc, directive_strings[tr.directive],
                (tr.directive && tr.d_explanation ? tr.d_explanation : ""));
          if (fail_msg)
	    {
	      fprintf(stream, "%-12s%s\n", " ", fail_msg);
	    }
	}
  }
  return fail_count;
}
