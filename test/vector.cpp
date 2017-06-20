#include <vector.h>
#include <gtest/gtest.h>

void fillVector(Vector* v, size_t size) {
	for (unsigned int i = 0; i < size; i++)
		vectorAdd(v, &i);
}

TEST(VectorSuite, vectorInit) {
	Vector vec = INIT_VECTOR(int);
	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorAdd) {
	Vector vec = INIT_VECTOR(int);

	for (int i = 0; i < 20; i++) {
		int elem = 10 + i;
		vectorAdd(&vec, &elem);
	}

	EXPECT_EQ(10, *(int*) vectorGet(&vec, 0));
	EXPECT_EQ(20, ((int*) vec.data)[10]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorAddArray) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 20;
	fillVector(&vec, 20);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	const size_t arrLength = 5;
	const int arr[arrLength] = {0, 1, 2, 3, 4};

	vectorAddArray(&vec, arr, arrLength);
	EXPECT_EQ(vec.size, testSize + arrLength);

	for (unsigned int i = 0; i < arrLength; ++i)
		EXPECT_EQ(((int*) vec.data)[testSize + i], arr[i]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorGet) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 20;
	fillVector(&vec, 20);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	EXPECT_EQ(*(int*) vectorGet(&vec, 0), ((int*) vec.data)[0]);
	EXPECT_EQ(*(int*) vectorGet(&vec, 10), ((int*) vec.data)[10]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorClear) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 5;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	vectorClear(&vec);
	EXPECT_FALSE(vec.size);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorShrinkToFit) {
	Vector vec = INIT_VECTOR(int);

	const size_t testCapacity = 100;
	vectorReserve(&vec, testCapacity);
	fillVector(&vec, testCapacity / 4);
	ASSERT_GE(vec.capacity, testCapacity);
	ASSERT_EQ(vec.size, testCapacity / 4);

	vectorShrinkToFit(&vec);
	EXPECT_LT(vec.capacity, testCapacity);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorShrinkToFitExactly) {
	Vector vec = INIT_VECTOR(int);

	const size_t testCapacity = 100;
	vectorReserve(&vec, testCapacity);
	fillVector(&vec, testCapacity / 4);
	ASSERT_GE(vec.capacity, testCapacity);
	ASSERT_EQ(vec.size, testCapacity / 4);

	vectorShrinkToFitExactly(&vec);
	EXPECT_EQ(vec.size, vec.capacity);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorReserve) {
	Vector vec = INIT_VECTOR(int);

	vectorReserve(&vec, 20);
	EXPECT_GE(vec.capacity, 20u);

	vectorReserve(&vec, 40);
	EXPECT_GE(vec.capacity, 40u);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorSwap) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	const int index1 = 0;
	const int index2 = 10;
	const int val1 = ((int*) vec.data)[index1];
	const int val2 = ((int*) vec.data)[index2];

	vectorSwap(&vec, index1, index2);

	EXPECT_EQ(((int*) vec.data)[index1], val2);
	EXPECT_EQ(((int*) vec.data)[index2], val1);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorInsert) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrBefore, vec.data, vec.size * sizeof(int));

	const size_t insertIndex = testSize / 3;
	const int val = 200;
	vectorInsert(&vec, insertIndex, &val);

	for (size_t i = 0; i < insertIndex; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i]);

	EXPECT_EQ(((int*) vec.data)[insertIndex], val);

	for (size_t i = insertIndex + 1; i < vec.size; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i - 1]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorRemoveFirst) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrBefore, vec.data, vec.size * sizeof(int));

	vectorRemoveFirst(&vec);
	EXPECT_EQ(vec.size, testSize - 1);

	for (size_t i = 0; i < vec.size; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i + 1]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorRemoveLast) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrBefore, vec.data, vec.size * sizeof(int));

	vectorRemoveLast(&vec);
	EXPECT_EQ(vec.size, testSize - 1);

	for (size_t i = 0; i < vec.size; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorRemoveAt) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrBefore, vec.data, vec.size * sizeof(int));

	const size_t removeIndex = testSize / 3;
	vectorRemoveAt(&vec, removeIndex);
	EXPECT_EQ(vec.size, testSize - 1);

	for (size_t i = 0; i < removeIndex; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i]);

	for (size_t i = removeIndex; i < vec.size; i++)
		EXPECT_EQ(((int*) vec.data)[i], ((int*) arrBefore)[i + 1]);

	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorRemoveRange) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrayBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrayBefore, vec.data, vec.size * sizeof(int));

	const size_t rangeSize = 10;
	const size_t index = 4;

	vectorRemoveRange(&vec, index, index + rangeSize);

	for (size_t i = 0; i < index; i++)
		EXPECT_EQ(arrayBefore[i], ((int*) vec.data)[i]);

	for (size_t i = index; i < vec.size; i++)
		EXPECT_EQ(arrayBefore[i + rangeSize], ((int*) vec.data)[i]);

	free(arrayBefore);
	vectorDestroy(&vec);
}

TEST(VectorSuite, vectorInsertArray) {
	Vector vec = INIT_VECTOR(int);

	const size_t testSize = 100;
	fillVector(&vec, testSize);
	ASSERT_TRUE(vec.data);
	ASSERT_EQ(vec.size, testSize);

	int* arrayBefore = (int*) calloc(vec.size, sizeof(int));
	memcpy(arrayBefore, vec.data, vec.size * sizeof(int));

	const size_t arrLength = 10;
	const size_t index = 4;

	const int arr[arrLength] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	vectorInsertArray(&vec, index, arr, arrLength);

	for (size_t i = 0; i < index; i++)
		EXPECT_EQ(arrayBefore[i], ((int*) vec.data)[i]);

	for (size_t i = 0; i < arrLength; i++)
		EXPECT_EQ(arr[i], ((int*) vec.data)[index + i]);

	for (size_t i = index + arrLength; i < vec.size; i++)
		EXPECT_EQ(arrayBefore[i - arrLength], ((int*) vec.data)[i]);

	free(arrayBefore);
	vectorDestroy(&vec);
}
