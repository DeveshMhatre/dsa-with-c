#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct {
  int total_size;
  int used_size;
  int *list;
} NewArray;

/* Constructor to create NewArray object */
NewArray *NewArray_create(int t_size);

/* Populate the list in the NewArray object */
int NewArray_populate(NewArray *arr, int length);

/* Print all elements in the list of the NewArray object */
int NewArray_traversal(NewArray *arr);

/* Increase size of the list in the NewArray object */
int NewArray_append(NewArray *arr);

/* Insert an element in the list of the NewArray object */
int NewArray_insert(NewArray *array, int element, int index);

/* Delete an element in the list of the NewArray object */
int NewArray_delete(NewArray *array, int index);

/* Release memory allocated to NewArray object */
int NewArray_kill(NewArray *array);

int main(int argc, char *argv[]) {
  NewArray *arr = NewArray_create(6);

  NewArray_populate(arr, 5);

  NewArray_insert(arr, 13, 5);

  NewArray_insert(arr, 14, 6);

  NewArray_delete(arr, 5);

  printf("Total Space: %d\n", arr->total_size);
  printf("Used Space: %d\n", arr->used_size);

  NewArray_kill(arr);
  return 0;
}

NewArray *NewArray_create(int t_size) {
  NewArray *newArr = malloc(sizeof(NewArray));
  check_mem(newArr);

  newArr->list = malloc(t_size * sizeof(int));
  check_mem(newArr->list);

  newArr->total_size = t_size;
  newArr->used_size = 0;
  return newArr;

error:
  exit(1);
}

int NewArray_populate(NewArray *arr, int length) {
  if (length > arr->total_size) {
    log_info("Size increased to add %d elements in the array.", length);
    NewArray_append(arr);
  }

  for (int i = 0; i < length; i++) {
    printf("Enter element to be inserted at index[%d]: ", i);
    scanf("%d", &arr->list[i]);
    arr->used_size += 1;
  }

  NewArray_traversal(arr);

  return 1;
}

int NewArray_traversal(NewArray *arr) {
  printf("[%d, ", arr->list[0]);
  for (int i = 1; i < arr->used_size - 1; i++) {
    printf("%d, ", arr->list[i]);
  }
  printf("%d]\n", arr->list[arr->used_size - 1]);

  return 1;
}

int NewArray_append(NewArray *arr) {
  arr->total_size *= 2;

  arr->list = realloc(arr->list, arr->total_size * sizeof(int));
  check_mem(arr->list);

  printf("Total Size: %d\n", arr->total_size);

  return 1;

error:
  exit(1);
}

int NewArray_insert(NewArray *array, int element, int index) {
  if (index > array->used_size) {
    log_err("Insert operation out of bounds");
    return -1;
  }

  if (array->used_size == array->total_size) {
    log_info("Size increased to add an additional element to the list.");
    NewArray_append(array);
  }

  for (int i = array->used_size; i > index; i--) {
    array->list[i] = array->list[i - 1];
  }

  array->list[index] = element;
  array->used_size += 1;

  NewArray_traversal(array);

  return 1;
}

int NewArray_delete(NewArray *array, int index) {
  if (index > array->used_size - 1) {
    log_err("Delete operation out of bounds");
    return -1;
  }
  for (int i = index; i < array->used_size - 1; i++) {
    array->list[i] = array->list[i + 1];
  }

  array->used_size -= 1;
  NewArray_traversal(array);

  return 1;
}

int NewArray_kill(NewArray *array) {
  check_mem(array->list);
  free(array->list);
  /* printf("Released memory reserved for list.\n"); */

  check_mem(array);
  free(array);
  /* printf("Released memory reserved for array.\n"); */

  return 1;

error:
  exit(1);
}
