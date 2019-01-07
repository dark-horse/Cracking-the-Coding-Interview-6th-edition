/*
 *
 * Sorted Merge: You are given two sorted arrays, A and B, where A has a large enough buffer at the
 * end to hold B. Write a method to merge B into A in sorted order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sorted_merge(int * a, int a_len, int * b, int b_len);

void print_int_arr(int * a, int a_len);

int main()
{
	int * a = (int *) malloc( (10+5) * sizeof(int));
	a[0] = -10; a[1] = 20;
	int b[13] = {-1, 1, 2, 3, 4, 5, 6, 7, 9, 20, 21, 22, 23};
	sorted_merge(a, 2, b, 13);
	print_int_arr(a,15);
	return 0;
}

/* "a" points to an array big enough to hold a_len + b_len */
/* the trick is to start from the end of the input */
/* assume both "a" and "b" are sorted in increasing order */
/* if "a" and "b" are sorted in decreasing order just flip the sign on the if statement */
void sorted_merge(int * a, int a_len, int * b, int b_len)
{
	int a_index = a_len, b_index = b_len;
	
	while (a_index + b_index && a_index && b_index)
	{
		if (a[a_index-1] >= b[b_index-1])
		{
			a[a_index+b_index-1] = a[a_index-1];
			a_index --;
		}
		else
		{
			a[a_index+b_index-1] = b[b_index-1];
			b_index--;
		}
	}
	
	if (b_index)
	{
		memcpy(a /*dest*/, b/*src*/, b_index * sizeof(int));
	}
}

void print_int_arr(int * a, int a_len)
{
	if (!a_len || !a)
	{
		return;
	}
	
	printf("%d ", a[0]);
	
	for (int i = 1; i < a_len; i ++)
	{
		printf("; %d", a[i]);
	}
	
	printf("\n");
}
