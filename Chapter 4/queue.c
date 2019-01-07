/*
 * Implementation file for a simple queue object.
 * Used for breath first traversal.
 */

#include <string.h>
#include <stdlib.h>
#include "queue.h"


queue * create_empty_queue()
{
	queue * res = (queue *) malloc(sizeof(queue));
	memset(res, 0, sizeof(queue));
	return res;
}

void free_queue(queue * q)
{
	if (!q)
	{
		return;
	}
	list * l = q->l;
	while (l)
	{
		list * prev = l;
		l = l->next;
		free(prev);
	}
	
	free(q);
}

bool isEmpty(queue * q)
{
	return (!q || !(q->l));
}

void enqueue(queue * q, void * d)
{
	list * new_node = (list *) malloc(sizeof(list));
	new_node-> d = d;
	new_node->next = NULL;
	/* add it at the end */
	if (!q->l_tail)
	{
		/* should assert that q->l is also NULL */
		q->l = new_node;
		q->l_tail = new_node;
	}
	else
	{
		q->l_tail->next = new_node;
		q->l_tail = new_node;
	}
}

void * dequeue(queue * q)
{
	if (!q || !(q->l))
	{
		return NULL;
	}
	list * first_node = q->l;
	if (q->l == q->l_tail)
	{
		q->l = NULL;
		q->l_tail = NULL;
	}
	else
	{
		q->l = first_node->next;
	}
	
	void * res = first_node->d;
	free(first_node);
	return res;
}