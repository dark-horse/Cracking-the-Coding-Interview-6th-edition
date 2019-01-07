/*
 *
 * Diving Board: You are building a diving board by placing a bunch of planks of wood end-to-end.
 * There are two types of planks, one of length shorter and one of length longer. You must use
 * exactly K planks of wood. Write a method to generate all possible lengths for the diving board.
 *
 */

#include <stdio.h>

void print_possible_planks(unsigned int K, unsigned int shorter, unsigned int longer);

int main()
{
	print_possible_planks(10, 2, 4);
	return 0;
}

void print_possible_planks(unsigned int K, unsigned int shorter, unsigned int longer)
{
	for (int i = 0; i < K; i ++)
	{
		unsigned int board_len = i * shorter + (K-i) * longer;
		printf("diving board lenght is %d made from %d shorter planks and %d longer planks.\n", board_len, i, K-i);
	}
}
