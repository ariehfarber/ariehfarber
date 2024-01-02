/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include <stdio.h> 

#include "bst.h"

#define TRUE     1 
#define FALSE    0
#define ERROR   -1
#define SUCCESS  0
#define SAME 0
#define MAGIC_NUMBER 0XBADCAFFE

typedef struct node node_t;

struct node
{
    void *data;
    node_t *parent;
	node_t *right;
    node_t *left;
};

struct bst
{
    node_t *root;
    compare_t compare;
};

static bst_iter_t BSTGetIter(node_t *node);	
static node_t *BSTGetNode(bst_iter_t iter);
static node_t *BSTCreateNode(bst_t *bst, node_t *parent, void *data);
static void BSTInitNode(node_t *new_node, node_t *parent, void *data);
static void BSTInitParentNode(bst_t *bst, node_t *new_node, \
							  node_t *parent, void *data);				  
static int BSTIsOneChildOrNone(node_t *node);
static void BSTRemoveNode(node_t *node);
static node_t *BSTReturnTheChild(node_t *node);
static int BSTCountSize(void *data, void *params);
static node_t *BSTChooseSide(bst_t *bst, node_t *node, void *data);

bst_t *BSTCreate(compare_t compare)
{
	bst_t *bst = NULL;
	
	assert (NULL != compare);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return (NULL);
	}
	
	bst->root = BSTCreateNode(bst, NULL, (void *)0XBADCAFFE);
	if (NULL == bst->root)
	{
		free (bst);
		
		return (NULL);
	}
	
	bst->compare = compare;
	
	return (bst);
}

void BSTDestroy(bst_t *bst)
{
	bst_iter_t iter = BSTBegin(bst);
	
	while (FALSE == BSTIsEqual(iter, BSTEnd(bst)))
	{
		iter = BSTRemove(iter);
	}
	
	free (iter);
	
	free (bst);
}

bst_iter_t BSTInsert(bst_t *bst, const void *data)
{
	node_t *parent = bst->root;
	node_t *runner = bst->root->left;
	node_t *new_node = NULL;

	assert (NULL != bst);
	
	if (NULL == bst->root->left)
	{
		new_node = BSTCreateNode(bst, parent, (void *)data);
		if (NULL == new_node)
		{
			return (NULL);
		}
		
		return (BSTGetIter(new_node));
	}
		
	while (NULL != runner)
	{
		assert (runner->data != data);
		
		parent = runner;
		runner = BSTChooseSide(bst, runner, (void *)data);	
	}
 	
 	new_node = BSTCreateNode(bst, parent, (void *)data);
	if (NULL == new_node)
	{
		return (NULL);
	}

	return (BSTGetIter(new_node));
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
	node_t *successor = BSTGetNode(iter);
	
	assert (NULL != iter);
	
	if (TRUE == BSTIsOneChildOrNone(BSTGetNode(iter)))
	{
		successor = BSTGetNode(BSTNext(iter));
		
		BSTRemoveNode(BSTGetNode(iter));
	}
	else
	{
		successor = BSTGetNode(iter);
		iter = BSTNext(iter);
		
		successor->data = BSTGetData(iter);
			
		BSTRemoveNode(BSTGetNode(iter));
	}
	
	return (BSTGetIter(successor));
}

/*Find and insert need to use a shared function to find the node*/
bst_iter_t BSTFind(const bst_t *bst, const void *to_find)
{
	node_t *node = NULL;
	
	assert (NULL != bst);
	
	node = bst->root->left;
	
	while (NULL != node)
	{
		if (SAME == bst->compare((void *)to_find, BSTGetData(BSTGetIter(node))))
		{
			return (BSTGetIter(node));
		}
		node = BSTChooseSide((bst_t *)bst, node, (void *)to_find);	
	}

	return (BSTEnd(bst));
}

void *BSTGetData(const bst_iter_t iter)
{
	node_t *node = NULL;
	void *data = NULL;
	
	assert (NULL != iter);
	
	node = BSTGetNode(iter);
	data = node->data;
	
	return (data);
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
	node_t *runner = BSTEnd(bst);

	assert (NULL != bst);
		
	while (NULL != runner->left)
	{
		runner = runner->left;
	}
	
	return (BSTGetIter(runner));
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert (NULL != bst);
	
	return (BSTGetIter(bst->root));
}

bst_iter_t BSTNext(const bst_iter_t iter)
{
	node_t *runner = BSTGetNode((bst_iter_t)iter);
	node_t *successor = NULL;
	
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
		
	return (BSTGetIter(successor)); 
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{
	node_t *predecessor = NULL;
	node_t *runner = NULL;
	
	assert (NULL != iter);
	
	runner = BSTGetNode((bst_iter_t)iter);
	
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

	return (BSTGetIter(predecessor)); 	
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

static node_t *BSTGetNode(bst_iter_t iter)
{
	return (iter);
}

static bst_iter_t BSTGetIter(node_t *node)
{
	return (node);
}

static node_t *BSTCreateNode(bst_t *bst, node_t *parent, void *data)
{
	node_t *new_node = NULL;
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	BSTInitNode(new_node, parent, data);
	BSTInitParentNode(bst, new_node, parent, data);
	
	return (new_node);
}

static void BSTInitNode(node_t *new_node, node_t *parent, void *data)
{
	new_node->data = data;
	new_node->parent = parent;
	new_node->right = NULL;
	new_node->left = NULL; 
}

static void BSTInitParentNode(bst_t *bst, node_t *new_node, \
							  node_t *parent, void *data)
{
 	if (NULL == parent)
 	{
 		return;
 	}
 	else if (bst->root == parent)
 	{
 		parent->left = new_node;
 	}
 	
 	else if ((0 < bst->compare(BSTGetData(BSTGetIter(parent)), (void *)data)))
 	{
 		parent->left = new_node;
 	}
 	else
 	{
 		parent->right = new_node;
 	}
}

static int BSTIsOneChildOrNone(node_t *node)
{
	int state = FALSE;
	
	 if (NULL == node->right && NULL != node->left)
	 {
	 	state = TRUE;
	 }
	 else if (NULL != node->right && NULL == node->left)
	 {
	 	state = TRUE;
	 }
	 else if (NULL == node->right && NULL == node->left)
	 {
	 	state = TRUE;
	 }
	 
	 return (state);
}

static void BSTRemoveNode(node_t *node)
{
	node_t *parent = node->parent;
	node_t *only_child = BSTReturnTheChild(node);
	
	if (NULL != only_child)
	{
		only_child->parent = parent;
	}
	
	if (node == parent->right)
	{
		parent->right = only_child;
	}
	else if (node == parent->left)
	{
		parent->left = only_child;
	}
					
	free (node);
}

static node_t *BSTReturnTheChild(node_t *node)
{
	 if (NULL != node->left)
	 {
	 	return (node->left);
	 }
	 else if (NULL != node->right)
	 {
	 	return (node->right);
	 }
	 
	 return (NULL);
}

static int BSTCountSize(void *data, void *params)
{
	++*(size_t *)params;
	(void)data;
	
	return (SUCCESS);
}

static node_t *BSTChooseSide(bst_t *bst, node_t *node, void *data)
{
	if ((0 < bst->compare(BSTGetData(BSTGetIter(node)), data)))
	{
		node = node->left;
	}
	else
	{
		node = node->right;
	}
	
	return (node);
}
