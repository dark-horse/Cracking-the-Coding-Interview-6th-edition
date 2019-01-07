/*
 *
 * Paths with Sum: You are given a binary tree in which each node contains an integer value (which
 * might be positive or negative). Design an algorithm to count the number of paths that sum to a
 * given value. The path does not need to start or end at the root or a leaf, but it must go downwards
 * (traveling only from parent nodes to child nodes).
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
} tree;


/* the function for this assignment */
int paths_count(tree * t, int target);
int paths_count_root(tree * t, int target);

/* "administrative" functions for this exercise */
tree * build_tree();
tree * create_tree_node(int data);
void print_tree(tree * t);
void free_tree(tree * t);

int main()
{
	tree * t = build_tree();
	printf("input a number on a line to check if the tree has paths that sum to the number.\n");
	printf("to end the program type \"q\" or Ctrl-C.\n");
	int input = 0;
	int sign = 1;
	while(true)
	{
		char c = getchar();
		if (c == 'q')
		{
			break;
		}
		if (c=='\n')
		{
			input = input * sign;
			printf("number inputed to check is :%d. There are %d paths in the tree that sum to it.\n", input, paths_count(t, input));
			input = 0;
			sign = 1;
		}
		if (c == '-')
		{
			sign = -1;
		}
		if (c <= '9' && c >= '0')
		{
			input = input * 10;
			input += (int) (c-'0');
		}
	}
	
	free_tree(t);
	return 0;
}

/* There may be a mis-understanding with how this problem was stated */
/* The algorithm below finds the number of un-interupted sequences of nodes from top to bottom that sum to target */
/* However, someone may think a path does not have to be an un-interupted sequence of nodes */

/* I don't think the algorithm can run faster than O(n-squared) where n is the number of nodes. */
/* Taking the simplest binary tree - one which has only left nodes. It is the equivalent of a linked list */
/* The algorithm will have to consider all 1-long paths - there are n of these */
/* Then all 2-long paths - there are n-1 of these. Then all 3-long paths - n-2 of these */
/* Altogether, the algorithm will have to consider n * (n-1) / 2 paths: O(n-square) */

/* the number of paths in the tree that sum to the target, not necessarily starting at the root */
int paths_count(tree * t, int target)
{
	/* some base cases */
	if (!t)
	{
		return 0;
	}

	if (!t->left && !t->right)
	{
		return (target == t->data) ? 1 : 0;
	}

	int res = (t->data == target) ? 1 : 0;
	if (t->left)
	{
		res += paths_count(t->left, target);
		res += paths_count_root(t->left, target - t->data);
	}

	if (t->right)
	{
		res += paths_count(t->right, target);
		res += paths_count_root(t->right, target - t->data);
	}

	return res;
}


/* the number of paths that sum to target that start at the root */
int paths_count_root(tree * t, int target)
{
	/* some base cases */
	if (!t)
	{
		return 0;
	}
	
	if (!t->left && !t->right)
	{
		return (target == t->data) ? 1 : 0;
	}
	
	int res = (t->data == target) ? 1 : 0;
	
	if (t->left)
	{
		res += paths_count_root(t->left, target - t->data);
	}
	if (t->right)
	{
		res += paths_count_root(t->right, target - t->data);
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
	tree * res = create_tree_node(1);
	
	/* level 2 in the tree */
	res->left = create_tree_node(1);
	res->right = create_tree_node(1);

	/* level 3 in the tree */
	res->left->left = create_tree_node(1);
	res->left->right = create_tree_node(1);
	res->right->left = create_tree_node(1);
	res->right->right = create_tree_node(1);
	
	/* level 4 in the tree */
	res->right->left->right = create_tree_node(1);
	res->right->left->left = create_tree_node(1);
	res->right->right->right = create_tree_node(1);
	res->right->right->left = create_tree_node(1);
	res->left->left->right = create_tree_node(1);
	res->left->left->left = create_tree_node(1);
	res->left->right->right = create_tree_node(1);
	res->left->right->left = create_tree_node(1);

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