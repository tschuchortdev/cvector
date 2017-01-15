//
// Created by Thilo on 1/13/2017.
//

#include <stdlib.h>
#include <mem.h>
#include "vector.h"


static const size_t VECTOR_INITIAL_CAPACITY = 8;

unsigned int roundUpToMultiple(unsigned int num, unsigned int multiple) {
	if (multiple == 0)
		return num;

	int remainder = num % multiple;

	if (remainder == 0)
		return num;
	else
		return num + multiple - remainder;
}

Vector initVector(size_t elemSize) {
	return (Vector) {.elemSize = elemSize};
}

VectorError vectorAdd(Vector* vec, const void* elem) {
	return vectorAddArray(vec, elem, 1);
}

VectorError vectorAddArray(Vector* vec, const void* elems, size_t length) {
	vectorReserve(vec, vec->size + length);

	memcpy((char*) vec->data + vec->elemSize * vec->size, elems, vec->elemSize * length);
	vec->size += length;
	return VEC_OK;
}

void* vectorGet(Vector* vec, rsize_t index) {
	if (vec->data && index < vec->size)
		return (char*) vec->data + (index * vec->elemSize);
	else
		return NULL; // out of bounds
}

void vectorClear(Vector* vec) {
	vec->size = 0;
}

VectorError vectorShrinkToFit(Vector* vec) {
	size_t newCapacity =
			vec->size
			? roundUpToMultiple(vec->size, VECTOR_INITIAL_CAPACITY)
			: VECTOR_INITIAL_CAPACITY;

	if (vec->data)
		vec->data = realloc(vec->data, vec->elemSize * newCapacity);
	else
		vec->data = calloc(vec->elemSize, newCapacity);

	vec->capacity = newCapacity;
	return VEC_OK;
}

VectorError vectorShrinkToFitExactly(Vector* vec) {
	vec->data = realloc(vec->data, vec->elemSize * vec->size);
	vec->capacity = vec->size;
	return VEC_OK;
}

VectorError vectorReserve(Vector* vec, size_t capacity) {
	if (capacity > vec->capacity) {
		size_t newCapacity =
				vec->capacity
				? roundUpToMultiple(vec->capacity, VECTOR_INITIAL_CAPACITY)
				: VECTOR_INITIAL_CAPACITY;

		while (newCapacity < capacity)
			newCapacity *= 2;

		if (vec->data)
			vec->data = realloc(vec->data, vec->elemSize * newCapacity);
		else
			vec->data = calloc(vec->elemSize, newCapacity);

		vec->capacity = newCapacity;
	}

	return VEC_OK;
}

VectorError vectorSwap(Vector* vec, rsize_t index1, rsize_t index2) {
	if (vec->data && index1 < vec->size && index2 < vec->size) {
		char* temp = malloc(vec->elemSize);
		memcpy(temp, (char*) vec->data + index1 * vec->elemSize, vec->elemSize);

		memcpy(
				(char*) vec->data + index1 * vec->elemSize,
				(char*) vec->data + index2 * vec->elemSize,
				vec->elemSize);

		memcpy((char*) vec->data + index2 * vec->elemSize, temp, vec->elemSize);

		free(temp);
		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

VectorError vectorInsert(Vector* vec, rsize_t index, const void* elem) {
	if (vec->data && index < vec->size) {
		vectorReserve(vec, vec->size + 1);

		if (index != vec->size) {
			//using memcpy here would violate the restrict contract and terrrribbleee things could happen
			memmove(
					(char*) vec->data + ((index + 1) * vec->elemSize),
					(char*) vec->data + (index * vec->elemSize),
					(vec->size - index) * vec->elemSize);
		}

		memcpy((char*) vec->data + (index * vec->elemSize), elem, vec->elemSize);
		vec->size++;

		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

VectorError vectorRemoveFirst(Vector* vec) {
	if (vec->data) {
		//using memcpy here would violate the restrict contract and terrrribbleee things could happen
		memmove(vec->data, (char*) vec->data + vec->elemSize, (vec->size - 1) * vec->elemSize);
		vec->size--;

		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

VectorError vectorRemoveLast(Vector* vec) {
	if (vec->data && vec->size) {
		vec->size--;
		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

VectorError vectorRemoveAt(Vector* vec, rsize_t index) {
	if (vec->data && index < vec->size) {
		if (index != vec->size - 1) {
			//using memcpy here would violate the restrict contract and terrrribbleee things could happen
			memmove(
					(char*) vec->data + (index * vec->elemSize),
					(char*) vec->data + ((index + 1) * vec->elemSize),
					(vec->size - (index + 1)) * vec->elemSize);
		}

		vec->size--;
		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

//end is the index after the last element
VectorError vectorRemoveRange(Vector* vec, rsize_t begin, size_t end) {
	if (vec->data && begin < vec->size) {
		if (end >= vec->size) {
			vec->size = begin - 2;
		}
		else {
			size_t rangeSize = end - begin;

			//using memcpy here would violate the restrict contract and terrrribbleee things could happen
			memmove(
					(char*) vec->data + begin * vec->elemSize,
					(char*) vec->data + end * vec->elemSize,
					(vec->size - begin - rangeSize) * vec->elemSize);

			vec->size -= rangeSize;
		}

		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

VectorError vectorInsertArray(Vector* vec, rsize_t index, const void* elems, size_t length) {
	if (vec->data && index < vec->size) {
		vectorReserve(vec, vec->size + length);

		if (index != vec->size) {
			//using memcpy here would violate the restrict contract and terrrribbleee things could happen
			memmove(
					(char*) vec->data + (index + length) * vec->elemSize,
					(char*) vec->data + index * vec->elemSize,
					(vec->size - (index + 1)) * vec->elemSize);
		}

		memcpy(
				(char*) vec->data + index * vec->elemSize,
				elems,
				length * vec->elemSize);

		return VEC_OK;
	}
	else
		return VEC_OUT_OF_BOUNDS;
}

void vectorDestroy(Vector* vec) {
	free(vec->data);
}
