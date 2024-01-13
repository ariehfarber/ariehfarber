/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Elinor Fuchs
*Date: 03/01/2024
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include <stdio.h> 

#include "bst.h"
#include "ds_utils.h" /*TRUE, FALSE, SUCCESS*/

#define EQUAL 	 0
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

static bst_iter_t BSTFetchIter(node_t *node);	
static node_t *BSTFetchNode(bst_iter_t iter);
static node_t *BSTCreateNode(bst_t *bst, node_t *parent, void *data);
static void BSTInitLeaf(node_t *new_node, node_t *parent, void *data);
static void BSTConnectParent(bst_t *bst, node_t *new_node, \
							  node_t *parent, void *data);				  
static int BSTIsTwoChildren(node_t *node);
static void BSTRemoveNode(node_t *node);
static int BSTCountSize(void *data, void *params);
static node_t *BSTDeepDiveLocate(bst_t *bst, void *data);
static node_t *BSTDeepDiveRight(node_t *node);
static node_t *BSTDeepDiveLeft(node_t *node);

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
	node_t *runner = BSTFetchNode(BSTBegin(bst));
	
	while (FALSE == BSTIsEqual(BSTFetchIter(runner), BSTEnd(bst)))
	{
		runner = BSTRemove(BSTFetchIter(runner));
	}
	
	free (runner);
	
	free (bst);
}

bst_iter_t BSTInsert(bst_t *bst, const void *data)
{
	node_t *parent = NULL;
	node_t *new_node = NULL;

	assert (NULL != bst);
		
	parent = BSTDeepDiveLocate(bst, (void *)data);
	
	/*assert that the same data was not inserted twice*/
	#ifndef NDEBUG
	if (bst->root != parent)
	{
		assert(EQUAL != bst->compare(BSTGetData(BSTFetchIter(parent)), \
									(void *)data));
	}
	#endif

		
 	new_node = BSTCreateNode(bst, parent, (void *)data);
	if (NULL == new_node)
	{
		return (NULL);
	}

	return (BSTFetchIter(new_node));
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
	node_t *successor = BSTFetchNode(iter);
	
	assert (NULL != iter);
	
	if (TRUE == BSTIsTwoChildren(BSTFetchNode(iter)))
	{
		successor = BSTFetchNode(iter);
		iter = BSTNext(iter);
		
		successor->data = BSTGetData(iter);
			
		BSTRemoveNode(BSTFetchNode(iter));		
	}
	else
	{
		successor = BSTFetchNode(BSTNext(iter));
		
		BSTRemoveNode(BSTFetchNode(iter));
	}
	
	return (BSTFetchIter(successor));
}

bst_iter_t BSTFind(const bst_t *bst, const void *to_find)
{
	node_t *find_node = NULL;
	
	assert (NULL != bst);
	
	find_node = BSTDeepDiveLocate((bst_t *)bst, (void *)to_find);
	
	if (EQUAL == bst->compare((void *)to_find, \
		BSTGetData(BSTFetchIter(find_node))))
	{
		return (BSTFetchIter(find_node));
	}

	return (BSTEnd(bst));
}

void *BSTGetData(const bst_iter_t iter)
{
	void *data = NULL;
	
	assert (NULL != iter);

	data = (BSTFetchNode(iter))->data;
	
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
	
	return (BSTFetchNode(iter1) == BSTFetchNode(iter2));
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	node_t *runner = BSTEnd(bst);

	assert (NULL != bst);
		
	runner = BSTDeepDiveLeft(runner);
	
	return (BSTFetchIter(runner));
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert (NULL != bst);
	
	return (BSTFetchIter(bst->root));
}

bst_iter_t BSTNext(const bst_iter_t iter)
{
	node_t *runner = NULL;
	
	assert (NULL != iter);
	
	runner = BSTFetchNode((bst_iter_t)iter);
	
	if (NULL == runner->parent)
	{
		return (NULL);
	}
	
	if (NULL != runner->right)
	{
		runner = runner->right;
		
		runner = BSTDeepDiveLeft(runner);
	}
	else 
	{
		while (runner != runner->parent->left)
		{
			runner = runner->parent;
		}
		runner = runner->parent;	
	}
		
	return (BSTFetchIter(runner)); 
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{
	node_t *runner = NULL;
	
	assert (NULL != iter);
	
	runner = BSTFetchNode((bst_iter_t)iter);
	
	if (NULL != runner->left)
	{
		runner = runner->left;

		runner = BSTDeepDiveRight(runner);
	}
	else
	{
		while (NULL != runner->parent && runner != runner->parent->right)
		{
			runner = runner->parent;
		}
		runner = runner->parent;	
	}

	return (BSTFetchIter(runner)); 	
}

int BSTForEach(bst_iter_t from, bst_iter_t to, 
               action_t action_func, void *params)
{
	int state = SUCCESS;
	
	assert (NULL != from);
	assert (NULL != to);
	assert (NULL != action_func);
	
	while (FALSE == BSTIsEqual(from, to) && SUCCESS == state)
	{
		state = action_func(BSTGetData(from), params);

		from = BSTNext(from);
	}
	
	return (state);
}

static node_t *BSTFetchNode(bst_iter_t iter)
{
	return ((node_t *)iter);
}

static bst_iter_t BSTFetchIter(node_t *node)
{
	return ((bst_iter_t)node);
}

static node_t *BSTCreateNode(bst_t *bst, node_t *parent, void *data)
{
	node_t *new_node = NULL;
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	BSTInitLeaf(new_node, parent, data);
	BSTConnectParent(bst, new_node, parent, data);
	
	return (new_node);
}

static void BSTInitLeaf(node_t *new_node, node_t *parent, void *data)
{
	new_node->data = data;
	new_node->parent = parent;
	new_node->right = NULL;
	new_node->left = NULL; 
}

static void BSTConnectParent(bst_t *bst, node_t *new_node, \
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
 	else if ((0 < bst->compare(BSTGetData(BSTFetchIter(parent)), (void *)data)))
 	{
 		parent->left = new_node;
 	}
 	else
 	{
 		parent->right = new_node;
 	}
}

static int BSTIsTwoChildren(node_t *node)
{
	return (NULL != node->right && NULL != node->left);
}

static void BSTRemoveNode(node_t *node)
{
	node_t *parent = node->parent;
	node_t *only_child = (node_t *)((size_t)node->right ^ (size_t)node->left);
	
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

static int BSTCountSize(void *data, void *params)
{
	++*(size_t *)params;
	(void)data;
	
	return (SUCCESS);
}

static node_t *BSTDeepDiveLocate(bst_t *bst, void *data)
{
	node_t *node = bst->root->left;
	node_t *parent = bst->root;
	
	while (NULL != node) 
	{
		if ((0 < bst->compare(BSTGetData(BSTFetchIter(node)), data)))
		{
			parent = node;
			node = node->left;
		}
		else
		{
			parent = node;
			node = node->right;
		}
		if (EQUAL == bst->compare(BSTGetData(BSTFetchIter(parent)), data))
		{
			break;
		}
	}

	return (parent);
}

static node_t *BSTDeepDiveRight(node_t *node)
{
	while (NULL != node->right)
	{
		node = node->right;
	}
	
	return (node);
}

static node_t *BSTDeepDiveLeft(node_t *node)
{
	while (NULL != node->left)
	{
		node = node->left;
	}
	
	return (node);
}


