#include <stdio.h>

void swap(int *x, int *y);

int main(int argc, char *argv[]) {
  int x = 5;
  int y = 15;

  printf("Values of x and y before the swap: %d %d\n", x, y);
  swap(&x, &y);
  printf("Values of x and y after the swap: %d %d\n", x, y);

  return 1;
}

void swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
