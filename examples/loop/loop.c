#include <stdio.h>

int main() {
  int counter = 0;

  for (int looper = 0; looper < 0xdead; looper++) {
    counter++;
  }

  printf("counter: %d\n", counter);

  return 0;
}
