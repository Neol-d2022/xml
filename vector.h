#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	const unsigned int elementSize_uint;
	const unsigned int count_uint;
	const unsigned int capacitiy_uint;
	const void **base_void;
} VECTOR;

typedef void (*FP_DEALLOC)(void *);
typedef int (*COMP_FUNC)(const void *, const void *);

VECTOR* CreateVector_VECTOR(unsigned int elementSize_uint);
void DestroyVector_void(VECTOR *v_VECTOR, FP_DEALLOC deAlloc_FP_DEALLOC);

VECTOR* AddToVector_VECTOR(VECTOR *v_VECTOR, const void *obj_void);
void* VectorFind_void(const VECTOR *v_VECTOR, const void *obj_void, COMP_FUNC comp_COMP_FUNC);
int VectorRemove_void(VECTOR *v_VECTOR, const void *obj_void, COMP_FUNC comp_COMP_FUNC, FP_DEALLOC deAlloc_FP_DEALLOC);
void VectorSort_void(const VECTOR *v_VECTOR, COMP_FUNC sort_COMP_FUNC);

void* VectorAt_void(VECTOR *v_VECTOR, unsigned int idx_uint);

void** VectorIndex_void(const VECTOR *v_VECTOR, COMP_FUNC sort_COMP_FUNC);

unsigned int VectorGetElementSize_uint(const VECTOR *v_VECTOR);
unsigned int VectorGetElementCount_uint(const VECTOR *v_VECTOR);
unsigned int VectorGetCapacity_uint(const VECTOR *v_VECTOR);

#endif