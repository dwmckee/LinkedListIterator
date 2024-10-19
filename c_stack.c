#include "c_stack.h"

#include <assert.h>
#include <stdlib.h>

struct stack_node {
  stack_node* next;
  int payload;
};

stack_node* create_node(int payload)
{
  stack_node* node = calloc(sizeof(stack_node),1);
  node->payload = payload;
  return node;
}

void reap_node(stack_node**node)
{
  if (*node == NULL)
    return;

  free(*node);
  *node = NULL;
}

bool stack_empty(stack_node* head)
{
  return head == NULL;
}

void stack_push(int value, stack_node** head)
{
  stack_node* new_node = create_node(value);
  new_node->next = *head;
  *head = new_node;
  return;
}

int stack_pop(stack_node** head)
{
  assert(head != NULL);
  assert(*head != NULL);
  int value = (*head)->payload;
  stack_node* next_node = (*head)->next;
  reap_node(head);
  *head = next_node;
  return value;
}

int stack_peek(stack_node* head)
{
  assert(head != NULL);
  return head->payload;
}

void stack_clear(stack_node **head)
{
  while (!stack_empty(*head))
    stack_pop(head);
}
