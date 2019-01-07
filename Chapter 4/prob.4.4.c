/*
 *
 * Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of
 * this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of any
 * node never differ by more than one.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* the binary tree */
typedef struct trees
{
	int data;
	struct trees * left;
	struct trees * right;
} tree;

/* the function for this assignment */
bool check_balanced(tree * t);

/* "administrative" functions for tree */
int tree_depth(tree * t);
tree * build_tree();
tree * create_tree_node(int data);
void free_tree(tree * t);

int main()
{
	tree * t = build_tree();
	printf ("tree is %sbalanced.\n", check_balanced(t) ? "" : "NOT ");
	free_tree(t);
	return 0;
}

bool check_balanced(tree * t)
{
	if (!t)
	{
		return true;
	}
	int l_depth = tree_depth(t->left);
	int r_depth = tree_depth(t->right);
	return (l_depth - r_depth) > -2 && (l_depth - r_depth) < 2;
}

int tree_depth(tree * t)
{
	if (!t)
	{
		return 0;
	}
	int l_depth = tree_depth(t->left);
	int r_depth = tree_depth(t->right);
	return (l_depth > r_depth) ? l_depth + 1 : r_depth + 1;
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

tree * create_tree_node(int data)
{
	tree * res = (tree *) malloc(sizeof(tree));
	res->data = data;
	res->left = NULL;
	res->right = NULL;
	return res;
}

tree * build_tree()
{
	/* top node (level 1) */
	tree * res = create_tree_node(0);
	
	/* level 2 in the tree */
	res->left = create_tree_node(1);
	res->right = create_tree_node(2);

	/* level 3 in the tree */
	res->left->left = create_tree_node(3);
	res->left->right = create_tree_node(4);
	res->right->left = create_tree_node(5);
	res->right->right = create_tree_node(6);
	
	/* level 4 in the tree */
	res->right->left->right = create_tree_node(7);
	res->right->left->left = create_tree_node(8);
	res->right->right->right = create_tree_node(9);
	res->right->right->left = create_tree_node(10);
#if 0
	res->left->left->right = create_tree_node(11);
	res->left->left->left = create_tree_node(12);
	res->left->right->right = create_tree_node(13);
	res->left->right->left = create_tree_node(14);
#endif
	return res;
}