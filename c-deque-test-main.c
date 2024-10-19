#include "c_deque.h"
#include "test_infrastructure.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

const char * initialized_deque_is_empty()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  TEST_THAT(deque_empty(&deque), "Freshly initialized evaluated non-empty");
  reap_deque(&deque);
  return NULL;
}

const char * not_empty_after_push_front()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  deque_push_front(42, &deque);
  TEST_THAT(!deque_empty(&deque), "Evaluated non-empty after push");
  reap_deque(&deque);
  return NULL;
}

const char * not_empty_after_push_back()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  deque_push_back(42, &deque);
  TEST_THAT(!deque_empty(&deque), "Evaluated non-empty after push");
  reap_deque(&deque);
  return NULL;
}

const char * peak_front_returns_pushed_value()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      deque_push_front(data[i], &deque);
      TEST_THAT((deque_peek_front(&deque) == data[i]), "Peak didn't match push");
    }
  reap_deque(&deque);
  return NULL;
}

const char * peak_back_returns_pushed_value()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      deque_push_back(data[i], &deque);
      TEST_THAT((deque_peek_back(&deque) == data[i]), "Peak didn't match push");
    }
  reap_deque(&deque);
  return NULL;
}

const char * can_pop_front_to_empty()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int size = 9;
  for (int i=0; i<size; ++i)
    {
      deque_push_front(i+11, &deque);
    }
  int pop_count = 0;
  while (!deque_empty(&deque))
    {
      TEST_THAT((pop_count < size), "Too many pops, isn't that thing removing nodes");
      deque_pop_front(&deque);
      ++pop_count;
    }
  reap_deque(&deque);
  return NULL;
}

const char * can_pop_back_to_empty()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int size = 9;
  for (int i=0; i<size; ++i)
    {
      deque_push_back(i+11, &deque);
    }
  int pop_count = 0;
  while (!deque_empty(&deque))
    {
      TEST_THAT((pop_count < size), "Too many pops, isn't that thing removing nodes");
      deque_pop_back(&deque);
      ++pop_count;
    }
  reap_deque(&deque);
  return NULL;
}

const char * first_in_last_out()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      deque_push_front(data[i], &deque);
    }
  for (size_t i=data_size; i-->0; )
    {
      TEST_THAT((deque_pop_front(&deque) == data[i]), "Same-end pops aren't reversing order");
    }
  reap_deque(&deque);
  return NULL;
}

const char * first_in_first_out()
{
  dl_deque deque;
  init_deque_in_place(&deque);
  const int data[] = {2,3,5,7,11,13,19};
  const size_t data_size = sizeof(data)/(sizeof(data[0]));
  for (size_t i=0; i<data_size; ++i)
    {
      deque_push_front(data[i], &deque);
    }
  for (size_t i=data_size; i-->0; )
    {
      TEST_THAT((deque_pop_back(&deque) == data[i]), "Oposite-end pops aren't maintaining order");
    }
  reap_deque(&deque);
  return NULL;
}


int main()
{
  initialize_tests();

  register_test("Empty at initialization", initialized_deque_is_empty, NO_DIRECTIVE, NULL);
  register_test("Not empty after push front", not_empty_after_push_front, NO_DIRECTIVE, NULL);
  register_test("Not empty after push back", not_empty_after_push_back, NO_DIRECTIVE, NULL);
  register_test("Peak returns pushed value", peak_front_returns_pushed_value, NO_DIRECTIVE, NULL);
  register_test("Peak returns pushed value", peak_back_returns_pushed_value, NO_DIRECTIVE, NULL);
  register_test("Can pop front to empty", can_pop_front_to_empty, NO_DIRECTIVE, NULL);
  register_test("Can pop back to empty", can_pop_back_to_empty, NO_DIRECTIVE, NULL);
  register_test("First in last out", first_in_last_out, NO_DIRECTIVE, NULL);
  register_test("First in first out", first_in_last_out, NO_DIRECTIVE, NULL);
  int fail_count = run_tests(stdout);
  
  return fail_count;
}
