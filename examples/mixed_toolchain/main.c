#include <stdio.h>
#include "common.h"

extern int sum_proxy(int a, addable ab);

int main() {
	int left_operand = 1;
	addable adb = { .a = 2, .b = 4};

	int total = sum_proxy(left_operand, adb);

	printf("total: %d\n", total);
	return 0;
}
