/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "bst.h"

#define TRUE     1 
#define FALSE    0
#define ERROR   -1
#define SUCCESS  0
#define IS_EQUAL 0

struct node
{
    void *data;
    bst_iter_t parent;
    bst_iter_t right;
    bst_iter_t left;
};

struct bst
{
    bst_iter_t root;
    compare_t compare_func;
};

static int BSTIsLeaf(bst_iter_t iter);
static void BSTRemoveLeaf(bst_iter_t iter);
static int BSTIsIterWithOneChild(bst_iter_t iter);
static void BSTRemoveIterWithOnlyChild(bst_iter_t iter);
static bst_iter_t BSTReturnTheOnlyChild(bst_iter_t iter);
static void BSTCreateLeaf(bst_iter_t iter, bst_iter_t parent, void *data);
static int BSTCountSize(void *data, void *params);
static bst_iter_t BSTChooseSide(bst_t *bst, bst_iter_t iter, void *data);

bst_t *BSTCreate(compare_t compare_func)
{
	bst_t *bst = NULL;
	
	assert (NULL != compare_func);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return (NULL);
	}
	
	bst->root = (bst_iter_t)malloc(sizeof(struct node));
	if (NULL == bst->root)
	{
		free (bst);
		
		return (NULL);
	}
	
	bst->compare_func = compare_func;
	BSTCreateLeaf(bst->root, NULL, NULL);
	
	return (bst);
}

void BSTDestroy(bst_t *bst)
{
	bst_iter_t runner = BSTBegin(bst);
	
	while (FALSE == BSTIsEqual(runner, BSTEnd(bst)))
	{
		runner = BSTRemove(runner);
	}
	
	free (runner);
	
	free (bst);
}

bst_iter_t BSTInsert(bst_t *bst, const void *data)
{
	bst_iter_t parent = bst->root;
	bst_iter_t runner = bst->root->left;
	bst_iter_t iter = NULL;

	assert (NULL != bst);
	
	iter = (bst_iter_t)malloc(sizeof(struct node));
	if (NULL == iter)
	{
		return (NULL);
	}
	
	if (NULL == bst->root->left)
	{
		bst->root->left = iter;
		BSTCreateLeaf(iter, parent, (void *)data);
		
		return (iter);
	}
		
	while (NULL != runner)
	{
		assert (runner->data != data);
		
		parent = runner;
		runner = BSTChooseSide(bst, runner, (void *)data);	
	}
 
 	if ((0 < bst->compare_func((void *)data, BSTGetData(parent))))
 	{
 		parent->right = iter;
 	}
 	else
 	{
 		parent->left = iter;
 	}
 	
 	BSTCreateLeaf(iter, parent, (void *)data);

	return (iter);
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
	bst_iter_t successor = NULL;
	
	assert (NULL != iter);
	
	if (TRUE == BSTIsLeaf(iter))
	{
		successor = BSTNext(iter);
		
		BSTRemoveLeaf(iter);
	}
	else if (TRUE == BSTIsIterWithOneChild(iter))
	{
		successor = BSTNext(iter);
		
		BSTRemoveIterWithOnlyChild(iter);
	}
	else
	{
		successor = iter;
		iter = BSTNext(iter);
		
		successor->data = iter->data;
		
		if (TRUE == BSTIsLeaf(iter))
		{
			BSTRemoveLeaf(iter);
		}
		else if (TRUE == BSTIsIterWithOneChild(iter))
		{		
			BSTRemoveIterWithOnlyChild(iter);
		}
	}
	
	return (successor);
}

bst_iter_t BSTFind(const bst_t *bst, const void *to_find)
{
	bst_iter_t runner = bst->root->left;
	
	assert (NULL != bst);
	
	while (NULL != runner && \
		   IS_EQUAL != bst->compare_func(BSTGetData(runner), (void *)to_find))
	{
		runner = BSTChooseSide((bst_t *)bst, runner, (void *)to_find);	
	}

	return (runner);
}

void *BSTGetData(const bst_iter_t iter)
{
	assert (NULL != iter);
	
	return ((bst_iter_t)iter->data);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert (NULL != bst);
	
	return (TRUE == BSTIsEqual(BSTBegin(bst), BSTEnd(bst)));
}

