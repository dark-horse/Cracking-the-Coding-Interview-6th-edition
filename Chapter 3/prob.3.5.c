/*
 *
 * Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use
 * an additional temporary stack, but you may not copy the elements into any other data structure
 * (such as an array). The stack supports the following operations: push, pop, peek, and is Empty.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

typedef struct nodes
{
	int data;
	struct nodes * next;
} node;

typedef struct stacks
{
	node * head;
} stack;

stack * create_stack();
void push(stack * s, int item);
int pop(stack * s);
int peek(stack * s);
bool is_empty(stack * s);
void free_stack(stack * s);
void print_stack(stack * s);
void sort_stack(stack * input, stack * tmp_stack);
void add_rand_items(stack *s, int items_count);

int main()
{
	stack * s = create_stack();
	stack * tmp_stack = create_stack();
	add_rand_items(s, 20);
	printf("the stack before sorting.\n");
	print_stack(s);
	sort_stack(s, tmp_stack);
	printf("stack after sorting.\n");
	print_stack(s);
	free_stack(s);
	free_stack(tmp_stack);
	return 0;
}

/* this function will sort the input stack, using only the additional temporary stack. */
/* the algorithm complexity will be O(n^2) where 'n' is the number of input items. */
/* the stack will be sorder in ascending order (meaning poping the stack will output */
/* items in sorted order */
void sort_stack(stack * input, stack * tmp_stack)
{
	if (is_empty(input))
	{
		return;
	}

	/* first find out the input size */
	int input_sz = 0;
	while (!is_empty(input))
	{
		int item = pop(input);
		push(tmp_stack, item);
		input_sz ++;
	}
	
	/* now the input stack is empty, and the tmp stack is the reverse of the input stack */
	for (int i = 0; i < input_sz; i ++)
	{
		int max_value = INT_MIN;
		for (int j = 0; j < input_sz - i ; j ++)
		{
			int val = pop(tmp_stack);
			push(input, val);
			if (val > max_value)
			{
				max_value = val;
			}
		}
		/* input stack has all the items, and tmp_stack is empty */
		bool found_max = false;
		for (int j = 0; j < input_sz - i; j++)
		{
			int val = pop(input);
			if (val == max_value)
			{
				found_max = true;
			}
			
			if (val != max_value || found_max)
			{
				push(tmp_stack, val);
			}
		}
		push(input, max_value);
		/* now input stack has the "i"th greatest items and tmp_stack has "input_sz - i" items */
	}
}

stack * create_stack()
{
	stack * res = (stack *) malloc(sizeof(stack));
	res->head = NULL;
	return res;
}

void push(stack * s, int item)
{
	if (!s)
	{
		return;
	}

	node * add_node = (node *) malloc(sizeof(node));
	add_node->data = item;
	add_node->next = s->head;
	s->head = add_node;
}

int pop(stack * s)
{
	if (!s || !s->head)
	{
		return 0;	/* how do we return errors with this interface ????*/
	}
	int res = s->head->data;
	node * tmp = s->head;
	s->head = tmp->next;
	free(tmp);
	return res;
}

int peek(stack *s)
{
	if (!s || !s->head)
	{
		return 0;	/* how do we return errors with this interface ????*/
	}
	
	return s->head->data;
}

bool is_empty(stack * s)
{
	return (s == NULL || s->head == NULL);
}

void free_stack(stack * s)
{
	if (!s)
	{
		return;
	}
	
	node * head = s->head;
	while (head)
	{
		node * next = head->next;
		free(head);
		head = next;
	}
	
	free(s);
}

void print_stack(stack * s)
{
	if (s == NULL)
	{
		printf ("NULL stack.\n");
		return;
	}
	
	node * head = s->head;
	if (!head)
	{
		printf ("Empty stack.\n");
		return;
	}

	printf("\n********************************\n");
	
	printf("%d", head->data);
	head = head->next;
	while (head)
	{
		printf("\t-> %d", head->data);
		head = head->next;
	}
	printf("\n********************************\n");
}

void add_rand_items(stack * s, int items_count)
{
	srand(time(NULL));
	for (int i = 0; i < items_count; i ++)
	{
		int r = rand() % 150;
		push(s, r);
	}
}
