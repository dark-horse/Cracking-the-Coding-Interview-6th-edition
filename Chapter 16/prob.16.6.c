/*
 *
 * Smallest Difference: Given two arrays of integers, compute the pair of values (one value in each
 * array) with the smallest (non-negative) difference. Return the difference.
 * EXAMPLE
 * Input: {1, 3, 15, 11, 2}, {23, 127,235, 19, 8}
 * Output: 3. That is, the pair (11, 8).
 *
 */

#include <stdio.h>
#include <limits.h>

void smallest_difference(int* arr1, int arr1_sz, int * arr2, int arr2_sz);

int main()
{
	return 0;
}

/* the problem is a bit confusing */
/* It is not clear if the smallest (non-negative) difference is the "distance" between elements of the array */
/*    This would be a "natural" question to ask about two vectors - what is the smallest distance between them. */
/* I will assume that the author is not looking for the smallest "distance". */
/* I will assume the author is looking for min{a-b | a>=b, a in first array, b in second array */
/* It may be the case there is no solution (if all the elements in arr1 are smaller than any of the elements in arr2) */
void smallest_difference(int * arr1, int arr1_sz, int * arr2, int arr2_sz)
{
	/*find the smalle element in arr2*/
	int min_arr2 = INT_MAX;
	for (int i = 0; i < arr2_sz; i ++)
	{
		if (min_arr2 > arr2[i])
		{
			min_arr2 = arr2[i];
		}
	}
	int arr1_candidate_index = -1;
	int min_diff;
	for (int i = 0; i < arr1_sz; i ++)
	{
		int diff = arr1[i] - min_arr2;
		if (diff >= 0)
		{
			min_diff = diff;
			arr1_candidate_index = i;
		}
	}
	
	if (min_diff == -1)
	{
		printf("no solution to the problem: all elements in the first array are smaller than any element in the second array (and thus all differences are negative)\n");
	}
	else
	{
		printf("%d. That is, the pair (%d, %d).\n", min_diff, arr1[arr1_candidate_index], min_arr2);
	}
}
