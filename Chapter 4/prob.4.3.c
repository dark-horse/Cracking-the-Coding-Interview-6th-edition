/*
 *
 * List of Depths: Given a binary tree, design an algorithm which creates a linked list of all the nodes
 * at each depth (e.g., if you have a tree with depth D, you'll have D linked lists.)
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

/* the linked list */
typedef struct nodes
{
	int data;
	struct nodes * next;
} node;

/* list of linked list */
typedef struct lists
{
	node * list;
	struct lists * next;
} list_of_lists;

/* the function for this assignment */
list_of_lists * lists_from_tree(tree * t);

/* "administrative" functions for tree */
tree * build_tree();
tree * create_tree_node(int data);
void free_tree(tree * t);

/* "administrative" functions for the list of lists */
void print_lists_of_lists(list_of_lists * lists);
void free_list_of_lists(list_of_lists * lists);
void free_linked_list(node * head);

int main()
{
	tree * check = build_tree();
	list_of_lists * list = lists_from_tree(check);
	printf("print the list of lists\n");
	print_lists_of_lists(list);
	free_tree(check);
	free_list_of_lists(list);
	return 0;
}

list_of_lists * lists_from_tree(tree * t)
{
	if (!t)
	{
		return NULL;
	}
	
	list_of_lists * res = (list_of_lists *) malloc(sizeof(list_of_lists));
	node * list = (node *) malloc(sizeof(node)); 
	list->data = t->data;
	list->next = NULL;
	res->list = list;
	res->next = NULL;
	list_of_lists * res_end = res; /* we will add lists at the end of the result list */
	
	list_of_lists * l = lists_from_tree(t->left);
	list_of_lists * r = lists_from_tree(t->right);
	
	/* traverse the lists of lists from left and right and snap them together */
	while (l || r)
	{
		if (l && l->list)
		{
			/* snap r at the end of l */
			node * traverse_l = l->list;
			while (traverse_l->next)
			{
				traverse_l = traverse_l->next;
			}
			if (r)
			{
				traverse_l->next = r->list;
			}
			else
			{
				traverse_l->next = NULL;
			}
			/* add l to the end of the current list */
			res_end->next = l;
		}
		else
		{
			res_end->next = r;
		}
		/* advance l and r */
		if (l)
		{
			l = l->next;
		}
		if (r)
		{
			r = r->next;
		}
		
		res_end = res_end->next;
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

void print_lists_of_lists(list_of_lists * list)
{
	int i = 1; /* for printing we will use 1-based level */
	while (list)
	{
		printf("level %d:", i);
		node * list_beg = list->list;
		if (list_beg)
		{
			printf("\t%d", list_beg->data);
			list_beg = list_beg->next;
		}
		while(list_beg)
		{
			printf(",\t%d", list_beg->data);
			list_beg = list_beg->next;
		}
		printf(".\n");
		
		list = list->next;

		i ++;
	}
}

void free_list_of_lists(list_of_lists * list)
{
	while (list)
	{
		list_of_lists * next = list->next;
		free_linked_list(list->list);
		free(list);
		list = next;
	}
}

void free_linked_list(node * head)
{
	while (head)
	{
		node * next = head->next;
		free(head);
		head = next;
	}
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
