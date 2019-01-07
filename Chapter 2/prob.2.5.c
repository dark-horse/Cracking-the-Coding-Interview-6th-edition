/*
 * You have two numbers represented by a linked list, where each node contains a single
 * digit. The digits are stored in reverse order, such that the 1 's digit is at the head of the list. Write a
 * function that adds the two numbers and returns the sum as a linked list.

 * FOLLOW UP
 * Suppose the digits are stored in forward order. Repeat the above problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct nodes
{
	int data;
	struct nodes * next;
} node;

node * add_lists(node * add1, node * add2, bool reverse_order);
int int_from_list(node * head, bool reverse_order);
node * list_from_int(int val, bool reverse_order);
node * build_list(int list_sz, bool random, bool duplicates);
void free_list(node * head);
void print_list(node * head);

int main()
{
	node * add1 = build_list(5 /*list_sz*/, true /*random*/, false/*duplicates*/);
	node * add2 = build_list(5 /*list_sz*/, true /*random*/, false /*duplicates*/);
	printf("add 1 list\n");
	print_list(add1);
	printf("int from list for list 1 %d.\n",int_from_list(add1, false /*reverse_order*/));
	printf("add 2 list\n");
	print_list(add2);
	printf("int from list for list 2 %d.\n",int_from_list(add2, false /*reverse_order*/));
	node * res = add_lists(add1, add2, true /*reverse_order*/);
	printf("result of reverse order addition\n");
	print_list(res);
	
	free_list(res);
	res = add_lists(add1, add2, false /*reverse_order*/);
	printf("result of forward order addition.\n");
	print_list(res);

	free_list(add1);
	free_list(add2);
	free_list(res);
	return 0;
}

int int_from_list(node * head, bool reverse_order)
{
	int res = 0;
	int curr_index = 0;
	int power_of_ten = 1;
	while (head)
	{
		int dig = head->data;
		if (reverse_order)
		{
			res += dig * power_of_ten;
			power_of_ten = power_of_ten * 10;
		}
		else
		{
			res = res * 10;
			res += dig;
		}
		curr_index ++;
		head = head->next;
	}
	
	return res;
}

/*assume val is an integer greater than 0 */
node * list_from_int(int val, bool reverse_order)
{
	node * head = (node *) malloc(sizeof(node));
	node * tail;
	int dig = val % 10;
	val = (val - dig) / 10;
	
	head->data = dig;
	head->next = NULL;
	tail = head;
	while (val)
	{
		dig = val % 10;
		val = (val - dig) / 10;
		node * dig_node = (node *) malloc(sizeof(node));
		dig_node->data = dig;
		if (reverse_order)
		{
			/* add the digit at the end of the list */
			tail->next = dig_node;
			dig_node->next = NULL;
			tail = dig_node;
		}
		else
		{
			/* add the digit at the beginning of the list */
			dig_node->next = head;
			head = dig_node;
		}
	}
	
	return head;
}

node * add_lists(node * add1, node * add2, bool reverse_order)
{
	int i1 = int_from_list(add1, reverse_order);
	int i2 = int_from_list(add2, reverse_order);
	return list_from_int(i1+i2, reverse_order);
}

void free_list(node * head)
{
	while (head)
	{
		node * next = head->next;
		free(head);
		head = next;
	}
}

node * build_list(int list_sz, bool random, bool duplicates)
{
	if (list_sz == 0)
	{
		return NULL;
	}
	
	if (random)
	{
		srand(time(NULL));
	}
	
	node * head = (node *) malloc(sizeof(node));
	head->data = 1;
	head->next = NULL;
	node * end = head;
	
	for (int i = 1; i < list_sz; i ++)
	{
		node * next = (node *) malloc(sizeof(node));
		int val;
		if (random)
		{
			/* for this problem all the integers in the list are digits from 0 to 9 */
			val = rand() % 10;
		}
		else
		{
			/* for this problem all the integers in the list are digits from 0 to 9 */
			val = (i + 1) % 10;
		}
		
		next->data = val;
		
		/* add at the end of the list */
		end->next = next;
		next->next = NULL;
		end = next;
		if (duplicates)
		{
			next = (node *) malloc(sizeof(node));
			next->data = val;
			end->next = next;
			next->next = NULL;
			end = next;
		}
	}
	return head;
}

void print_list(node * head)
{
	if (head == NULL)
	{
		printf ("empty list.\n");
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