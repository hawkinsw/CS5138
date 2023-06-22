#include <stdio.h>
#include <stdint.h>

int add4(uint64_t one, uint64_t two, uint64_t three, uint64_t four) {
    return one + two + three + four;
}

int main() {
    int sum = add4(5, 10, 15, 20);
    printf("sum: %d\n", sum);
    return 0;
}