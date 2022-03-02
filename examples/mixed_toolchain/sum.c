#include <stdio.h>
#include "common.h"


/*
 * This function is a leaf function -- it will use the redzone
 * to store it's local variables.
 */
int sum(int a, addable ab) {
	int local_a = 48879;
	return a + ab.a + ab.b;
}

/*
 * This function is *not* a leaf function -- it will make space
 * on the stack to store it's local variables.
 */
int sum_proxy(int a, addable ab) {
	int local_a = 57005;
	return sum(a, ab);
}
