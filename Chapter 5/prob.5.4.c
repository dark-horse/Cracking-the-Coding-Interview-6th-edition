/*
 *
 * Next Number: Given a positive integer, print the next smallest and the next largest number that
 * have the same number of 1 bits in their binary representation.
 */

#include <stdio.h>
#include <stdbool.h>

void print_binary(unsigned int a);

void next_number(unsigned int a);

int main()
{
	next_number(3);printf("\n************************\n");
	next_number(4);printf("\n************************\n");
	next_number(5);printf("\n************************\n");
	next_number(6);printf("\n************************\n");
	next_number((unsigned int) 0x80000000);printf("\n************************\n");
	return 0;
}

void next_number(unsigned int a)
{
	unsigned int exception = 0xFFFFFFFF;
	if (a == exception)
	{
		printf("error: ");
		print_binary(a);
		printf(" has no room for changing 1's around\n");
		return;
	}
	/* the next largest number with the same number of 1 bits is found */
	/* by finding the first "01" and converting it to "10" */
	/* the next smalest number with the same number of 1 bits is found */
	/* by finding the first "10" and converting it to "01" */
	bool found_next_largest = false, found_next_smallest = false;
	unsigned int next_largest = a, next_smallest = a;
	unsigned int lower_mask = 1, higher_mask = 2;
	int binary_sz = sizeof(unsigned int )* 8;
	for (int i = 0; i < binary_sz-1; i ++)
	{
		if (!found_next_largest && ( (next_largest & lower_mask) == lower_mask) && ( (next_largest & higher_mask) != higher_mask))
		{
			next_largest = a & (~lower_mask);
			next_largest = next_largest | higher_mask;
			found_next_largest = true;
		}
		if (!found_next_smallest && ( (next_smallest & higher_mask) == higher_mask) && ( (next_smallest & lower_mask) != lower_mask))
		{
			next_smallest = a & (~higher_mask);
			next_smallest = next_smallest | lower_mask;
			found_next_smallest = true;
		}
		if (found_next_largest && found_next_smallest)
		{
			break;
		}
		higher_mask = higher_mask << 1;
		lower_mask = lower_mask << 1;
	}
	printf("input %d in binary is: \t\t", a);
	print_binary(a); printf("\n");
	if (found_next_largest)
	{
		printf("next largest number is %d: \t", next_largest);
		print_binary(next_largest); printf("\n");
	}
	else
	{
		printf("no next largest found for input.\n");
	}
	if (found_next_smallest)
	{
		printf("next smallest number is %d: \t", next_smallest);
		print_binary(next_smallest); printf("\n");
	}
	else
	{
		printf("no next smallest found for input.\n");
	}
}

void print_binary(unsigned int a)
{
	int binary_sz = sizeof(unsigned int) * 8;		/* assume char has 8 bits */
	unsigned int mask = 0x80000000;					/* here we make an implicit assumption that unsigned int takes 32 bits. So what's the point of measuring binary_sz above? */
	for (int i = 0; i < binary_sz; i ++)
	{
		printf("%d", ( (a & mask) >> (binary_sz - 1) ));
		a = a << 1;
	}
}