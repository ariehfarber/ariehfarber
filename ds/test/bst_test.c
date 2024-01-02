/*******************************************************************************
*Author: Chen
*******************************************************************************/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "bst.h"

#define FASLE (0)
#define TRUE (1)
#define SUCCESS (0)
#define FAILURE (-1)

static void TestBSTCreate(void);
static void TestBSTInsert(void);
static void TestBSTFind(void);
static void TestBSTIsEmptyAndSize(void);
static void TestBSTNextAndPrev(void);
static void TestBSTForEach(void);

static int Compare(void *data1, void *data2);
static int Mult2(void *data1, void *data2);

int main(void)
{
	TestBSTCreate();
	TestBSTInsert();
	TestBSTFind();
	TestBSTIsEmptyAndSize();
	TestBSTNextAndPrev();
	TestBSTForEach();

	return(1);
}

static void TestBSTCreate(void)
{
	bst_t *bst =BSTCreate(Compare);

	assert(NULL != bst);

	printf("BSTCreate: success\n");
	BSTDestroy(bst);
	printf("BSTDestory: success\n");
}

static void TestBSTInsert(void)
{
	bst_t *bst =BSTCreate(Compare);
	bst_iter_t iter = NULL;
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int arr_expected[] = {1, 2, 3, 5, 6, 8, 10};
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(NULL != BSTInsert(bst, &arr[i]));
	}

	iter = BSTBegin(bst);
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr_expected[i] == *(int*)BSTGetData(iter));
		iter = BSTNext(iter);
	}

	BSTDestroy(bst);

	printf("BSTInsert: success\n");
	printf("BSTGetData: success\n");
	printf("BSTIsEqual: success\n");
}
static void TestBSTFind(void)
{
	bst_t *bst =BSTCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int num_not_fount = 11;
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(NULL != BSTInsert(bst, &arr[i]));
	}

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr[i] == *(int*)BSTGetData(BSTFind(bst,&arr[i])));
	}

	assert(NULL == BSTFind(bst,&num_not_fount));

	BSTDestroy(bst);
	printf("BSTFind: success\n");
}
static void TestBSTIsEmptyAndSize(void)
{
	bst_t *bst =BSTCreate(Compare);
	bst_iter_t iter = NULL;
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	size_t i = 0;

	assert(TRUE == BSTIsEmpty(bst));
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(i == BSTSize(bst));
		assert(NULL != BSTInsert(bst, &arr[i]));
	}

	assert(FASLE == BSTIsEmpty(bst));
	iter = BSTBegin(bst);
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(sizeof(arr) / sizeof(arr[0]) - i == BSTSize(bst));
		iter = BSTRemove(iter);
	}
	
	assert(TRUE == BSTIsEmpty(bst));
	BSTDestroy(bst);
	printf("BSTRemove: success\n");
	printf("BSTSize: success\n");
	printf("BSTIsEmpty: success\n");
}

static void TestBSTNextAndPrev(void)
{
	bst_t *bst =BSTCreate(Compare);
	bst_iter_t iter = NULL;
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int arr_expected_forward[] = {1, 2, 3, 5, 6, 8, 10};
	int arr_expected_backward[] = {10, 8, 6, 5, 3, 2, 1};
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(NULL != BSTInsert(bst, &arr[i]));
	}

	iter = BSTBegin(bst);
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr_expected_forward[i] == *(int*)BSTGetData(iter));
		iter = BSTNext(iter);
	}

	iter = BSTEnd(bst);
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		iter = BSTPrev(iter);
		assert(arr_expected_backward[i] == *(int*)BSTGetData(iter));
	}

	BSTDestroy(bst);
	printf("BSTNext: success\n");
	printf("BSTPrev: success\n");
	printf("BSTBegin: success\n");
	printf("BSTEnd: success\n");
}
static void TestBSTForEach(void)
{
	bst_t *bst =BSTCreate(Compare);
	bst_iter_t from = NULL, to = NULL;
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int arr_expected[] = {1, 2, 3, 5, 6, 8, 10};
	int param = 2;
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(NULL != BSTInsert(bst, &arr[i]));
	}

	from = BSTBegin(bst); /*1*/
	from = BSTNext(from); /*2*/
	from = BSTNext(from); /*3*/
	to = BSTEnd(bst); /*dummy*/
	to = BSTPrev(to); /*10*/
	to = BSTPrev(to); /*8*/

	assert(SUCCESS == BSTForEach(from, to, Mult2, &param));
	from = BSTBegin(bst);
	for(i = 0; i < 2; ++i)
	{
		assert(arr_expected[i] == *(int*)BSTGetData(from));
		from = BSTNext(from);
	}

	for(i = 2; i < 5; ++i)
	{
		assert(arr_expected[i] * param == *(int*)BSTGetData(from));
		from = BSTNext(from);
	}

	for(i = 5; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr_expected[i] == *(int*)BSTGetData(from));
		from = BSTNext(from);
	}

	BSTDestroy(bst);
	printf("BSTForEach: success\n");
}

static int Mult2(void *data1, void *data2)
{
	*(int*)data1 *= *(int*)data2;
	return(SUCCESS);
}

static int Compare(void *data1, void *data2)
{
	return(*(int*)data1 - *(int*)data2);
}
