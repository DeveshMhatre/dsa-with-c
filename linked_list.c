#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

typedef struct LinkedList {
  int data;
  struct LinkedList *next;
} LinkedList;

/* Constructor for creating a LinkedList object */
LinkedList *LinkedList_create(int data);

/* Traverse all the nodes in a LinkedList object */
void LinkedList_traverse(LinkedList *node);

/* Insert a new node at the beginning of a LinkedList object */
LinkedList *LinkedList_insert_at_head(LinkedList *node, int data);

/* Insert a new node in between two nodes in a LinkedList object */
LinkedList *LinkedList_insert_in_between(LinkedList *node, int data, int index);

/* Insert a new node after another node in a LinkedList object */
LinkedList *LinkedList_insert_after_node(LinkedList *head,
                                         LinkedList *before_node, int data);

/* Insert a new node at the end of a LinkedList object */
LinkedList *LinkedList_insert_at_tail(LinkedList *node, int data);

/* Delete the head of a LinkedList object */
LinkedList *LinkedList_delete_head(LinkedList *node);

/* Delete a node in between two nodes of a LinkedList object */
LinkedList *LinkedList_delete_node_in_between(LinkedList *node, int index);

/* Delete a node with a specific value in a LinkedList object */
LinkedList *LinkedList_delete_a_specific_node(LinkedList *node, int data);

/* Delete the tail of a LinkedList object */
LinkedList *LinkedList_delete_tail(LinkedList *node);

/* Free memory reserved for a LinkedList object */
void LinkedList_kill(LinkedList *node);

int main(int argc, char *argv[]) {
  LinkedList *head = LinkedList_create(9);

  head = LinkedList_insert_at_head(head, 6);
  head = LinkedList_insert_at_tail(head, 10);
  head = LinkedList_insert_in_between(head, 8, 1);
  head = LinkedList_insert_after_node(head, head, 7);

  LinkedList_traverse(head);

  head = LinkedList_delete_head(head);
  head = LinkedList_delete_node_in_between(head, 2);
  head = LinkedList_delete_a_specific_node(head, 8);
  head = LinkedList_delete_tail(head);

  LinkedList_traverse(head);

  LinkedList_kill(head);

  return 1;
}

LinkedList *LinkedList_create(int data) {
  LinkedList *node = malloc(sizeof(LinkedList));
  check_mem(node);

  node->data = data;
  node->next = NULL;

  return node;

error:
  exit(1);
}

void LinkedList_traverse(LinkedList *node) {
  printf("[%d", node->data);
  node = node->next;

  if (node == NULL) {
    printf("]\n");
    return;
  }
  printf(", ");

  while (node->next != NULL) {
    printf("%d, ", node->data);
    node = node->next;
  }

  printf("%d]\n", node->data);
}

LinkedList *LinkedList_insert_at_head(LinkedList *node, int data) {
  LinkedList *inserted_node = LinkedList_create(data);
  check_mem(inserted_node);

  LinkedList *head = inserted_node;

  inserted_node->next = node;

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_insert_in_between(LinkedList *node, int data,
                                         int index) {
  LinkedList *inserted_node = LinkedList_create(data);
  check_mem(inserted_node);

  if (index == 0) {
    log_err("Index cannot be 0. To replace the head node, use insert_at_head "
            "method!");
    exit(1);
  }

  LinkedList *head = node;
  int i = 0;

  while (i < index - 1) {
    node = node->next;
    i += 1;

    if (node->next == NULL) {
      log_err("To insert a node at the tail, use insert_at_tail method!");
      exit(1);
    }
  }

  inserted_node->next = node->next;
  node->next = inserted_node;

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_insert_after_node(LinkedList *head, LinkedList *node,
                                         int data) {
  LinkedList *inserted_node = LinkedList_create(data);
  check_mem(inserted_node);

  inserted_node->next = node->next;
  node->next = inserted_node;

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_insert_at_tail(LinkedList *node, int data) {
  LinkedList *inserted_node = LinkedList_create(data);
  check_mem(inserted_node);

  LinkedList *head = node;

  while (node->next != NULL) {
    node = node->next;
  }

  node->next = inserted_node;

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_delete_head(LinkedList *node) {
  LinkedList *head = node->next;

  check_mem(node);
  free(node);

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_delete_node_in_between(LinkedList *node, int index) {
  if (index == 0) {
    log_err("Index cannot be 0. To delete the head, use delete_head method!");
    exit(1);
  }

  LinkedList *head = node;
  check_mem(head);

  int i = 0;
  while (i != index - 1) {
    node = node->next;
    i += 1;

    if (node->next->next == NULL) {
      log_err("To delete the tail, use delete_tail method!");
      exit(1);
    }
  }

  LinkedList *node_to_be_deleted = node->next;
  check_mem(node_to_be_deleted);

  node->next = node_to_be_deleted->next;

  free(node_to_be_deleted);

  return head;

error:
  exit(1);
}

LinkedList *LinkedList_delete_a_specific_node(LinkedList *node, int data) {
  LinkedList *head = node;
  check_mem(head);

  /* Check if head is the node to be deleted */
  if (node->data == data) {
    head = LinkedList_delete_head(node);
    return head;
  }
  /* Check if the node to the right of head is the one to be deleted */
  /* This is to make sure that the pointer in head is updated */
  else if (node->next->data == data) {
    LinkedList *node_to_be_deleted = node->next;
    check_mem(node_to_be_deleted);

    node->next = node_to_be_deleted->next;

    free(node_to_be_deleted);

    return node;
  } else {
    node = node->next;
    while (node != NULL && node->next != NULL) {
      if (node->next->data == data) {
        LinkedList *node_to_be_deleted = node->next;
        check_mem(node_to_be_deleted);

        node->next = node_to_be_deleted->next;

        free(node_to_be_deleted);

        return head;
      }
      node = node->next;
    }
  }

  printf("No node with data %d found.\n", data);
  return head;

error:
  exit(1);
}

LinkedList *LinkedList_delete_tail(LinkedList *node) {
  LinkedList *head = node;
  check_mem(head);

  if (node->next == NULL) {
    log_err(
        "Cannot perform delete_tail if there is only one node in the list!");
    exit(1);
  }

  while (node->next->next != NULL) {
    node = node->next;
  }

  LinkedList *node_to_be_deleted = node->next;
  check_mem(node_to_be_deleted);

  node->next = NULL;

  free(node_to_be_deleted);

  return head;

error:
  exit(1);
}

void LinkedList_kill(LinkedList *node) {
  LinkedList *tempNode;

  while (node != NULL) {
    tempNode = node;
    node = node->next;

    check_mem(tempNode);
    free(tempNode);
    printf("Node freed!\n");
  }
  printf("Linked List freed!\n");

error:
  exit(1);
}
