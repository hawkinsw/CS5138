#include <stdio.h>

void send(const char *task) {
    int t = 5;
    printf("%s\n", task);
    return;
}

int main() {
    const char todo[] = "Just do it.";
    send(todo);
    return 0;
}