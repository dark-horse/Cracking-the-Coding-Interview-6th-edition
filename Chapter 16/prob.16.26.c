/*
 *
 * Calculator: Given an arithmetic equation consisting of positive integers, +, -, * and / (no parentheses),
 * compute the result.
 * EXAMPLE
 * Input: 2*3+5/6*3+15
 * Output: 23.5
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* we will use a stack with operators and operands */
union data
{
	char operation;
	float operator;
};

typedef struct stacks
{
	union data * arr;
	unsigned int arr_alloc;
	unsigned int front;
	unsigned int stack_sz;
} stack;

/*****************************************/
/*            STACK FUNCTIONS            */
/*****************************************/
void push(stack *s, union data d);
union data pop(stack *s);
union data stack_front(stack * s);
bool isEmpty(stack *s);
void free_stack(stack *s);
stack * create_stack();

/*****************************************/
/*              THE SOLUTION             */
/*****************************************/
void process_eq(char * eq, unsigned int eq_sz, stack * s);

int main()
{
	char * eq = (char *) malloc(2048 * sizeof(char));
	stack * s = create_stack();
	
	size_t n;
	while (true)
	{
	
		getline(&eq, &n, stdin);
		if(eq[0] == 'q' || eq[0] == 'Q')
		{
			break;
		}
		int eq_sz = strlen(eq);
		eq_sz --;
		eq[eq_sz] = '\0';	/* remove the new line character */
		
		process_eq(eq,eq_sz,s);
	}
		
	free(eq);
	free_stack(s);
	return 0;
}

/*****************************************/
/*              THE SOLUTION             */
/*****************************************/
void process_eq(char * eq, unsigned int eq_sz, stack * s)
{
	/* the algorithm is to read operations and operators from the command line */
	/* push the operators into the stack */
	/* if the operation is + or - (lowest precedence) push them into the stack */
	/* if the operation is * or / (higher precedence) pop the stack (it should have an integer) */
	/*         read the next operator, perform the operation and push the result into the stack */
	/* when we are done reading the eq, the stack should have + / - and operators */
	/* traverse the stack from the front (in FIFO not LIFO order) */
	char * curr = eq;
	/* read the first operator */
	float operator = 0;
	union data d;
	while (*curr >= '0' && *curr <= '9')
	{
		operator = operator * 10;
		operator += (int) (*curr - '0');
		curr ++;
	}
	d.operator = operator;
	push(s, d);
	while (curr < eq + eq_sz)
	{
		if (*curr == '+' || *curr == '-')
		{
			d.operation = *curr;
			push(s,d);
			curr++;
			operator = 0;
			while (*curr >= '0' && *curr <= '9')
			{
				operator = operator * 10;
				operator += (int) (*curr - '0');
				curr ++;
			}
			d.operator = operator;
			push(s, d);
		}
		else if (*curr == '*' || *curr == '/')
		{
			char operation = *curr;
			d = pop(s);
			operator = d.operator;
			curr ++;
			float operator2 = 0;
			while (*curr >='0' && *curr <= '9')
			{
				operator2 = operator2 * 10;
				operator2 += (int) (*curr - '0');
				curr++;
			}
			if (operation == '*')
			{
				operator = operator * operator2;
			}
			else
			{
				operator = operator / operator2;
			}
			d.operator = operator;
			push(s, d);
		}
		else
		{
			printf("error: unknown operation: %c.\n", *curr);
			return;
		}
	}
	/*traverse the stack from the front (in FIFO order not LIFO order) */
	d = stack_front(s);
	float res = d.operator;
	while (!isEmpty(s))
	{
		d = stack_front(s);
		char operation = d.operation;
		float operator2;
		d = stack_front(s);
		operator2 = d.operator;
		if (operation == '+')
		{
			res += operator2;
		}
		else
		{
			/*assert the operation is - */
			res = res - operator2;
		}
	}
	
	printf("result for equation %s is %f.\n", eq, res);
}


/*****************************************/
/*            STACK FUNCTIONS            */
/*****************************************/
void push(stack *s , union data d)
{
	if (s->arr_alloc <= s->stack_sz)
	{
		s->arr_alloc = s->arr_alloc * 2;
		s->arr = realloc(s->arr, s->arr_alloc * sizeof(union data));
	}
	s->arr[s->stack_sz] = d;
	s->stack_sz ++;
}

union data pop(stack * s)
{
	s->stack_sz --;
	return s->arr[s->stack_sz];
}


union data stack_front(stack * s)
{
	s->front ++;
	return s->arr[s->front-1];
}

bool isEmpty(stack *s)
{
	return !(s->stack_sz-s->front);
}

stack * create_stack()
{
	stack * res = malloc(sizeof(stack));
	res->arr_alloc = 64;
	res->arr = (union data *) malloc(res->arr_alloc * sizeof(union data));
	if (!res->arr)
	{
		free (res);
		return NULL;
	}
	res->stack_sz = 0;
	res->front = 0;
	
	return res;
}

void free_stack(stack *s)
{
	free(s->arr);
	memset(s, 0, sizeof(stack));
}