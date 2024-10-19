#include "c_stack.h"
#include "test_infrastructure.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

const char * failing_test()
{
  return "What is the sound of a failing test passing?";
}

const char * null_is_empty()
{
  TEST_THAT(stack_empty(NULL), "NULL stack head should evaluate empty");
  return NULL;
}

const char * not_empty_after_push()
{
  stack_node *stack = NULL;
  stack_push(42, &stack);
  TEST_THAT(!stack_empty(stack), "Stack should not be empty after push");
  stack_clear(&stack);
  return NULL;
}

const char * peak_returns_pushed_value()
{
  stack_node *stack=NULL;
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      stack_push(data[i], &stack);
      TEST_THAT((stack_peek(stack) == data[i]), "Peak didn't match push");
    }
  stack_clear(&stack);
  return NULL;
}

const char * can_pop_all_entries_to_empty()
{
  stack_node *stack = NULL;
  const int size = 9;
  for (int i=0; i<size; ++i)
    {
      stack_push(i+11, &stack);
    }
  int pop_count = 0;
  while (!stack_empty(stack))
    {
      TEST_THAT((pop_count < size), "Too many pops, isn't that thing removing nodes?");
      stack_pop(&stack);
      ++pop_count;
    }
  return NULL;
}

const char * first_in_last_out()
{
  stack_node *stack=NULL;
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      stack_push(data[i], &stack);
    }
  for (size_t i=data_size; i-->0; )
    {
      TEST_THAT((stack_pop(&stack) == data[i]), "Pop aren't reversing pushes?");
    }
  return NULL;
}


const char * performance_test()
{
  return "Too slow!";
}

int main()
{
  initialize_tests();

  register_test("NULL is empty", null_is_empty, NO_DIRECTIVE, NULL);

  register_test("Not empty after push", not_empty_after_push, NO_DIRECTIVE, 
		NULL);

  register_test("Peak returns pushed value", peak_returns_pushed_value, 
		NO_DIRECTIVE, NULL);

  register_test("Stack emptied as expected", can_pop_all_entries_to_empty, 
		NO_DIRECTIVE, NULL);

  register_test("First in last out", first_in_last_out, NO_DIRECTIVE, NULL);

  int fail_count = run_tests(stdout);
  
  return fail_count;
}
