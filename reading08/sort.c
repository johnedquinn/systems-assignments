
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS (1<<10)

int cmp (const void * num1, const void * num2) {
	return (*(int*)num1 - *(int*)num2);
}

size_t read_numbers (FILE * stream, int numbers[], size_t n) {
	size_t i = 0;
	while ( (i < n) && (scanf("%d", & numbers[i]) != EOF) )
		i++;
	return i;
}

int main (int argc, char * argv []) {
	int numbers[MAX_NUMBERS];
	size_t numSize;

	numSize = read_numbers(stdin, numbers, MAX_NUMBERS);
	qsort((void*)numbers, numSize, sizeof(numbers[0]), cmp);
	for (size_t i = 0; i < numSize; i++) {
		printf("%d\n", numbers[i]);
	}
	return EXIT_SUCCESS;
}
