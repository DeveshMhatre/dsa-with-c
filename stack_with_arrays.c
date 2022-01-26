#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct {
  int size;
  int top;
  int *arr;
} Stack;

/* Create */
Stack *Stack_create(int size);

/* Check if stack is empty */
bool Stack_isEmpty(Stack *stack);

/* Check if stack is full */
bool Stack_isFull(Stack *stack);

/* Peek */
int Stack_peek(Stack *stack);

/* Push */
void Stack_push(Stack *stack, int item);

/* Pop */
int Stack_pop(Stack *stack);

/* Kill */
void *Stack_kill(Stack *stack);

int main(int argc, char *argv[]) {
  Stack *stack = Stack_create(5);

  Stack_push(stack, 10);

  printf("Element at Top: %d\n", Stack_peek(stack));

  printf("Popped Element: %d\n", Stack_pop(stack));

  Stack_kill(stack);
}

Stack *Stack_create(int size) {
  Stack *stack = malloc(sizeof(Stack));
  check_mem(stack);

  stack->size = size;
  stack->top = -1;
  stack->arr = malloc(size * sizeof(int));
  check_mem(stack->arr);

  return stack;

error:
  exit(0);
}

bool Stack_isEmpty(Stack *stack) {
  if (stack->top == -1) {
    return true;
  }
  return false;
}

bool Stack_isFull(Stack *stack) {
  if (stack->size == stack->top + 1) {
    return true;
  }
  return false;
}

int Stack_peek(Stack *stack) {
  if (Stack_isEmpty(stack) == true) {
    log_info("Stack empty!");
  }

  return stack->arr[stack->top];
}

void Stack_push(Stack *stack, int item) {
  if (Stack_isFull(stack) == true) {
    log_err("Stack overflow!");
    return;
  }

  stack->top += 1;
  stack->arr[stack->top] = item;
}

int Stack_pop(Stack *stack) {
  if (Stack_isEmpty(stack) == true) {
    log_err("Stack empty!");
    return stack->top;
  }

  int popped_item = stack->arr[stack->top];
  stack->top -= 1;

  return popped_item;
}

/* Kill */
void *Stack_kill(Stack *stack) {
  check_mem(stack->arr);
  free(stack->arr);
  log_info("Stack array freed!");

  check_mem(stack);
  free(stack);
  log_info("Stack freed!");

error:
  exit(0);
}
