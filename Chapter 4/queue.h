/*
 * Definition file for a simple queue object.
 * Used for breath first traversal.
 */

#include <stdbool.h>

typedef struct lists
{
	void * d;
	struct lists * next;
} list;

typedef struct queues
{
	list * l;
	list * l_tail;
} queue;

queue * create_empty_queue();
void free_queue(queue * q);
bool isEmpty(queue * q);
void enqueue(queue * q, void * t);
void * dequeue(queue * q);