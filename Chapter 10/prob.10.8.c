/*
 *
 * Find Duplicates: You have an array with all the numbers from 1 to N, where N is at most 32,000. The
 * array may have duplicate entries and you do not know what N is. With only 4 kilobytes of memory
 * available, how would you print all duplicate elements in the array?
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_duplicates(unsigned short * input, int input_sz);

int main()
{
	return 0;
}

/* the problem is a bit confusing */
/* I assume the 4 kilobytes do not include the input array (otherwise we are in trouble - there is no bound on the input array size) */
/* 4 kilobytes of memory can hold 32,000 bits */
/* NOTE: this algorithm does not use the fact that all numbers between 1 and N are in the array */
void print_duplicates(unsigned short  * input, int input_sz)
{
	char * mem = (char *) malloc(4*1024 * sizeof(char));
	memset(mem, 0, 4*1024*sizeof(char));

	for (int i = 0; i < input_sz; i ++)
	{
		/*mem has 32,000 bits*/
		/*Input has at most 32,000 integers */
		/*Coincidence? I think not */
	
		unsigned short a = input[i];
		/*find the corresponding bit in the mem */
		unsigned int offset = a / 8;
		unsigned short mask = 1 << ((a % 8) + 1);
		if (mem[offset] & mask)
		{
			/* duplicate */
			printf("%d\n", input[i]);
		}
		
		/* flip the bit for this integer */
		mem[offset] = mem[offset] | mask;
	}
	free (mem);
}