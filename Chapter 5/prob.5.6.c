/*
 *
 * Conversion: Write a function to determine the number of bits you would need to flip to convert
 * integer A to integer B.
 * EXAMPLE
 * Input: 29 (or: 11101), 15 (or: 01111)
 * Output: 2
 */

#include <stdio.h>

void print_binary(unsigned int a);

unsigned int flips_required(unsigned int a, unsigned b);

int main()
{
	unsigned int flips = flips_required(29, 15);
	printf("flips required from 29 to 15 is %d. \n", flips);
	return 0;
}

unsigned int flips_required(unsigned int a, unsigned int b)
{
	int res = 0;
	a = a ^ b;
	while(a)
	{
		res += (a & 1);
		a = a >> 1;
	}
	return res;
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