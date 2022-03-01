#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_stack_with_arrays.c"
#include "dbg.h"

/* Determine whether a character is an operator or not */
int is_operator(char ch);

/* Check the precedence of a character (BOMDAS) */
int precedence(char ch);

/* Convert an infix expression into a postfix one */
char *postfix(char *infix, Stack *stack);

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    log_err("Provide a string as the first argument!");

    return -1;
  }

  Stack *stack = Stack_create(strlen(argv[1]));

  char *postfix_expression = postfix(argv[1], stack);
  check_mem(postfix);

  printf("%s\n", postfix_expression);

  Stack_kill(stack);

  free(postfix_expression);

  return 1;

error:
  exit(1);
}

int is_operator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
    return 1;
  }

  return 0;
}

int precedence(char ch) {
  if (ch == '*' || ch == '/') {
    return 2;
  } else if (ch == '+' || ch == '-') {
    return 1;
  }

  return 0;
}

char *postfix(char *infix, Stack *stack) {
  char *postfix = malloc(sizeof(char) * strlen(infix));

  char popped_ch;

  int i = 0;

  while (infix[i] != '\0') {
    if (is_operator(infix[i]) == 0) {
      strncat(postfix, &infix[i], 1);
      i++;
    } else {
      if (precedence(infix[i]) > precedence(Stack_peek_top(stack))) {
        Stack_push(stack, infix[i]);
        i++;
      } else {
        popped_ch = Stack_pop(stack);
        strncat(postfix, " ", 1);
        strncat(postfix, &popped_ch, 1);
      }
    }
  }

  while (Stack_isEmpty(stack) != true) {
    popped_ch = Stack_pop(stack);
    strncat(postfix, " ", 1);
    strncat(postfix, &popped_ch, 1);
  }

  return postfix;
}
