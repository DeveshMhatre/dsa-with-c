#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct Stack {
  int data;
  struct Stack *next;
} Stack;

/* Create */
Stack *Stack_create(int data);

/* Check if stack is empty */
bool Stack_isEmpty(Stack *stack);

/* Peek */
int Stack_peek(Stack *stack, int position);

/* Peek Top */
int Stack_peek_top(Stack *stack);

/* Peek Bottom */
int Stack_peek_bottom(Stack *stack);

/* Push */
Stack *Stack_push(Stack *stack, int data);

/* Pop */
int Stack_pop(Stack **stack);

/* Kill */
void Stack_kill(Stack *stack);

int main(int argc, char *argv[]) {
  Stack *stack = Stack_create(6);
  printf("Popped Element: %d\n", Stack_pop(&stack));

  stack = Stack_push(stack, 5);
  stack = Stack_push(stack, 4);
  stack = Stack_push(stack, 3);
  stack = Stack_push(stack, 2);

  printf("Top: %d\n", Stack_peek_top(stack));
  printf("Element at position 2: %d\n", Stack_peek(stack, 2));
  printf("Element at position 3: %d\n", Stack_peek(stack, 3));
  printf("Bottom: %d\n", Stack_peek_bottom(stack));

  printf("Popped Element: %d\n", Stack_pop(&stack));

  printf("Top: %d\n", Stack_peek_top(stack));
  printf("Element at position 2: %d\n", Stack_peek(stack, 2));
  printf("Bottom: %d\n", Stack_peek_bottom(stack));

  Stack_kill(stack);

  return 1;
}

/* Create */
Stack *Stack_create(int data) {
  Stack *stack = malloc(sizeof(Stack));
  check_mem(stack);

  stack->data = data;
  stack->next = NULL;

  return stack;

error:
  exit(1);
}

/* Check if stack is empty */
bool Stack_isEmpty(Stack *top) { return top == NULL; }

/* Peek */
int Stack_peek(Stack *stack, int position) {
  if (Stack_isEmpty(stack) == true) {
    log_info("Stack is empty!");
    return -1;
  }

  int index = 1;
  Stack *current = stack;

  while (current->next != NULL) {
    if (position == index) {
      return current->data;
    }

    index += 1;
    current = current->next;
  }

  if (position == index) {
    return current->data;
  }

  log_err("Invalid position!");
  return -1;
}

/* Peek Top */
int Stack_peek_top(Stack *stack) {
  if (Stack_isEmpty(stack) == true) {
    log_info("Stack is empty!");
    return -1;
  }

  return stack->data;
}

/* Peek Bottom */
int Stack_peek_bottom(Stack *stack) {
  if (Stack_isEmpty(stack) == true) {
    log_info("Stack is empty!");
    return -1;
  }

  Stack *current = stack;

  while (current->next != NULL) {
    current = current->next;
  }

  return current->data;
}

/* Push */
Stack *Stack_push(Stack *stack, int data) {
  Stack *new_top = malloc(sizeof(Stack));
  check_mem(new_top);

  new_top->data = data;
  new_top->next = stack;

  return new_top;

error:
  exit(1);
}

/* Pop */
int Stack_pop(Stack **stack) {
  if (Stack_isEmpty(*stack) == true) {
    log_info("Stack is empty!");
    return -1;
  }

  Stack *popped = *stack;
  check_mem(popped);

  int popped_data = popped->data;
  *stack = popped->next;

  free(popped);
  log_info("Popped node freed!");

  return popped_data;

error:
  exit(1);
}

/* Kill */
void Stack_kill(Stack *stack) {
  Stack *temp_node;

  while (stack->next != NULL) {
    temp_node = stack;
    stack = stack->next;

    check_mem(temp_node);
    free(temp_node);
    log_info("Node freed!");
  }

  check_mem(stack);
  free(stack);
  log_info("Last node freed!");

error:
  exit(1);
}
