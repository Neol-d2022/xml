#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_VECTOR_SIZE 8u

typedef struct {
	unsigned int elementSize_uint;
	unsigned int count_uint;
	unsigned int capacitiy_uint;
	void **base_void;
} VECTOR;

typedef void (*FP_DEALLOC)(void *);
typedef int (*COMP_FUNC)(const void *, const void *);

VECTOR* CreateVector_VECTOR(unsigned int elementSize_uint) {
	VECTOR *ret_VECTOR;
	
	ret_VECTOR = (VECTOR*)malloc(sizeof(VECTOR));
	if(!ret_VECTOR) return 0;
	
	ret_VECTOR->elementSize_uint = elementSize_uint;
	ret_VECTOR->count_uint = 0;
	ret_VECTOR->capacitiy_uint = INITIAL_VECTOR_SIZE;
	ret_VECTOR->base_void = malloc(sizeof(*(ret_VECTOR->base_void)) * ret_VECTOR->capacitiy_uint);
	if(!ret_VECTOR->base_void) {
		free(ret_VECTOR);
		return 0;
	}
	
	return ret_VECTOR;
}

void DestroyVector_void(VECTOR *v_VECTOR, FP_DEALLOC deAlloc_FP_DEALLOC) {
	unsigned int idx_uint;
	
	if(deAlloc_FP_DEALLOC)
		for(idx_uint = 0; idx_uint < v_VECTOR->count_uint; idx_uint += 1)
			deAlloc_FP_DEALLOC((v_VECTOR->base_void)[idx_uint]);
	
	free(v_VECTOR->base_void);
	free(v_VECTOR);
}

static int Expend_int(VECTOR *v_VECTOR) {
	void **newBase_void;
	
	if(!(v_VECTOR->capacitiy_uint << 1)) return -1;
	
	newBase_void = (void**)malloc(sizeof(*newBase_void) * (v_VECTOR->capacitiy_uint << 1));
	if(!newBase_void) return -1;
	
	memcpy(newBase_void, v_VECTOR->base_void, sizeof(*newBase_void) * v_VECTOR->capacitiy_uint);
	free(v_VECTOR->base_void);
	v_VECTOR->base_void = newBase_void;
	v_VECTOR->capacitiy_uint <<= 1;
	
	return 0;
}

VECTOR* AddToVector_VECTOR(VECTOR *v_VECTOR, const void *obj_void) {
	void *obj2_void;
	
	obj2_void = malloc(v_VECTOR->elementSize_uint);
	if(!obj2_void) return 0;
	
	if(v_VECTOR->count_uint == v_VECTOR->capacitiy_uint) {
		if(Expend_int(v_VECTOR)) {
			free(obj2_void);
			return 0;
		}
	}
	
	memcpy(obj2_void, obj_void, v_VECTOR->elementSize_uint);
	
	(v_VECTOR->base_void)[v_VECTOR->count_uint] = obj2_void;
	v_VECTOR->count_uint += 1;
	
	return v_VECTOR;
}

void* VectorFind_void(const VECTOR *v_VECTOR, const void *obj_void, COMP_FUNC comp_COMP_FUNC) {
	return *((void**)bsearch(&obj_void, v_VECTOR->base_void, v_VECTOR->count_uint, v_VECTOR->elementSize_uint, comp_COMP_FUNC));
}

int VectorRemove_void(VECTOR *v_VECTOR, const void *obj_void, COMP_FUNC comp_COMP_FUNC, FP_DEALLOC deAlloc_FP_DEALLOC) {
	void **res_void;
	size_t rmIdx_size_t;
	
	res_void = (void**)VectorFind_void(v_VECTOR, obj_void, comp_COMP_FUNC);
	if(!res_void) return -1;
	
	if(deAlloc_FP_DEALLOC) deAlloc_FP_DEALLOC(*res_void);
	rmIdx_size_t = (size_t)res_void - (size_t)(v_VECTOR->base_void);
	memmove(v_VECTOR->base_void + rmIdx_size_t, v_VECTOR->base_void + rmIdx_size_t + 1, sizeof(*res_void) * (v_VECTOR->count_uint - rmIdx_size_t - 1));
	v_VECTOR->count_uint -= 1;
	
	return 0;
}

void VectorSort_void(const VECTOR *v_VECTOR, COMP_FUNC sort_COMP_FUNC) {
	return qsort(v_VECTOR->base_void, v_VECTOR->count_uint, sizeof(*(v_VECTOR->base_void)), sort_COMP_FUNC);
}

void* VectorAt_void(VECTOR *v_VECTOR, unsigned int idx_uint) {
	if(idx_uint >= v_VECTOR->count_uint) return 0;
	return (v_VECTOR->base_void)[idx_uint];
}

void** VectorIndex_void(const VECTOR *v_VECTOR, COMP_FUNC sort_COMP_FUNC) {
	void **ret_void;
	
	ret_void = malloc(sizeof(*ret_void) * v_VECTOR->count_uint);
	if(!ret_void) return 0;
	memcpy(ret_void, v_VECTOR->base_void, sizeof(*ret_void) * v_VECTOR->count_uint);
	qsort(ret_void, v_VECTOR->count_uint, sizeof(*(v_VECTOR->base_void)), sort_COMP_FUNC);
	
	return ret_void;
}

unsigned int VectorGetElementSize_uint(const VECTOR *v_VECTOR) {
	return v_VECTOR->elementSize_uint;
}

unsigned int VectorGetElementCount_uint(const VECTOR *v_VECTOR) {
	return v_VECTOR->count_uint;
}

unsigned int VectorGetCapacity_uint(const VECTOR *v_VECTOR) {
	return v_VECTOR->capacitiy_uint;
}