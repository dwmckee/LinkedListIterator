#ifndef C_STACK_H
#define C_STACK_H

// A pure C implementation of a linked-list stack
#include <stdbool.h>

typedef struct stack_node stack_node;
struct stack_node {
  stack_node* next;
  int payload;
};

bool stack_empty(stack_node* head);
void stack_push(int value, stack_node** head);
int stack_pop(stack_node** head);
int stack_peek(stack_node* head);
void stack_clear(stack_node **head);

#endif//C_STACK_H
