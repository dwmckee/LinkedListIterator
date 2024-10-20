#include "linkedlistiterator.h"
#include <stdlib.h>

extern "C" {
#include "c_deque.h"
#include "c_stack.h"
}

#include <algorithm>
#include <cstdlib>
#include <iostream>

// Can you traverse the container using the iterators
template <typename ITER>
bool manual_iteration(ITER it, size_t count, const int *comp_ary) {
  const auto end_it = end<typename ITER::value_type,
			  typename ITER::next_type>(&(*it));

  size_t i = count;
  while (it != end_it)
    {
      --i;
      if (it->payload != comp_ary[i])
        return false;

      ++it;
  }
  return (i == 0);

}

// Can you use the container with (at elast some of) the algorithms header
template <typename ITER, typename VALUE_T>
ITER find_in_list(ITER begin, ITER end, VALUE_T val)
{
  auto it = std::find_if(
      begin, end, [val](const stack_node &n) { return n.payload == val; });
  return it;
}

///////////////////////////////////////////////////////////////////////////////
// Try some iterator operation on the naive stack
bool test_stack()
{
  const int test_data[] = {2, 3, 5, 7, 11, 13};
  const size_t test_data_count = sizeof(test_data) / sizeof(test_data[0]);

  std::cout << "Testing against the naive stack..." << std::endl;
  stack_node *stack = nullptr;
  assert(begin<stack_node>(stack) == end<stack_node>(stack));
  for (size_t i = 0; i < test_data_count; ++i) {
    stack_push(test_data[i], &stack);
  }
  assert(begin<stack_node>(stack) != end<stack_node>(stack));

  assert(manual_iteration(LinkedListIterator<stack_node>(stack),
                          test_data_count, test_data));

  const auto it_13 = find_in_list(LinkedListIterator<stack_node>(stack),
				  LinkedListIterator<stack_node>(nullptr), 13);
  assert(it_13 == stack);

  const auto it_9 = find_in_list(LinkedListIterator<stack_node>(stack),
				  LinkedListIterator<stack_node>(nullptr), 9);
  assert(it_9 == LinkedListIterator<stack_node>(nullptr));

  auto it_2 = find_in_list(LinkedListIterator<stack_node>(stack),
				  LinkedListIterator<stack_node>(nullptr), 2);
  assert(it_2 != stack);
  assert(it_2 != LinkedListIterator<stack_node>(nullptr));
  assert(++it_2 == LinkedListIterator<stack_node>(nullptr));

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// The various default operations on won't work for the deque because it have a
// more complex structure (exception the default next and previous functors
// _will_ work). To that end, we write specialized templates here before
// defining the deque tests
template <>
LinkedListIterator<deque_node, default_next<deque_node>>
begin(dl_deque list) {
  default_next<deque_node> next;
  return LinkedListIterator<deque_node, default_next<deque_node>>(next(list.sentinal));
}

template <>
LinkedListIterator<deque_node, default_next<deque_node>> end(dl_deque list) {
  return LinkedListIterator<deque_node, default_next<deque_node>>(list.sentinal);
}



///////////////////////////////////////////////////////////////////////////////
// Try operations against the deque
bool test_deque()
{
  const int test_data[] = {2, 3, 5, 7, 11, 13};
  const size_t test_data_count = sizeof(test_data) / sizeof(test_data[0]);

  std::cout << "Testing against the more structured deque..." << std::endl;
  dl_deque deque;
  init_deque_in_place(&deque);
  assert(begin<deque_node>(deque) == end<deque_node>(deque));
  for (size_t i = 0; i < test_data_count; ++i) {
    deque_push_front(test_data[i], &deque);
  }
  assert(begin<deque_node>(deque) != end<deque_node>(deque));
  
  return true;
}

int main()
{
  return ( test_stack() && test_deque() ) ? EXIT_SUCCESS : EXIT_FAILURE;
}
