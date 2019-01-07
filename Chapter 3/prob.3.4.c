/*
 *
 * Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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


typedef struct queues
{
	stack * data; 	/*will hold the data*/
	stack * helper; /* to be used for add / remove / peek operations */
	bool data_stack_in_queue_order;
} queue;

/*queue API*/
queue * create_queue();
bool is_empty_queue(queue * q);
void add(queue * q, int data);
int queue_remove(queue *q);
int peek_queue(queue *q);
void free_queue(queue * q);

/* stack API */
stack * create_stack();
void push(stack * s, int item);
int pop(stack * s);
int peek_stack(stack * s);
bool is_empty_stack(stack * s);
void free_stack(stack * s);
void print_stack(stack * s);
void add_test_items(queue *q, int items_count);

int main()
{
	queue * q = create_queue();
	add_test_items(q, 20);
	printf("remove the first 10 items in the queue.\n");
	for (int i = 0; i < 10; i++)
	{
		int d = queue_remove(q);
		printf("%d ",d);
	}
	printf("\n");
	printf("add 10 more items.\n");
	add_test_items(q,10);
	printf("remove all the items in the queue while printing them\n");
	while (!is_empty_queue(q))
	{
		int d = queue_remove(q);
		printf("%d ", d);
	}
	printf("\n");

	printf("add 3 items\n");
	add_test_items(q,3);
	printf("the first item added is : %d.\n", peek_queue(q));

	printf("remove again all the items in the queue while printing them\n");
	while (!is_empty_queue(q))
	{
		int d = queue_remove(q);
		printf("%d ", d);
	}
	
	free_queue(q);

	return 0;
}

/*******************************************/
/*                                         */
/*           QUEUE FUNCTIONS               */
/*                                         */
/*******************************************/
queue * create_queue()
{
	queue * q = (queue *) malloc(sizeof(queue));
	q->data = create_stack();
	q->helper = create_stack();
	q->data_stack_in_queue_order = false;
	return q;
}

bool is_empty_queue(queue *q)
{
	return is_empty_stack(q->data);
}

/* Invariants: */
/* 1. Data in the helper stack will always be in stack order (opposite from queue order) */
/* 2. If the data in data stack is in queue order we always add data to the helper stack */
/* 3. If the data in the data stack is in queue order, the beggining of the queue is on the data stack */
/* 4. If the data in the data stack is in queue order, the data stack is not empty */
/* 5. if the data in the data stack is in stack order, the helper stack is empty */
void add(queue * q, int data)
{
	if (q->data_stack_in_queue_order)
	{
		push(q->helper, data);
	}
	else
	{
		/* we should assert q->helper is empty */
		push(q->data, data);
	}
}

int queue_remove(queue * q)
{
	if (is_empty_queue(q))
	{
		return 0; /* how do we return error with this interface ? */
	}
	
	if (q->data_stack_in_queue_order)
	{
		/* should assert the data stack is not empty */
		
		/* CHECK THE INVARIANTS: */
		/* 1. data in the helper stack is in stack order (as it was when we entered the procedure */
		int res = pop(q->data);
		if (is_empty_stack(q->data))
		{
			/* the data stack became empty */
			/* swap it with the helper stack and flip the data_stack_in_queue_order to false */
			stack * tmp = q->helper;
			q->helper = q->data;
			q->data = tmp;
			q->data_stack_in_queue_order = false;
			/* CHECK THE INVARIANTS: */
			/* 5. if data in data stack is in stack order, the helper stack is empty */
		}
		/* 2. If the data in data stack is in queue order we always add data to the helper stack (not applicable) */
		/* 3. If the data in the data stack is in queue order, the beggining of the queue is on the data stack */
		/* 4. If the data in the data stack is in queue order, the data stack is not empty */
		return res;
	}
	
	/* we should assert helper stack is empty.... */

	/* move the items from the data stack into the helper stack (which should be empty). */
	/* moving from stack order into another stack makes the second stack in queue order. */
	while (!is_empty_stack(q->data))
	{
		int d = pop(q->data);
		push(q->helper, d);
	}

	int res = pop(q->helper);

	if (!is_empty_stack(q->helper))
	{
		stack * tmp = q->helper;
		q->helper = q->data;
		q->data = tmp;
		q->data_stack_in_queue_order = true;
	}

	/* CHECK THE INVARIANTS: */
	/* 1. data in the helper stack is in stack order (helper stack is empty)*/
	/* 2. If the data in data stack is in queue order we always add data to the helper stack (not applicable) */
	/* 3. If the data in the data stack is in queue order, the beggining of the queue is on the data stack */
	/* 4. If the data in the data stack is in queue order, the data stack is not empty */
	/* 5. if data in data stack is in stack order, the helper stack is empty */
	return res;
}

int peek_queue (queue * q)
{
	if (is_empty_queue(q))
	{
		return 0; /*how do we return error with this interface? */
	}

	if (q->data_stack_in_queue_order)
	{
		return peek_stack(q->data);
	}
	/*should assert helper stack is empty */
	/* move the data from the data stack into the helper stack */
	int res;
	while (!is_empty_stack(q->data))
	{
		res = pop(q->data);
		push(q->helper, res);
	}
	stack * tmp = q->helper;
	q->helper = q->data;
	q->data = tmp;
	q->data_stack_in_queue_order = true;

	return res;
}

void free_queue(queue * q)
{
	if(!q)
	{
		return;
	}

	free_stack(q->data);

	free_stack(q->helper);
	
	free(q);
}

void add_test_items(queue * q, int items_count)
{
	for (int i = 0; i < items_count; i ++)
	{
		add(q, i+1);
	}
}


/*******************************************/
/*                                         */
/*           STACK FUNCTIONS               */
/*                                         */
/*******************************************/
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

int peek_stack(stack *s)
{
	if (!s || !s->head)
	{
		return 0;	/* how do we return errors with this interface ????*/
	}
	
	return s->head->data;
}

bool is_empty_stack(stack * s)
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

