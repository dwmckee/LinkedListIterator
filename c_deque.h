#ifndef C_DEQUE_H
#define C_DEQUE_H
// A circular, double-linked list in c

#include <stdbool.h>
#include <stdint.h>

// A pure-c implementation could hide the node definition, but to use
// the linked-list iterator, we need to have access to the raw node
// pointers
typedef struct deuqe_node deque_node;
deque_node* init_deque_node_in_place(deque_node* node, int value);
deque_node* create_deque_node_on_heap(int value);

// Out implementation will use a always present sentinal node, so we
// need a constructor/destructor
typedef struct dl_deque dl_deque;
struct dl_deque
{
  deque_node *sentinal;
};

dl_deque* init_deque_in_place(dl_deque* deque);
dl_deque* create_deque_on_heap();
void reap_deque(dl_deque* deque);

// Container interface
void clear_deque(dl_deque* deque);
bool deque_empty(dl_deque* deque);

void deque_push_back(int value, dl_deque* deque);
void deque_push_front(int value, dl_deque* deque);

int deque_pop_back(dl_deque*  deque);
int deque_pop_front(dl_deque*  deque);

int deque_peek_back(dl_deque* deque);
int deque_peek_front(dl_deque* deque);
  
/* // A class to build a circular list of dl_nodes using a sentinal */
/* // */
/* // The list that's built up is a wholely C data structure (NB: */
/* // malloc/free for allocation control). I'm just using a class here to */
/* // lump all the scaffolding together. */
/* class dl_circular */
/* { */
/* public: */
/*   using iterator = LinkedListIterator<dl_node>; */
/*   using reverse_iterator = LinkedListIterator<dl_node, default_prev<dl_node>>; */
    
/*   dl_circular() = default; */
/*   dl_circular(const dl_circular&) = delete; */
/*   dl_circular& operator=(const dl_circular&) = delete; */
/*   dl_circular(dl_circular&&) = default; */
/*   dl_circular& operator=(dl_circular&&) = default; */

/*   ~dl_circular() */
/*   { */
/*     if (_head == nullptr) */
/*       return; */
    
/*     while (_head->next != _head) */
/*       { */
/* 	pop_front(); */
/*       } */
/*     destruct_with_free(_head); */
/*   } */

/*   void pop_back() */
/*   { */
/*     if (_head == nullptr) */
/*       return; */
    
/*     const auto first_node = _head->prev; */
/*     const auto second_node = first_node->prev; */
/*     _head->prev = second_node; */
/*     second_node->next = _head; */
/*     destruct_with_free(first_node); */
/*   } */
/*   void pop_front() */
/*   { */
/*     if (_head == nullptr) */
/*       return; */
    
/*     const auto first_node = _head->next; */
/*     const auto second_node = first_node->next; */
/*     _head->next = second_node; */
/*     second_node->prev = _head; */
/*     destruct_with_free(first_node); */
/*   } */

/*   void push_back(int payload) */
/*   { */
/*     if (_head == nullptr) */
/*       init(); */
    
/*     const auto old_back = _head->prev->prev; */
/*     const auto new_node = construct_with_malloc(_head, old_back, payload); */
/*     old_back->next = new_node; */
/*     _head->prev = new_node; */
/*   } */
/*   void push_front(int payload) */
/*   { */
/*     if (_head == nullptr) */
/*       init(); */
    
/*     const auto old_front = _head->next->next; */
/*     const auto new_node = construct_with_malloc(old_front, _head, payload); */
/*     old_front->prev = new_node; */
/*     _head->next = new_node; */
/*   } */

/*   iterator begin() */
/*   { */
/*     if (_head==nullptr) */
/*       init(); */

/*     return iterator(_head->next); */
/*   } */
/*   iterator end() */
/*   { */
/*     if (_head == nullptr) */
/*       init(); */

/*     return iterator(_head); */
/*   } */

/*   reverse_iterator rbegin() */
/*   { */
/*     if (_head == nullptr) */
/*       init(); */

/*     return reverse_iterator(_head->prev); */
/*   } */
/*   reverse_iterator rend() */
/*   { */
/*     if (_head == nullptr) */
/*       init(); */

/*     return reverse_iterator(_head); */
/*   } */

/* private: */
/*   void init() */
/*   { */
/*     _head = construct_with_malloc(nullptr, nullptr, 0xDEADBEEF); */
/*     _head->next = _head->prev = _head; */
/*   } */

/*   dl_node* construct_with_malloc(dl_node* next, dl_node* prev, int payload) */
/*   { */
/*     const auto buffer = calloc(sizeof(dl_node), 1); */
/*     dl_node* ptr = new (buffer) dl_node(); */
/*     ptr->next = next; */
/*     ptr->prev = prev; */
/*     ptr->payload = payload; */

/*     return ptr; */
/*   } */
/*   void destruct_with_free(dl_node* ptr) */
/*   { */
/*     free(ptr); */
/*   } */
  
/*   dl_node* _head = nullptr; */
/* }; */
#endif//C_DEQUE_H
