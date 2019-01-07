/*
 *
 * 	Pairwise Swap: Write a program to swap odd and even bits in an integer with as few instructions as
 * possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, and so on).
 *
 *
 */

#include <stdio.h>

unsigned int pairwise_bit_swap(unsigned int a);

void print_binary(unsigned int a);
void test();

int main()
{
	test(1);
	test(1024);
	test(5);
	test(7);
	return 0;
}

unsigned int pairwise_bit_swap(unsigned int a)
{
	unsigned int a1 = a << 1;
	unsigned int a2 = a >> 1;
	unsigned int mask1 = 0xAAAAAAAA;
	unsigned int mask2 = 0x55555555;
	return (a1 & mask1) | (a2 & mask2);
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

void test(unsigned int a)
{
	printf("\n*********************\n");
	printf("input is \t");
	print_binary(a);
	printf("\n");
	printf("output is \t");
	print_binary(pairwise_bit_swap(a));
	printf("\n*********************\n");
}
