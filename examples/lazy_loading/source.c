#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *copy(const char *src) {
	char *dest = (char*)calloc(strlen(src) + 1, sizeof(char));
	strcpy(dest, src);

	return dest;
}

int main() {
	char *result = copy("Testing");
	printf("Copied: %s----\n", result);
	free(result);
	return 0;
}
