/*
 *
 * Contiguous Sequence: You are given an array of integers (both positive and negative). Find the
 * contiguous sequence with the largest sum. Return the sum.
 * EXAMPLE
 * Input:2, -8, 3, -2, 4, -10
 * Output: 5 ( i. e.  { 3, -2, 4})
 *
 */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int contiguous_sequence(int * arr, int arr_sz, int * beg, int * end);
int check_all_negative(int * arr, int arr_sz);

int main()
{
	int arr[6] = {-2, -8, 5, -4,4,10};
	int beg, end, sum;
	sum = contiguous_sequence(arr, 6, &beg, &end);
	printf("%d {", sum);
	for (int i = beg; i <=end; i ++)
	{
		printf(" %d,", arr[i]);
	}
	printf(" }\n");
	return 0;
}

/* some invariants : */
/* 1. the first and last element in the contiguous array are positive */
/* 2. the sum of numbers between the first and any element in the contiguous array is positive */
/* 3. the sum of numbers between any element in the contiguous array and the last element is positive */
int contiguous_sequence(int * arr, int arr_sz, int * beg, int * end)
{
	if (arr_sz <= 0)
	{
		*beg = 0;
		*end = 0;
		return 0;
	}

	int all_neg = check_all_negative(arr, arr_sz);
	if (all_neg >=0)
	{
		*beg = all_neg;
		*end = all_neg;
		return arr[all_neg];
	}

	bool found_positive_seq = false;			/* true when we found a positive sequence in the past */
	int beg_pos_seq = -1, end_pos_seq = -1, sum_pos_seq = -1;

	bool searching_for_seq_beg = true;			/* true when we are searching for the beggining of the sequence */
	int beg_candidate = -1, end_candidate = -1, sum_candidate = -1, tmp_sum = -1;

	int i = 0;
	while (i < arr_sz)
	{
		if (arr[i]>0)
		{
			if (searching_for_seq_beg)
			{
				beg_candidate = i;
				end_candidate = i;
				sum_candidate = arr[i];
				tmp_sum = arr[i];
				searching_for_seq_beg = false;
			}
			else
			{
				tmp_sum += arr[i];
				if (tmp_sum >= sum_candidate)
				{
					end_candidate = i;
					sum_candidate = tmp_sum;
				}
			}
			i++;
		}
		else
		{
			if (searching_for_seq_beg)
			{
				i++;
				continue;
			}
			/* we have seen some positive numbers in the past and now we have negative numbers */
			/* if the sum is still positive (invariant 2) we can still keep going */
			tmp_sum += arr[i];
			if (tmp_sum > 0)
			{
				i++;
				continue;
			}
			/* so we had some positive numbers and now the sum turns negative */
			/* check to see to see if the latest sum is higher than the previous sequence (if any) */
			if (!found_positive_seq || sum_candidate > sum_pos_seq)
			{
				beg_pos_seq = beg_candidate;
				end_pos_seq = end_candidate;
				sum_pos_seq = sum_candidate;
			}
			/* in any case, now we have seen a positive sequence and are starting to look for the next one */
			found_positive_seq = true;
			searching_for_seq_beg = true;
			beg_candidate = -1;
			end_candidate = -1;
			sum_candidate = -1;
			tmp_sum = -1;
			i++;
			continue;
		}
	}
	if (sum_pos_seq > sum_candidate)
	{		
		*beg = beg_pos_seq;
		*end = end_pos_seq;
		return sum_pos_seq;
	}
	else
	{
		*beg = beg_candidate;
		*end = end_candidate;
		return sum_candidate;
	}
}


/* the index of the largest negative number in arr when  arr is all negative numbers */
/* -1 if arr has one or more positive numbers */
int check_all_negative(int * arr, int arr_sz)
{
	if(arr[0] > 0)
	{
		return -1;
	}

	int largest = 0;
	for (int i = 1; i < arr_sz; i ++)
	{
		if (arr[i] > 0)
		{
			return -1;
		}
		if (arr[largest] < arr[i])
		{
			largest = i;
		}
	}
	return largest;
}