#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_stack_with_arrays.c"
#include "dbg.h"

bool check_parenthisis_match(Stack *stack, char *exp);
bool match_brackets(char open, char close);

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    log_err("Provide a string as the first argument!");
    return -1;
  }

  char *query = argv[1];

  Stack *stack = Stack_create(strlen(query));

  printf("%s\n", check_parenthisis_match(stack, query) ? "true" : "false");

  Stack_kill(stack);

  return 1;
}

bool check_parenthisis_match(Stack *stack, char *exp) {
  char popped_char;
  for (int i = 0; exp[i] != '\0'; i++) {
    if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
      Stack_push(stack, exp[i]);
    }

    if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
      if (Stack_isEmpty(stack) == true) {
        return false;
      }

      popped_char = Stack_pop(stack);

      if (match_brackets(popped_char, exp[i]) == false) {
        return false;
      }
    }
  }

  return Stack_isEmpty(stack);
}

bool match_brackets(char open, char close) {
  if (open == '(' && close == ')') {
    return true;
  }

  if (open == '[' && close == ']') {
    return true;
  }

  if (open == '{' && close == '}') {
    return true;
  }

  return false;
}
