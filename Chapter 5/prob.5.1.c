/*
 *
 * Insertion: You are given two 32-bit numbers, N and M, and two bit positions, i and
 * j. Write a method to insert M into N such that M starts at bit j and ends at bit i. You
 * can assume that the bits j through i have enough space to fit all of M. That is, if
 * M = 10011, you can assume that there are at least 5 bits between j and i. You would not, for
 * example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.
 * EXAMPLE
 * Input: N=10000000000, M=10011, i=2, j=6
 * Output: N = 10001001100
 *
 */

#include <stdio.h>
#include <stdbool.h>

unsigned int insert_m_into_n(unsigned int m, unsigned int n, unsigned int i , unsigned int j);

void print_binary(unsigned int a);

int main()
{
	unsigned int m, n;
	m = 0 + 2 + 16;
	n = 0xFFF;
	printf("n is \t"); print_binary(n); printf("\n");
	printf("m is \t"); print_binary(m); printf("\n");
	n = insert_m_into_n(m, n, 2, 6);
	printf("n is \t"); print_binary(n); printf("\n");
	return 0;
}

unsigned int insert_m_into_n(unsigned int m, unsigned int n, unsigned int i, unsigned int j)
{
	unsigned int res = 0;
	unsigned int int_sz = sizeof(unsigned int) * 8;		/*assume char has 8 bits */
	unsigned int mask = 0xFFFFFFFF >> (int_sz-i);
	mask = mask | (0xFFFFFFFF << (j+1));
	res = n & mask;

	res = res | (m << i);

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
