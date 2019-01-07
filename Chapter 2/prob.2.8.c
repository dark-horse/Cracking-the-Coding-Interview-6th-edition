/*
 *
 * Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
 * beginning of the loop.
 * DEFINITION
 * Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier node, so
 * as to make a loop in the linked list.
 * EXAMPLE
 * Input: A -> B -> C - > D -> E -> C [the same C as earlier]
 * Output: C
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct nodes
{
	int data;
	struct nodes * next;
} node;

node * find_loop_start(node * head);
int find_loop_length(node * head);


/* administrative functions */
node * build_circular_list(int list_sz, int loop_sz);
void free_list(node * head, node * loop_start);

int main()
{
	node * head = build_circular_list(10 /*list_sz*/, 5 /*loop_sz*/);
	node * loop_start = find_loop_start(head);
	printf("loop start node %d.\n", loop_start->data);
	free_list(head, loop_start);
	return 0;
}

node * find_loop_start(node * head)
{
	/* some base cases */
	if (!head)
	{
		return NULL;
	}
	if (head == head->next || head == head->next->next)
	{
		return head;
	}
	
	if (head->next == head->next->next)
	{
		return head->next;
	}

	int loop_len = find_loop_length(head);
	node * res = head, * traverse_pointer = head;
	for (int i = 0; i < loop_len-1; i ++)
	{
		traverse_pointer = traverse_pointer->next;
	}
	while (res != traverse_pointer->next)
	{
		res = res->next;
		traverse_pointer = traverse_pointer->next;
	}
	
	return res;
}

/* this algorithm will have two stages: */
/* 1st stage: use two pointers, once which advances 2 nodes at a time,  */
/*            the other advances 1 node at a time. They will meet somewhere */
/*            in the loop*/
/* 2nd stage: advance a pointer 1 node at a time until the meeting point */
/*           the number of steps will be the length of the loop */
int find_loop_length(node*head)
{
	/* a few base cases */
	if (head->next == head || head->next->next == head->next)
	{
		return 1;
	}
	if (head->next->next == head)
	{
		return 2;
	}

	node * one_node = head->next, * two_nodes = head->next->next;
	while (one_node != two_nodes)
	{
		one_node = one_node->next;
		two_nodes = two_nodes->next->next;
	}
	
	node * meeting_point = one_node, * traverse_pointer = one_node->next;
	int loop_len = 1;
	while (traverse_pointer != meeting_point)
	{
		loop_len ++;
		traverse_pointer = traverse_pointer->next;
	}
	
	return loop_len;
}

void free_list(node * head, node * loop_start)
{
	while (head)
	{
		node * next = head->next;
		free(head);
		head = next;
	}
}

node * build_circular_list(int list_sz, int loop_sz)
{
	if (list_sz == 0)
	{
		return NULL;
	}
	
	if (loop_sz > list_sz)
	{
		return NULL;
	}

	node * head = (node *) malloc(sizeof(node));
	head->data = 1;
	head->next = NULL;
	node * end = head; /* we will keep adding at the front, so the end of the linked list will be the first node we add */
	node * loop_start = NULL;
	if (list_sz == 1)
	{
		head->next = head;
		return head;
	}

	for (int i = 1; i < list_sz; i++)
	{
		node * n = (node*) malloc(sizeof(node));
		n->data = 1 + i + 1;
		n->next = head;
		head = n;
		
		if (i == list_sz - loop_sz)
		{
			loop_start = head;
		}
	}
	
	end->next = loop_start;

	return head;
}