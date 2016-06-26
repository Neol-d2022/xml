#include <stdio.h>

#include "vector.h"

static int cmp(const void *a, const void *b) {
	int *c = *((int**)a);
	int *d = *((int**)b);
	
	return *c - *d;
}

int main(void) {
	VECTOR *v = CreateVector_VECTOR(sizeof(int));
	int test;
	unsigned int test2;
	
	for(test = 321; test > 0; test -= 1) {
		AddToVector_VECTOR(v, &test);
		printf("%d added.\n", test);
	}
	
	VectorSort_void(v, cmp);
	printf("Size = %u\nCount = %u\nCapacity = %u\n", VectorGetElementSize_uint(v), VectorGetElementCount_uint(v), VectorGetCapacity_uint(v));
	
	for(test2 = 0; test2 < VectorGetElementCount_uint(v); test2 += 1) {
		printf("%d\n", *((int*)VectorAt_void(v, test2)));
	}
	
	DestroyVector_void(v, 0);
	
	return 0;
}