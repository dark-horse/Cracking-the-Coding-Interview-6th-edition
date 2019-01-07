/*
 * Magic Index: A magic index in an array A [ 0 ••• n -1] is defined to be an index such that A[ i] =
 * i. Given a sorted array of distinct integers, write a method to find a magic index, if one exists, in
 * array A.
 * FOLLOW UP
 * What if the values are not distinct?
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int magic_index_no_duplicates(int * arr, int beg, int end);
int magic_index_duplicates(int * arr, int beg, int end);

int main()
{
	int arr[] = {1,3,5};
	int magic_index = magic_index_no_duplicates(arr, 0, 2);
	printf("magic index with the no_duplicates method is %d.\n", magic_index);
	magic_index = magic_index_duplicates(arr, 0, 2);
	printf("magic index with the duplicates method is %d.\n", magic_index);
	return 0;
}

/* if arr is an array of increasing integers with no duplicates then */
/* arr[0] - 0; arr[1]-1; arr[2]-2;.... will be an array of increasing integers (with possible duplicates) */
/* use binary search to look for 0 in the arr[0] - 0; arr[1]-1; arr[2]-2;.... */
int magic_index_no_duplicates(int * arr, int beg, int end)
{
	/* base case */
	if (beg >= end)
	{
		return (arr[beg]-beg) ? -1 : beg;
	}
	
	int mid = (beg + end) / 2;
	
	if (arr[mid] - mid == 0)
	{
		return mid;
	}
	else if (arr[mid] - mid > 0)
	{
		return magic_index_no_duplicates(arr, beg, mid - 1);
	}
	else
	{
		return magic_index_no_duplicates(arr, mid + 1, end);
	}
}

/* if the array is sorted increasingly but may have duplicates, then */
/* arr[0] - 0; arr[1]-1; arr[2]-2;.... will not be an array of increasing integers */
/* however, looking at the middle of the array and comparing arr[mid] - mid may still help.... */
/* if arr[mid] - mid is too low, we know it cannot be in the first half of arr */
/* and if arr[mid] - mid is too high, we know it cannot be in the second half of arr */
int magic_index_duplicates(int * arr, int beg, int end)
{
	/* base case */
	if (beg >= end)
	{
		return (arr[beg]-beg) ? -1 : beg;
	}

	int mid = (beg + end) / 2;

	if (arr[mid] - mid == 0)
	{
		return mid;
	}

	if (arr[mid] - mid < beg - mid)
	{
		/* beg to mid cannot have a magic index */
		return magic_index_duplicates(arr, mid + 1, end);
	}

	/* We can't rule out that the first half of the array does not have a magic number. So recurse into it.*/
	int res = magic_index_duplicates(arr, beg, mid-1);
	if (res != -1)
	{
		/*found a magic number */
		return res;
	}

	if (arr[mid] - mid > end - mid)
	{
		/* mid to end cannot have a magic index */
		return -1;
	}

	/* We can't rule out that the second half of the array does not have a magic number. So recurse into it.*/
	return magic_index_duplicates(arr, mid + 1, end);
}