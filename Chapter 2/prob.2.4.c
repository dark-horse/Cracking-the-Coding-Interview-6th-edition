/*
 *
 * Partition: Write code to partition a linked list around a value x, such that all nodes less than x come
 * before all nodes greater than or equal to x. If x is contained within the list, the values of x only need
 * to be after the elements less than x (see below). The partition element x can appear anywhere in the
 * "right partition"; it does not need to appear between the left and right partitions.
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

node * partition_list(node * head, int partition_value);
node * build_list(int list_sz, bool random, bool duplicates);
void free_list(node * head);
void print_list(node * head);

int main()
{
	int partition_value = 250;
	node * head = build_list(10 /*list_sz*/, true /*random*/, true /*duplicates*/);
	printf("the built list\n");
	print_list(head);
	head = partition_list(head, partition_value);
	printf("partitioned list around value %d.\n", partition_value);
	print_list(head);
	free_list(head);
	return 0;
}

/* the algorithm will traverse the 'head' list while building */
/* two lists: one for nodes smaller than the partition value */
/* the other list for nodes greater than the partition value */
/* this function will not allocate more memory - it will re-arrange the nodes */
/* in the input list so the result is a partitioned list */
node * partition_list(node * head, int partition_value)
{
	node * smaller_list_head = NULL;
	node * smaller_list_end = NULL;		/* need a pointer to the end of the list to append the greater_list when we went through all the nodes */
	node * greater_list_head = NULL;
	
	while (head != NULL)
	{
		node * next = head->next;
		if (head->data >= partition_value)
		{
			/* append this node to the greater list */
			head->next = greater_list_head;
			greater_list_head = head;
		}
		else
		{
			/* append this node to the smaller list */
			head->next = smaller_list_head;
			smaller_list_head = head;
			if (smaller_list_end == NULL)
			{
				smaller_list_end = head;
			}
		}
		
		head = next;
	}
	
	/* combine the lists if necessary and return */
	if (smaller_list_head)
	{
		smaller_list_end->next = greater_list_head;
		return smaller_list_head;
	}
	else
	{
		return greater_list_head;
	}
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
			val = rand() / 100;
		}
		else
		{
			val = i + 1;
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
