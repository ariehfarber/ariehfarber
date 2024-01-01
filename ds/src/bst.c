/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "bst.h"

#define TRUE  1
#define FALSE 0

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
static int BSTIsOneChildParent(bst_iter_t iter);
static void BSTRemoveLeaf(bst_iter_t iter);
static void BSTRemoveOneChildParnet(bst_iter_t iter);

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
	
	bst->root->data = NULL;
	bst->root->parent = NULL;
	bst->root->right = NULL;
	bst->root->left = NULL;
	
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
		
	while (NULL != runner)
	{
		assert (runner->data != data);
		
		if ((0 < bst->compare_func(BSTGetData(runner), (void *)data)))
		{
			parent = runner;
			runner = runner->right;
		}
		else
		{
			parent = runner;
			runner = runner->left;
		}
	}
 
	iter->data = (void *)data;
	iter->parent = parent;
	iter->right = NULL;
	iter->left = NULL; 
	
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
	else if (TRUE == BSTIsOneChildParent(iter))
	{
		successor = BSTNext(iter);
		
		BSTRemoveOneChildParnet(iter);
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
		else if (TRUE == BSTIsOneChildParent(iter))
		{		
			BSTRemoveOneChildParnet(iter);
		}
	}
	
	return (successor);
}

/*bst_iter_t BSTFind(const bst_t *bst, const void *tofind)*/
/*{*/

/*}*/

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

/*size_t BSTSize(const bst_t *bst)*/
/*{*/

/*}*/

int BSTIsEqual(const bst_iter_t iter1, bst_iter_t iter2)
{
	assert (NULL != iter1);
	assert (NULL != iter2);
	
	return (iter1 == iter2);
}

/*bst_iter_t BSTBegin(const bst_t *bst)*/
/*{*/

/*}*/

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert (NULL != bst);
	
	return (bst->root);
}

/*bst_iter_t BSTNext(const bst_iter_t iter)*/
/*{*/

/*}*/

/*bst_iter_t BSTPrev(const bst_iter_t iter)*/
/*{*/

/*}*/

/*int BSTForEach(bst_iter_t from, bst_iter_t to, */
/*               action_t action_func, const void *params)*/
/*{*/

/*}*/

static int BSTIsLeaf(bst_iter_t iter)
{
	int state = FALSE;
	
	if (NULL == iter->right && NULL == iter->left)
	{
		state = TRUE;
	}
	
	 return (state);
}

static int BSTIsOneChildParent(bst_iter_t iter)
{
	int state = FALSE;
	
	 if ((NULL == iter->right && NULL != iter->left) || \
	 	 (NULL != iter->right && NULL == iter->left))
	 {
	 	state = TRUE;
	 }
	 
	 return (state);
}

static void BSTRemoveLeaf(bst_iter_t iter)
{
	bst_iter_t parent = NULL;
	
	parent = iter->parent;
	
	if (iter == parent->right)
	{
		parent->right = NULL;
	}
	else
	{
		parent->left = NULL;
	}
			
	free (iter);
}

static void BSTRemoveOneChildParnet(bst_iter_t iter)
{
	bst_iter_t child = NULL;
	
	if (NULL != iter->left)
	{
		child = iter->left;
		
		iter->data = child->data;
		
		iter->left = NULL;
	}
	else 
	{
		child = iter->right;
		
		iter->data = child->data;
		
		iter->right = NULL;
	}
					
	free (child);
}






