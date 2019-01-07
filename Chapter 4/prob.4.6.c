/*
 *
 * Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a
 * binary search tree. You may assume that each node has a link to its parent.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* the binary tree */
typedef struct trees
{
	int data;
	struct trees * left;
	struct trees * right;
	struct trees * parent;
} tree;


/* the function for this assignment */
tree * next(tree * t);

/* "administrative" functions for this exercise */
tree * build_tree();
tree * create_tree_node(int data, tree * parent);
void print_tree(tree * t);
void free_tree(tree * t);
void print_res(tree * in, tree *res);

int main()
{
	tree * t = build_tree();
	tree * test_node = t, * res = NULL;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->left->left->left;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->left->left->right;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->right->right->left;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->right->right;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->right->right->right;
	res = next(test_node);
	print_res(test_node, res);

	test_node = t->left;
	res = next(test_node);
	print_res(test_node, res);

	free_tree(t);
	return 0;
}

tree * next (tree * t)
{
	/* some base cases */
	if (!t)
	{
		return NULL;
	}
	if (t->right)
	{
		/* navigate left on the right subtree as much as possible */
		tree * res = t->right;
		while (res->left)
		{
			res = res->left;
		}
		return res;
	}
	if (!(t->parent))
	{
		/*root tree with no right subtree */
		return NULL;
	}
	if (t->parent->left == t)
	{
		return t->parent;
	}
	/* t has no right subtree and t is the right subtree of its parent */
	/* go up the parent chain until the first parent from which this is the left sub tree */
	tree * parent = t->parent;
	tree * res = NULL;
	while (parent)
	{
		if (parent->left == t)
		{
			res = parent;
			break;
		}
		t = parent;
		parent = t->parent;
	}

	return res;
}

void free_tree(tree * t)
{
	if (!t)
	{
		return;
	}
	if (t->left)
	{
		free_tree(t->left);
	}
	if (t->right)
	{
		free_tree(t->right);
	}
	free(t);
}

tree * create_tree_node(int data, tree * parent)
{
	tree * res = (tree *) malloc(sizeof(tree));
	res->data = data;
	res->left = NULL;
	res->right = NULL;
	res->parent = parent;
	return res;
}

tree * build_tree()
{
	/* insert in such way that the tree ends up binary search tree */
	/* top node (level 1) */
	tree * res = create_tree_node(100, NULL);
	
	/* level 2 in the tree */
	res->left = create_tree_node(50, res);
	res->right = create_tree_node(150, res);

	/* level 3 in the tree */
	res->left->left = create_tree_node(25,res->left);
	//res->left->right = create_tree_node(75,res->left);
	res->right->left = create_tree_node(125,res->right);
	res->right->right = create_tree_node(175,res->right);
	
	/* level 4 in the tree */
	res->right->left->right = create_tree_node(140,res->right->left);
	res->right->left->left = create_tree_node(110,res->right->left);
	res->right->right->right = create_tree_node(200,res->right->right);
	res->right->right->left = create_tree_node(160,res->right->right);
	res->left->left->right = create_tree_node(40,res->left->left);
	res->left->left->left = create_tree_node(15,res->left->left);
	//res->left->right->right = create_tree_node(85,res->left->right);
	//res->left->right->left = create_tree_node(60,res->left->right);

	return res;
}

/* prints the tree in pre-order traversal */
/* first print the root then the left then the right */
void print_tree(tree * t)
{
	if (!t)
	{
		return;
	}
	printf(" %d", t->data);
	print_tree(t->left);
	print_tree(t->right);
}

void print_res(tree * in, tree * res)
{
	printf("input tree %d generates result ",in->data);
	if (res)
	{
		printf("%d.\n", res->data);
	}
	else
	{
		printf("NULL.\n");
	}
}