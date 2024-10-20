#include "c_deque.h"

#include <assert.h>
#include <stdlib.h>

deque_node *init_deque_node_in_place(deque_node *node, int value)
{
  node->next = NULL;
  node->prev = NULL;
  node->payload = value;
  return node;
}

deque_node *create_deque_node_on_heap(int value)
{
  deque_node *newNode = malloc(sizeof(deque_node));
  return init_deque_node_in_place(newNode, value);
}


dl_deque *init_deque_in_place(dl_deque *deque) {
  deque->sentinal = create_deque_node_on_heap(0xDEADBEEF);
  deque->sentinal->next = deque->sentinal;
  deque->sentinal->prev = deque->sentinal;
  return deque;
}

dl_deque *create_deque_on_heap()
{
  dl_deque *newDeque = malloc(sizeof(dl_deque));
  return init_deque_in_place(newDeque);
}

// Discard all contents and sentinal, de-initializing the structure
void reap_deque(dl_deque *deque)
{
  clear_deque(deque);
  free(deque->sentinal);
  deque->sentinal = NULL;
}

// Container interface

// Discard all contents, leaving the container initialized
void clear_deque(dl_deque *deque) {
  while (!deque_empty(deque))
    deque_pop_front(deque);
  }

bool deque_empty(dl_deque *deque)
{
  return deque->sentinal->next == deque->sentinal;
  // In principle we could test prev as well for more robustness
}

void deque_push_back(int value, dl_deque *deque)
{
  deque_node* newNode = create_deque_node_on_heap(value);
  newNode->next = deque->sentinal;
  newNode->prev = deque->sentinal->prev;
  deque->sentinal->prev = newNode;
  newNode->prev->next = newNode;
}

void deque_push_front(int value, dl_deque *deque)
{
  deque_node* newNode = create_deque_node_on_heap(value);
  newNode->prev = deque->sentinal;
  newNode->next = deque->sentinal->next;
  deque->sentinal->next = newNode;
  newNode->next->prev = newNode;
}

int deque_pop_back(dl_deque *deque)
  {
  assert(deque->sentinal != NULL);
  assert(!deque_empty(deque));

  deque_node *temp = deque->sentinal->prev;
  int retVal = temp->payload;

  temp->prev->next = deque->sentinal;
  deque->sentinal->prev = temp->prev;

  free(temp);
  
  return retVal;
}

int deque_pop_front(dl_deque *deque)
{
  assert(deque->sentinal != NULL);
  assert(!deque_empty(deque));

  deque_node *temp = deque->sentinal->next;
  int retVal = temp->payload;

  temp->next->prev = deque->sentinal;
  deque->sentinal->next = temp->next;

  free(temp);
  
  return retVal;
}

int deque_peek_back(dl_deque *deque)
{
  assert(!deque_empty(deque)); 
  return deque->sentinal->prev->payload;
}
int deque_peek_front(dl_deque* deque)
{
  assert(!deque_empty(deque)); 
  return deque->sentinal->next->payload;
}
