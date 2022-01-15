#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct CircularLinkedList {
  int data;
  struct CircularLinkedList *next;
} CircularLinkedList;

/* Create */
CircularLinkedList *CircularLinkedList_create(int data);

/* Traverse */
void CircularLinkedList_traverse(CircularLinkedList *node);

/* Insert */
CircularLinkedList *CircularLinkedList_insert_head(CircularLinkedList *node,
                                                   int data);
CircularLinkedList *CircularLinkedList_insert_tail(CircularLinkedList *node,
                                                   int data);
CircularLinkedList *CircularLinkedList_insert_at_index(CircularLinkedList *node,
                                                       int data, int index);

/* Reverse */
CircularLinkedList *CircularLinkedList_reverse(CircularLinkedList *head);

/* Kill */
void CircularLinkedList_kill(CircularLinkedList *node);

int main(int argc, char *argv[]) {
  CircularLinkedList *head = CircularLinkedList_create(18);
  CircularLinkedList_traverse(head);

  head = CircularLinkedList_insert_head(head, 16);
  CircularLinkedList_traverse(head);

  head = CircularLinkedList_insert_tail(head, 19);
  CircularLinkedList_traverse(head);

  head = CircularLinkedList_insert_at_index(head, 17, 1);
  CircularLinkedList_traverse(head);

  head = CircularLinkedList_reverse(head);
  CircularLinkedList_traverse(head);

  CircularLinkedList_kill(head);
  return 1;
}

CircularLinkedList *CircularLinkedList_create(int data) {
  CircularLinkedList *head = malloc(sizeof(CircularLinkedList));
  check_mem(head);

  head->data = data;
  head->next = head;

  return head;

error:
  exit(1);
}

void CircularLinkedList_traverse(CircularLinkedList *node) {
  CircularLinkedList *head = node;

  int i = 0;
  while (node->next != head) {
    printf("Element at %d: %d\n", i, node->data);
    node = node->next;
    i += 1;
  }
  printf("Element at %d: %d\n", i, node->data);

  printf("===\n");
}

CircularLinkedList *CircularLinkedList_insert_head(CircularLinkedList *node,
                                                   int data) {
  CircularLinkedList *prev_head = node;

  /* New head, pointing to prev head */
  CircularLinkedList *head = CircularLinkedList_create(data);
  check_mem(head);

  head->next = prev_head;

  while (node->next != prev_head) {
    node = node->next;
  }

  node->next = head;

  return head;

error:
  exit(1);
}

CircularLinkedList *CircularLinkedList_insert_tail(CircularLinkedList *node,
                                                   int data) {
  CircularLinkedList *head = node;

  CircularLinkedList *tail = CircularLinkedList_create(data);
  check_mem(tail);

  while (node->next != head) {
    node = node->next;
  }

  node->next = tail;
  tail->next = head;

  return head;

error:
  exit(1);
}

CircularLinkedList *CircularLinkedList_insert_at_index(CircularLinkedList *node,
                                                       int data, int index) {
  CircularLinkedList *head = node;
  CircularLinkedList *prev_node;

  if (index == 0) {
    head = CircularLinkedList_insert_head(head, data);
    return head;
  }

  int i = 1;

  prev_node = node;
  node = node->next;

  CircularLinkedList *new_node = CircularLinkedList_create(data);
  check_mem(new_node);

  while (node->next != head) {
    if (i == index) {
      prev_node->next = new_node;
      new_node->next = node;

      return head;
    }

    prev_node = node;
    node = node->next;
    i += 1;
  }

  if (i == index) {
    prev_node->next = new_node;
    new_node->next = node;

    return head;
  }

  /* In case the index is out of bounds, insert the new node as tail */
  free(new_node);
  head = CircularLinkedList_insert_tail(head, data);

  return head;

error:
  exit(1);
}

CircularLinkedList *CircularLinkedList_reverse(CircularLinkedList *head) {
  CircularLinkedList *prev_node = head;
  CircularLinkedList *node = head->next;
  CircularLinkedList *next_node = node->next;

  while (next_node != head) {
    node->next = prev_node;
    prev_node = node;
    node = next_node;
    next_node = next_node->next;
  }

  node->next = prev_node;
  head->next = node;
  head = node;

  return head;
}

void CircularLinkedList_kill(CircularLinkedList *node) {
  CircularLinkedList *head = node;
  CircularLinkedList *node_to_be_deleted;

  while (node->next != head) {
    check_mem(node);
    node_to_be_deleted = node;
    node = node->next;
    free(node_to_be_deleted);

    log_info("Node freed!");
  }

  check_mem(node);
  free(node);
  log_info("Last node freed!");

error:
  exit(1);
}
