/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "bst.h"

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
	
	
	free (bst->root);
	
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
	
	if (NULL == iter->right && NULL == iter->left)
	{
		successor = iter->parent;
		
		if (iter == successor->right)
		{
			successor->right = NULL;
		}
		else
		{
			successor->left = NULL;
		}
				
		free (iter);
		
		return (successor);
	}
}

/*bst_iter_t BSTFind(const bst_t *bst, const void *tofind)*/
/*{*/

/*}*/

/*void *BSTGetData(const bst_iter_t iter)*/
/*{*/

/*}*/

/*int BSTIsEmpty(const bst_t *bst)*/
/*{*/

/*}*/

/*size_t BSTSize(const bst_t *bst)*/
/*{*/

/*}*/

/*int BSTIsEqual(const bst_iter_t iter1, bst_iter_t iter2)*/
/*{*/

/*}*/

/*bst_iter_t BSTBegin(const bst_t *bst)*/
/*{*/

/*}*/

/*bst_iter_t BSTEnd(const bst_t *bst)*/
/*{*/

/*}*/

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




