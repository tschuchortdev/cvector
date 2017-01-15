//
// Created by Thilo on 1/13/2017.
//

#ifndef CHAT_VECTOR_H
#define CHAT_VECTOR_H

#include <stddef.h>

#ifndef RSIZE_MAX
typedef size_t rsize_t;
#endif //RSIZE_MAX

#if __cplusplus
extern "C" {
#endif

#define INIT_VECTOR(type) initVector(sizeof(type));

typedef enum {
	VEC_OK = 0,
	VEC_OUT_OF_BOUNDS = -1
} VectorError;

typedef struct {
	void* data;
	size_t size;
	size_t capacity;
	size_t elemSize;
} Vector;

Vector initVector(size_t elemSize);
VectorError vectorAdd(Vector* vec, const void* elem);
VectorError vectorAddArray(Vector* vec, const void* elems, size_t length);
void* vectorGet(Vector* vec, rsize_t index);
void vectorClear(Vector* vec);
VectorError vectorShrinkToFit(Vector* vector);
VectorError vectorShrinkToFitExactly(Vector* vector);
VectorError vectorReserve(Vector* vec, unsigned int capacity);
VectorError vectorSwap(Vector* vec, rsize_t index1, rsize_t index2);
VectorError vectorInsert(Vector* vec, rsize_t index, const void* elem);
VectorError vectorRemoveFirst(Vector* vector);
VectorError vectorRemoveLast(Vector* vec);
VectorError vectorRemoveAt(Vector* vec, rsize_t index);
VectorError vectorRemoveRange(Vector* vec, rsize_t index, size_t end);
VectorError vectorInsertArray(Vector* vec, rsize_t index, const void* elems, unsigned int length);
void vectorDestroy(Vector* vec);

#if __cplusplus
}
#endif

#endif //CHAT_VECTOR_H
