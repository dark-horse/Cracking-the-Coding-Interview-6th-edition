/*
 *
 * First Common Ancestor: Design an algorithm and write code to find the first common ancestor
 * of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not
 * necessarily a binary search tree.
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
tree * common_ancestor(tree * t, tree * n_1, tree * n_2);
tree * common_ancestor_helper(tree * t, tree * n_1, tree * n_2, bool * t_contains_n_1, bool * t_contains_n_2);

/* "administrative" functions for tree */
tree * build_tree();
tree * create_tree_node(int data);
void free_tree(tree * t);

int main()
{
	tree * t = build_tree();
	tree * common = t->right;
	tree * res = common_ancestor(t, common->left->left, common->right->left);
	if (res == common)
	{
		printf("test passed: common ancestor is %d.\n", common->data);
	}
	else
	{
		printf("test failed: expect common ancestor %d and we got %d.\n", common->data, res ? res->data : -1);
	}

	free_tree(t);
	return 0;
}

/* the function for this assignment */
/* this function will return the common ancestor for n_1 and n_2 if it exists in the binary tree t */
/* the function will keep track of whether or not t contains n_1 and/or t contains n_2 */
/* if any of n_1 and n_2 is NULL common ancestor is NULL */
tree * common_ancestor(tree * t, tree * n_1, tree * n_2)
{
	if (!n_1 || !n_2)
	{
		return NULL;
	}

	bool t_contains_n_1 = false, t_contains_n_2 = false;
	return common_ancestor_helper(t, n_1, n_2, & t_contains_n_1, &t_contains_n_2);
}

tree * common_ancestor_helper(tree * t, tree * n_1, tree * n_2, bool * t_contains_n_1, bool * t_contains_n_2)
{
	/* some base cases */
	if (!t || (t->left == NULL && t->right == NULL))
	{
		*t_contains_n_1 = (t == n_1);
		*t_contains_n_2 = (t == n_2);
		return NULL;
	}

	/* see if the left subtree contains any of n_1 and n_2 */
	bool l_contains_n_1 = false, l_contains_n_2 = false;
	tree * res = common_ancestor_helper(t->left, n_1, n_2, &l_contains_n_1, &l_contains_n_2);

	if (res)
	{
		/* found the ancestor */
		/* should assert that l_contains_n_1 and l both n_1 and n_2 */
		return res;
	}

	if ( (l_contains_n_1 && t == n_2) || (l_contains_n_2 && t == n_1))
	{
		/* the root is the first common ancestor */
		*t_contains_n_1 = true;
		*t_contains_n_2 = true;
		return t;
	}
	
	/* have to look into the right sub_tree */
	bool r_contains_n_1 = false, r_contains_n_2 = false;
	res = common_ancestor_helper(t->right, n_1, n_2, &r_contains_n_1, &r_contains_n_2);
	
	if (res)
	{
		/* found the ancestor */
		/* should assert that subtree contains both n_1 and n_2 */
		return res;
	}
	
	if ( (l_contains_n_1 && r_contains_n_2) || (l_contains_n_2 && r_contains_n_1))
	{
		/* the root is the first common ancestor */
		*t_contains_n_1 = true;
		*t_contains_n_2 = true;
		return t;
	}
	
	/* no common ancestor in this tree. */
	/* update the t_contains_n_* booleans */
	* t_contains_n_1 = l_contains_n_1 || r_contains_n_1 || t == n_1;
	* t_contains_n_2 = l_contains_n_2 || r_contains_n_2 || t == n_2;

	return NULL;
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
	res->left->left->right = create_tree_node(11);
	res->left->left->left = create_tree_node(12);
	res->left->right->right = create_tree_node(13);
	res->left->right->left = create_tree_node(14);
	return res;
}