size_t BSTSize(const bst_t *bst)
{
	size_t counter = 0;
	
	BSTForEach(BSTBegin(bst),BSTEnd(bst), BSTCountSize, &counter);
	
	return (counter);
}

int BSTIsEqual(const bst_iter_t iter1, bst_iter_t iter2)
{
	assert (NULL != iter1);
	assert (NULL != iter2);
	
	return (iter1 == iter2);
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t runner = BSTEnd(bst);

	assert (NULL != bst);
		
	while (NULL != runner->left)
	{
		runner = runner->left;
	}
	
	return (runner);
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert (NULL != bst);
	
	return (bst->root);
}

bst_iter_t BSTNext(const bst_iter_t iter)
{
	bst_iter_t runner = (bst_iter_t)iter;
	bst_iter_t successor = NULL;
	
	assert (NULL != iter);
	
	if (NULL == runner->parent)
	{
		return (NULL);
	}
	
	if (NULL != runner->right)
	{
		runner = runner->right;
		while (NULL != runner->left)
		{
			runner = runner->left;
		}
		successor = runner;
	}
	else if (NULL == runner->right)
	{
		while (runner != runner->parent->left)
		{
			runner = runner->parent;
		}
		successor = runner->parent;	
	}
		
	return (successor);
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{
	bst_iter_t predecessor = NULL;
	bst_iter_t runner = (bst_iter_t)iter;
	
	assert (NULL != iter);
	
	if (NULL != runner->left)
	{
		runner = runner->left;
		while (NULL != runner->right)
		{
			runner = runner->right;
		}
		predecessor = runner;
	}
	else
	{
		while (runner != runner->parent->right)
		{
			if (NULL == runner->parent)
			{
				return (NULL);
			}
			runner = runner->parent;
		}
		predecessor = runner->parent;	
	}
		
	return (predecessor);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, 
               action_t action_func, void *params)
{
	int state = SUCCESS;
	
	assert (NULL != from);
	assert (NULL != to);
	assert (NULL != action_func);
	
	while (FALSE == BSTIsEqual(from, to) && ERROR != state)
	{
		state = action_func(BSTGetData(from), params);

		from = BSTNext(from);
	}
	
	return (state);
}

static int BSTIsLeaf(bst_iter_t iter)
{
	int state = FALSE;
	
	if (NULL == iter->right && NULL == iter->left)
	{
		state = TRUE;
	}
	
	 return (state);
}

static void BSTRemoveLeaf(bst_iter_t iter)
{
	bst_iter_t parent = iter->parent;
	
	if (iter == parent->right)
	{
		parent->right = NULL;
	}
	else if (iter == parent->left)
	{
		parent->left = NULL;
	}
			
	free (iter);
}

static int BSTIsIterWithOneChild(bst_iter_t iter)
{
	int state = FALSE;
	
	 if ((NULL == iter->right && NULL != iter->left) || \
	 	 (NULL != iter->right && NULL == iter->left))
	 {
	 	state = TRUE;
	 }
	 
	 return (state);
}

static void BSTRemoveIterWithOnlyChild(bst_iter_t iter)
{
	bst_iter_t parent = iter->parent;
	bst_iter_t only_child = BSTReturnTheOnlyChild(iter);
	
	only_child->parent = parent;
	
	if (iter == parent->right)
	{
		parent->right = only_child;
	}
	else if (iter == parent->left)
	{
		parent->left = only_child;
	}
					
	free (iter);
}

static bst_iter_t BSTReturnTheOnlyChild(bst_iter_t iter)
{
	 if (NULL != iter->left)
	 {
	 	return (iter->left);
	 }
	 else if (NULL != iter->right)
	 {
	 	return (iter->right);
	 }
	 
	 return (NULL);
}

static void BSTCreateLeaf(bst_iter_t iter, bst_iter_t parent, void *data)
{
	iter->data = data;
	iter->parent = parent;
	iter->right = NULL;
	iter->left = NULL; 
}

static int BSTCountSize(void *data, void *params)
{
	++*(size_t *)params;
	(void)data;
	
	return (SUCCESS);
}

static bst_iter_t BSTChooseSide(bst_t *bst, bst_iter_t iter, void *data)
{
	if ((0 < bst->compare_func(data, BSTGetData(iter))))
	{
		iter = iter->right;
	}
	else
	{
		iter = iter->left;
	}
	
	return (iter);
}
