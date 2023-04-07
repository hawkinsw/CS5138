#include <stdio.h>

double multiply(int a, double b) {
    return a*b;
}

int main() { 
    volatile double result = multiply(5, 17);
    return 0;
}