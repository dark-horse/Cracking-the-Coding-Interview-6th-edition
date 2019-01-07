/*
 *
 * Implement a function to check if a linked list is a palindrome
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct nodes
{
	char data;
	struct nodes * next;
} node;

node * build_list(int list_sz, bool random, bool duplicates);
node * build_palindrome_list(int list_sz, bool random);
bool check_palindrome_in_place(node * head);
bool check_palindrome_list(node * head);
void free_list(node * head);
void print_list(node * head);

int main()
{
	node * head = build_palindrome_list(15 /*list_sz*/, false /*random*/);
	printf("the palindrome list\n");
	print_list(head);
	printf("list is %spalindrome. (check with additional memory )\n", check_palindrome_list(head) ? "" : "NOT ");
	printf("list is %spalindrome. (no additional memory )\n", check_palindrome_in_place(head) ? "" : "NOT ");
	free_list(head);
	head = build_list(20, true /*random*/, false /*duplicates*/);
	printf("random list.\n");
	print_list(head);
	printf("list is %spalindrome. (check wth additional memory )\n", check_palindrome_list(head) ? "" : "NOT ");
	printf("list is %spalindrome. (no additional memory )\n", check_palindrome_in_place(head) ? "" : "NOT ");
	free_list(head);
	
	return 0;
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

/* this function will create (and then destroy) an intermediate list */
/* which is the input list in reverse order */
/* the running time of this algorithm is O(N) where N is the size of the input */
/* however, this function requires additional memory */
bool check_palindrome_list(node * head)
{
	if (head == NULL || head->next == NULL)
	{
		/* empty lists or list of size 1 are palindromes by default */
		return true;
	}
	
	node * reverse_list = NULL;
	node * traverse_input = head;
	while (traverse_input)
	{
		node * add = (node *) malloc(sizeof(node));
		add->data = traverse_input->data;
		add->next = reverse_list;
		reverse_list = add;
		traverse_input = traverse_input->next;
	}
	
	bool res = true;
	while (head)
	{
		if (head->data != reverse_list->data)
		{
			res = false;
			break;
		}
		head = head->next;
		reverse_list = reverse_list->next;
	}

	/* destroy the intermediary list */
	free_list(reverse_list);
	return res;
}

/* This function will check if a list is a palindrome without allocating any memory. */
/* In the first step the function will navigate a pointer to the end of the list */
/*   while changing the pointers from middle of the list to the end to point back */
/*   to the begining of the list. */
/* In the second step, the tail pointer will navigate backward towards the beginning */
/*   while the head pointer will navigate forward towards the end of the list. */
/* At the same time we fix the pointers we changed at step 1 and compare the tail with the head. */
bool check_palindrome_in_place(node * head)
{
	/* some base cases */
	if (head == NULL || head->next == NULL)
	{
		return true;
	}
	
	node * traverse = head, * mid = head;
	while (traverse)
	{
		traverse = traverse->next;
		if (traverse)
		{
			traverse = traverse->next;
		}
		if (!traverse)
		{
			break;
		}
		mid = mid->next;
	}
	traverse = mid->next;
	node * prev_node = mid, *curr_node; /* previous node in the original beginning->end order */
	/* navigate to the end of the list and flip the pointers to point towards the beginning of the list */
	while (traverse)
	{
		curr_node = traverse;
		traverse = traverse->next;
		curr_node->next = prev_node;
		prev_node = curr_node;
	}

	node * tail = prev_node, *next_node = NULL;
	bool res = true;

	while (true)
	{
		/* palindrome check */
		res = res & (tail->data == head->data);
		/* advance the tail pointer backwards while fixing the pointers to point towards the end of the list */
		prev_node = tail->next;
		tail->next = next_node;
		next_node = tail;
		tail = prev_node;

		if (head == mid)
		{
			break;
		}

		/* advance the beggining pointer forward */
		head = head->next;
	}

	return res;
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
	head->data = 'a';
	head->next = NULL;
	node * end = head;
	
	for (int i = 1; i < list_sz; i ++)
	{
		node * next = (node *) malloc(sizeof(node));
		char val;
		if (random)
		{
			int r = rand() % 27;
			val = (char)((int)'a' + r);
		}
		else
		{
			val = (char)((int)'a' + (i + 1) % 27);
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

node * build_palindrome_list(int list_sz, bool random)
{
	if (list_sz == 0)
	{
		return NULL;
	}
	if (list_sz == 1)
	{
		node * res = (node *) malloc(sizeof(node));
		res->next = NULL;
		res->data = 'a';
		return res;
	}

	int half_size = list_sz / 2;
	int remainder = list_sz % 2;
	
	node * head = build_list(half_size, random, false /*duplicates*/);
	node * tail = head;
	while (tail->next)
	{
		tail = tail->next;
	}
	
	node * new_list = NULL;
	node * traverse = head;
	while (traverse)
	{
		/* add the corresponding node at the end of the list */
		node * add = (node *) malloc(sizeof(node));
		add->data = traverse->data;
		add->next = new_list;
		new_list = add;
		traverse = traverse->next;
	}

	if (remainder)
	{
		node * add = (node *) malloc(sizeof(node));
		add->data = 'a';
		add->next = NULL;
		tail->next = add;
		tail = add;
	}

	tail->next = new_list;
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
	
	printf("%c", head->data);
	head = head->next;
	while (head)
	{
		printf("\t-> %c", head->data);
		head = head->next;
	}
	printf("\n********************************\n");
}