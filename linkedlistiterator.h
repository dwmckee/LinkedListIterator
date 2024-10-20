#ifndef LINKEDLISTITERATOR_H
#define LINKEDLISTITERATOR_H

// LinkListIterator
//
// A C++ iterator for C linked lists
#include <cassert>
#include <iterator>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////
// The iterator type is templated on a functor for advancing to the next
// available node. Here are implementations of the two most common cases.
//
// Callers should provide additional implementations for list with different
// interfaces.
template <typename NODE>
struct default_next {
  auto operator()(NODE* ptr) -> NODE* { return ptr->next; } 
};

template <typename NODE>
struct default_prev {
  auto operator()(NODE* ptr) -> NODE* { return ptr->prev; } 
};

///////////////////////////////////////////////////////////////////////////////
// The iterator
template <typename NODE, class NEXT = default_next<NODE>>
class LinkedListIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = typename std::remove_const<NODE>::type;
  using pointer           = value_type*;
  using const_pointer     = const value_type*;
  using reference         = value_type&;
  using const_reference   = const value_type&;
  using next_type         = NEXT;
  
  LinkedListIterator(pointer ptr = nullptr) : _ptr(ptr) {}
  LinkedListIterator(const LinkedListIterator &) = default;
  LinkedListIterator(LinkedListIterator &&) = default;
  
  LinkedListIterator& operator=(const LinkedListIterator&) = default;
  LinkedListIterator& operator=(LinkedListIterator&&) = default;
  
  const_reference operator*() const { return *_ptr; }
  reference operator*() { return *_ptr; }
  const_pointer operator->() const { return _ptr; }
  pointer operator->() { return _ptr; }
  bool operator!=(const LinkedListIterator &other) const;
  bool operator==(const LinkedListIterator &other) const;
  
  LinkedListIterator operator++();
  LinkedListIterator operator++(int);

private:
  pointer _ptr = nullptr;
};

// TODO: implement one in terms of the other.
template <typename NODE, class NEXT>
  bool LinkedListIterator<NODE, NEXT>::operator!=(const LinkedListIterator &other) const
  {
    return (this->_ptr != other._ptr);
  }

template <typename NODE, class NEXT>
  bool LinkedListIterator<NODE, NEXT>::operator==(const LinkedListIterator &other) const
  {
    return (this->_ptr == other._ptr);
  }

template <typename NODE, class NEXT>
  auto LinkedListIterator<NODE, NEXT>::operator++() -> LinkedListIterator
{
  assert(_ptr != NULL);
  NEXT next;
  _ptr = next(_ptr);
  return _ptr;
  
}

template <typename NODE, class NEXT>
auto LinkedListIterator<NODE, NEXT>::operator++(int) -> LinkedListIterator {
  assert(_ptr != NULL);
  NODE *current = _ptr;
  NEXT next;
  _ptr = next(_ptr);
  return current;
}

///////////////////////////////////////////////////////////////////////////////
// C liked lists aren't classes and won't have [c][r]begin() and [c][r]end()
// members, but we can define ::being(NODE*) and ::end(NODE*) for our types to
// allow algorithms to work.
//
// As with the advance functor we provide default implmentations for the naive
// cases. Specializations should be provided for more elaborate lists.
//
// The "r" reverse variants should be covered by using an appropriate advance
// functor (i.e. default_prev above).
template <typename NODE, class NEXT = default_next<NODE>, typename LIST=NODE*>
LinkedListIterator<NODE, NEXT> begin(LIST list) {
  return LinkedListIterator<NODE, NEXT>(list);
}
// template <typename NODE , class NEXT = default_next<NODE>, typename LIST=NODE*>
// LinkedListIterator<const NODE, NEXT> begin(const LIST list) {
//   return LinkedListIterator<NODE, NEXT>(list);
// }
template <typename NODE, class NEXT = default_next<NODE>, typename LIST=NODE*>
LinkedListIterator<const NODE, NEXT> cbegin(const LIST list) {
  return LinkedListIterator<NODE, NEXT>(list);
}

template <typename NODE, class NEXT = default_next<NODE>, typename LIST=NODE*>
LinkedListIterator<NODE, NEXT> end(LIST list) {
  return LinkedListIterator<NODE, NEXT>(nullptr);
}
// template <typename NODE, class NEXT = default_next<NODE>, typename LIST=NODE*>
// LinkedListIterator<const NODE, NEXT> end(const LIST list) {
//   return LinkedListIterator<NODE, NEXT>(nullptr);
// }
template <typename NODE, class NEXT = default_next<NODE>, typename LIST=NODE*>
LinkedListIterator<const NODE, NEXT> cend(const LIST list) {
  return LinkedListIterator<NODE, NEXT>(nullptr);
}

#endif//LINKEDLISTITERATOR_H
