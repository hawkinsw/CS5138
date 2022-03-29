#include <stdio.h>
#include <stdint.h>

typedef struct pooc {
  char a;
  uint64_t b;
  uint64_t c;
  uint32_t d;
  uint8_t e;
  uint64_t f;
  uint64_t g;
  uint64_t h;
} pooc_t;

pooc_t eeyore(char ee, uint64_t biggee, uint32_t mediumee, uint8_t smallee) {
  pooc_t result;

  result.a = ee;
  result.b = biggee;
  result.c = biggee;

  result.d = mediumee;

  result.e = smallee;

  result.f = biggee;
  result.g = biggee;
  result.h = biggee;

  return result;
}

int main() {
  pooc_t res;

  res = eeyore('a', 0xbadbeef, 0xba7, 0xf);

  return 0;
}
