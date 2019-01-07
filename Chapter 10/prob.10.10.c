/*
 *
 * Rank from Stream: Imagine you are reading in a stream of integers. Periodically, you wish to be able
 * to look up the rank of a numberx (the number of values less than or equal to x). lmplement the data
 * structures and algorithms to support these operations. That is, implement the method track ( int
 * x), which is called when each number is generated, and the method getRankOfNumber(int
 * x), which returns the number of values less than or equal to x (not including x itself).
 * EXAMPLE
 * Stream (in order of appearance): 5, 1, 4, 4, 5, 9, 7, 13, 3
 * getRankOfNumber(l) 0
 * getRankOfNumber(3) = 1
 * getRankOfNumber(4) 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
 * The data structure I will choose is a balanced sorted binary tree (AVL).
 * Insertion time will O(ln(N)) where N is the number of nodes in the tree.
 * Rank functon will take O(ln(N)), where N is the number of nodes in the tree.
 */
typedef struct trees
{
	struct trees * l;
	struct trees * r;
	int size;	/* use it for rank calc */
	int depth;	/* use it to balance the tree */
	int data;	/* the actual data stored in the tree */
} tree;

int getRankOfNumber(tree * t, int data);
bool track(tree * t, int data);
tree * new_node(int data);
void update_size_depth(tree * t);
void free_tree(tree * t);

int main()
{
	tree * t = new_node(5);
	track(t, 1);
	track(t, 4);
	track(t, 4);
	track(t, 5);
	track(t, 9);
	track(t, 7);
	track(t, 13);
	track(t, 3);
	printf("rank of 1 is %d.\n", getRankOfNumber(t, 1));
	printf("rank of 3 is %d.\n:", getRankOfNumber(t, 3));
	printf("rank of 4 is %d.\n:", getRankOfNumber(t, 4));

	free_tree(t);

	return 0;
}

/* this method will insert data in the tree */
/* will return true if data is not in the tree already (and thus was added) */
/* depth_added will b 1 if the depth of the tree increased by 1 */
/* 0 otherwise */
bool track(tree * t, int data)
{
	if (t->data == data)
	{
		return false;
	}
	/* some base cases */
	if (!t->l)
	{
		tree * node = new_node(data);
		if (data > t->data)
		{
			node->data = t->data;
			t->data = data;
		}
		t->l = node;
		t->depth += (t->r ? 0:1);
		t->size ++;
		return true;
	}
	if (!t->r)
	{
		tree * node = new_node(data);
		if (data < t->data)
		{
			node->data = t->data;
			t->data = data;
		}
		t->r = node;
		t->depth += (t->l ? 0 : 1);
		t->size ++;
		return true;
	}
	
	/* general case: t has both right and left subtrees */	
	bool res;
	if (t->data > data)
	{
		res = track(t->l, data);
	}
	else
	{
		res = track(t->r, data);
	}

	if (!res)
	{
		return false;
	}

	t->size ++;
	/* rebalance if necessary */
	if (t->l->depth > t->r->depth + 1)
	{
		/* move the left subtree to the right of t */
		tree * l = t->l, * r = t->r;
		int tmp = t->data;
		t->data = l->data;
		l->data = tmp;

		t->l = l->l;
		t->r = l;

		l->l = l->r;
		l->r = r;

		/* update the size and depth for l and t (r did not change )*/
		update_size_depth(t);
		update_size_depth(l);
	}
	else if (t->l->depth + 1 < t->r->depth)
	{
		/* the right node will become the left node */
		tree * l = t->l, * r = t->r;
		int tmp = t->data;
		t->data = r->data;
		r->data = tmp;

		t->l = r;
		t->r = r->r;

		r->r = r->l;
		r->l=l;

		/* update the size and depth for t an r (l did not change) */
		update_size_depth(t);
		update_size_depth(r);
	}
	else
	{
		update_size_depth(t);
	}

	return true;
}

/* t is a binary search tree */
/* returns the number of items in the tree smaller or equal to data */
int getRankOfNumber(tree * t, int data)
{
	if (!t)
	{
		return 0;
	}
	
	if (data < t->data)
	{
		return (getRankOfNumber(t->l, data));
	}
	if (data == t->data)
	{
		if (t->l)
		{
			return t->l->size + 1;
		}
		else
		{
			return 1;
		}
	}
	int res = getRankOfNumber(t->r, data) + 1; /* +1 for the root which is smaller than the number */
	if (t->l)
	{
		res += t->l->size;
	}
	return res;
}

void free_tree(tree * t)
{
	if (!t)
	{
		return;
	}
	free_tree(t->l);
	free_tree(t->r);
	free(t);
}

tree * new_node(int data)
{
	tree * res = (tree *) malloc(sizeof(tree));
	memset(res, 0, sizeof(tree));
	res->data = data;
	res->size = 1;
	res->depth = 1;
	return res;
}

void update_size_depth(tree * t)
{
	int size = 0, depth = 0;
	if (t->l)
	{
		size += t->l->size;
		depth += t->l->depth;
	}
	if (t->r)
	{
		size += t->r->size;
		if (t->r->depth >= depth)
		{
			depth = t->r->depth;
		}
	}
	t->size = size + 1;
	t->depth = depth + 1;
}