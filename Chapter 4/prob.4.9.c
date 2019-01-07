/*
 *
 * BST Sequences: A binary search tree was created by traversing through an array from left to right
 * and inserting each element. Given a binary search tree with distinct elements, print all possible
 * arrays that could have led to this tree.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

/* the binary tree */
typedef struct trees
{
	int data;
	struct trees * left;
	struct trees * right;
} tree;

typedef struct stacks
{
	tree ** arr;
	unsigned int stack_sz;
	unsigned int alloc_sz;
} stack;

/***************************************/
/*         ASSIGNMENT FUNCTION         */
/***************************************/
void print_solutions(tree * t, int * arr, int arr_sz, int arr_offset, stack * s, bool reload_stack);

/***************************************/
/*           TREE FUNCTIONS            */
/***************************************/
tree * create_tree_node(int data);
void insert_data(tree * t, int data);
void print_tree(tree * t);
void free_tree(tree * t);
void print_array(int * arr, int arr_sz);
bool check_bst(tree *t, int * max);
bool equal_trees(tree *t1, tree * t2);

/***************************************/
/*           STACK FUNCTIONS           */
/***************************************/
stack * create_stack();
void push(stack * s, tree * t);
bool isEmpty(stack * s);
tree * pop(stack * s);
tree * top(stack *s);
void free_stack(stack * s);

tree * test_tree;

int main()
{
	test_tree = create_tree_node(20);
	insert_data(test_tree, 10);
	insert_data(test_tree, 5);
	insert_data(test_tree, 15);
	insert_data(test_tree, 30);
	insert_data(test_tree, 25);
	insert_data(test_tree, 40);
	insert_data(test_tree, 14);
	insert_data(test_tree, 16);
	int * arr = (int*) malloc(9*sizeof(int));
	stack *s = create_stack();
	print_solutions(test_tree, arr, 9, 0, s, false);
	
	free(arr);
	free_tree(test_tree);
	free_stack(s);
	
	return 0;
}

/***************************************/
/*         ASSIGNMENT FUNCTION         */
/***************************************/
void print_solutions(tree * t, int * arr, int arr_sz, int arr_offset, stack * s, bool reload_stack)
{
	if (!t)
	{
		return;
	}
	arr[arr_offset] = t->data;
	/* base case */
	if (arr_offset + 1 == arr_sz)
	{
		printf("Print array\n**************************\n");
		print_array(arr, arr_sz);
		printf("**************************\n");
		tree * check_tree = create_tree_node(arr[0]);
		for (int i = 1; i < arr_sz; i++)
		{
			insert_data(check_tree, arr[i]);
		}
		printf("calculated array leads to same tree: %s\n", equal_trees(test_tree, check_tree) ? "TRUE\0" : "FALSE\0");
		free_tree(check_tree);
		return;
	}
	if (!t->left && !t->right)
	{
		/* leaf node */
		if (!isEmpty(s))
		{
			tree * sub_t = pop(s);
			print_solutions(sub_t, arr, arr_sz, arr_offset + 1, s, reload_stack);
			if (reload_stack)
			{
				push(s, sub_t);
			}
		}
		return;
	}
	bool reload_sub_stack = t->left && t->right;
	if (t->left)
	{
		if (t->right)
		{
			push(s, t->right);
		}
		print_solutions(t->left, arr, arr_sz, arr_offset + 1, s, reload_sub_stack);
		if (t->right)
		{
			pop(s);
		}
	}
	if (t->right)
	{
		if (t->left)
		{
			push(s, t->left);
		}
		print_solutions(t->right, arr, arr_sz, arr_offset + 1, s, reload_sub_stack);
		if (t->left)
		{
			pop(s);
		}
	}
}

/***************************************/
/*      ADMINISTRATIVE FUNCTIONS       */
/***************************************/
void free_tree(tree * t)
{
	if (!t)
	{
		return;
	}
	free_tree(t->left);
	free_tree(t->right);
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

/* PRE  - t is binary search tree */
/* POST - t is binary search tree */
void insert_data(tree * t, int data)
{
	if (t->data == data)
	{
		return;
	}
	if (t->data > data)
	{
		/*insert on the left subtree */
		if (t->left)
		{
			insert_data(t->left, data);
		}
		else
		{
			tree * t_node = create_tree_node(data);
			t->left = t_node;
		}
	}
	else
	{
		/*insert on the right subtree */
		if (t->right)
		{
			insert_data(t->right, data);
		}
		else
		{
			tree * t_node = create_tree_node(data);
			t->right = t_node;
		}
	}
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

void print_array(int * arr, int arr_sz)
{
	if (!arr_sz || !arr)
	{
		return;
	}
	printf("%d",arr[0]);
	for (int i = 1; i < arr_sz; i ++)
	{
		printf(" ,%d",arr[i]);
	}
	printf("\n");
}

/* returns true if t is a binary search tree (bst) */
bool check_bst(tree * t, int * max)
{
	*max = INT_MIN;
	if (!t)
	{
		return true;
	}

	bool res;
	int max_subtree;
	res = check_bst(t->left, &max_subtree);
	res = res && (t->data > max_subtree);
	if (!res)
	{
		return false;
	}
	*max = t->data;
	if (!t->right)
	{
		return true;
	}
	res = check_bst(t->right, &max_subtree);
	res = res & (max_subtree > t->data);
	if (!res)
	{
		*max = INT_MIN;
		return false;
	}
	*max = max_subtree;
	return true;
}

bool equal_trees(tree *t1, tree * t2)
{
	if (!t1 && !t2)
	{
		return true;
	}
	if ( (!t1 && t2) || (t1 && !t2))
	{
		return false;
	}
	if (t1->data != t2->data)
	{
		return false;
	}
	if (!equal_trees(t1->left,t2->left))
	{
		return false;
	}
	return equal_trees(t1->right, t2->right);
}

/***************************************/
/*           STACK FUNCTIONS           */
/***************************************/
stack * create_stack()
{
	stack * s = (stack *) malloc(sizeof(stack));
	s->alloc_sz = 32;
	s->arr = (tree **) malloc(s->alloc_sz * sizeof(tree *));
	s->stack_sz = 0;
	return s;
}
void push(stack * s, tree * t)
{
	if (s->stack_sz == s->alloc_sz)
	{
		s->alloc_sz = s->alloc_sz  * 2;
		s->arr = (tree **) realloc(s->arr, s->alloc_sz * (sizeof(tree *)));
	}
	s->arr[s->stack_sz] = t;
	s->stack_sz ++;
}

bool isEmpty(stack * s)
{
	return s->stack_sz == 0;
}

tree * pop(stack * s)
{
	if (!s->stack_sz)
	{
		return s->arr[0];		/* what's a good error code ? */
	}
	s->stack_sz --;
	return s->arr[s->stack_sz];
}

tree * top(stack *s)
{
	if (s->stack_sz)
	{
		return s->arr[s->stack_sz-1];
	}
	else
	{
		return s->arr[0];	/* what's a good error code */
	}
}

void free_stack(stack * s)
{
	free(s->arr);
	free(s);
}