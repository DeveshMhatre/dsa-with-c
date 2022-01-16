#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct DoublyLinkedList {
  int data;
  struct DoublyLinkedList *prev;
  struct DoublyLinkedList *next;
} DoublyLinkedList;

/* Create */
DoublyLinkedList *DoublyLinkedList_create(int data);

/* Traverse */
void DoublyLinkedList_traverse(DoublyLinkedList *node, bool reverse);

/* Insert */
DoublyLinkedList *DoublyLinkedList_insert_head(DoublyLinkedList *node,
                                               int data);
DoublyLinkedList *DoublyLinkedList_insert_tail(DoublyLinkedList *node,
                                               int data);
DoublyLinkedList *DoublyLinkedList_insert_at_index(DoublyLinkedList *node,
                                                   int data, int index);

/* Kill */
void DoublyLinkedList_kill(DoublyLinkedList *node);

int main(int argc, char *argv[]) {
  DoublyLinkedList *head = DoublyLinkedList_create(38);

  head = DoublyLinkedList_insert_head(head, 37);
  DoublyLinkedList_traverse(head, false);

  head = DoublyLinkedList_insert_tail(head, 40);
  DoublyLinkedList_traverse(head, false);

  head = DoublyLinkedList_insert_at_index(head, 39, 2);
  DoublyLinkedList_traverse(head, true);

  DoublyLinkedList_kill(head);

  return 1;
}

DoublyLinkedList *DoublyLinkedList_create(int data) {
  DoublyLinkedList *head = malloc(sizeof(DoublyLinkedList));
  check_mem(head);

  head->data = data;
  head->prev = head;
  head->next = head;

  return head;

error:
  exit(1);
}

void DoublyLinkedList_traverse(DoublyLinkedList *node, bool reverse) {
  int i = 0;

  if (reverse == true) {
    DoublyLinkedList *tail = node->prev;
    node = node->prev; /* If node is not moved back, while loop won't start */

    while (node->prev != tail) {
      printf("Element at %d: %d\n", i, node->data);
      node = node->prev;
      i += 1;
    }

    printf("Element at %d: %d\n", i, node->data);
    printf("===\n");
    return;
  } else {
    DoublyLinkedList *head = node;

    while (node->next != head) {
      printf("Element at %d: %d\n", i, node->data);
      node = node->next;
      i += 1;
    }

    printf("Element at %d: %d\n", i, node->data);
    printf("===\n");
    return;
  }
}

DoublyLinkedList *DoublyLinkedList_insert_head(DoublyLinkedList *node,
                                               int data) {
  DoublyLinkedList *prev_head = node;

  DoublyLinkedList *head = DoublyLinkedList_create(data);
  check_mem(head);

  head->prev = prev_head->prev;
  head->next = prev_head;

  prev_head->prev->next = head;
  prev_head->prev = head;

  return head;

error:
  exit(1);
}

DoublyLinkedList *DoublyLinkedList_insert_tail(DoublyLinkedList *node,
                                               int data) {
  DoublyLinkedList *head = node;
  DoublyLinkedList *prev_tail = head->prev;

  DoublyLinkedList *tail = DoublyLinkedList_create(data);
  check_mem(tail);

  prev_tail->next = tail;

  tail->prev = prev_tail;
  tail->next = head;

  head->prev = tail;

  return head;

error:
  exit(1);
}

DoublyLinkedList *DoublyLinkedList_insert_at_index(DoublyLinkedList *node,
                                                   int data, int index) {
  if (index == 0) {
    node = DoublyLinkedList_insert_head(node, data);
    return node;
  }

  DoublyLinkedList *head = node;

  int i = 1;
  node = node->next;

  while (node != head) {
    if (i == index) {
      DoublyLinkedList *new_node = DoublyLinkedList_create(data);
      check_mem(new_node);

      new_node->prev = node->prev;
      new_node->next = node;

      node->prev->next = new_node;
      node->prev = new_node;

      return head;
    }

    node = node->next;
    i += 1;
  }

  log_err("Invalid index provided!");

  return head;

error:
  exit(1);
}

void DoublyLinkedList_kill(DoublyLinkedList *node) {
  DoublyLinkedList *head = node;
  DoublyLinkedList *node_to_free;

  while (node->next != head) {
    node_to_free = node;
    node = node->next;

    check_mem(node_to_free);
    free(node_to_free);

    log_info("Node freed!");
  }

  check_mem(node);
  free(node);

  log_info("Last node freed!");

error:
  exit(1);
}
