/*
 *
 * Search in Rotated Array: Given a sorted array of n integers that has been rotated an unknown
 * number of times, write code to find an element in the array. You may assume that the array was
 * originally sorted in increasing order.
 * EXAMPLE
 * Input:findSin{lS, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}
 * Output: 8 (the index of 5 in the array)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool search(int * a, int a_sz, int target, int * res);
bool binary_search_pivot(int * a, int a_sz, int pivot, int target, int * res, int left, int right);
int rotated_pivot(int * a, int left, int right);

void test_search(int max_test_sz);

int main()
{
	/* test all possible rotations for all possible arrays from size 2 to 10000 */
	test_search(10000);
	return 0;
}

/* we first find the pivot of the rotation - which takes log(n) */
/* then we adapt the usual binary search with the pivot - takes log(n) too */
/* total time takes log(n) */
bool search(int * a, int a_sz, int target, int * res)
{
	int pivot = rotated_pivot(a, 0, a_sz-1);
	bool found = binary_search_pivot(a, a_sz, pivot, target, res, 0, a_sz-1);
	*res = (*res+pivot) % a_sz;
	return found;
}

/* adapt the binary search in an increasing array to an increasing array which was rotated */
bool binary_search_pivot(int * a, int a_sz, int pivot, int target, int * res, int left, int right)
{
	/* some base cases */
	if (left == right || left == right-1)
	{
		if (a[(left+pivot)%a_sz] == target)
		{
			*res = left;
			return true;
		}
		else if (a[(right+pivot)%a_sz] == target)
		{
			*res = right;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	int mid = (left + right) / 2;
	if (a[(mid+pivot)%a_sz] == target)
	{
		*res = mid;
		return true;
	}
	
	if (a[(mid+pivot) % a_sz] > target)
	{
		return binary_search_pivot(a, a_sz, pivot, target, res, left, mid-1);
	}
	else
	{
		return binary_search_pivot(a, a_sz, pivot, target, res, mid + 1, right);
	}
}

/* "a" is a rotated array which originally was in increasing order */
int rotated_pivot(int * a, int left, int right)
{
	int mid = (left + right) / 2;

	/*base case*/
	if (mid == left)
	{
		if (a[mid]>a[right])
		{
			return right;
		}
		else
		{
			return left;
		}
	}
	
	if (a[mid]>a[mid+1])
	{
		return mid+1;
	}
	else if (a[mid-1]>a[mid])
	{
		return mid;
	}

	if (a[left] > a[mid])
	{
		return rotated_pivot(a, left, mid-1);
	}
	else if (a[mid]>a[right])
	{
		return rotated_pivot(a, mid+1, right);
	}
	else
	{
		/*there is no rotation*/
		return left;
	}
}


void test_search(int max_test_sz)
{
	int * a = (int *) malloc(max_test_sz * sizeof(int));
	
	/* a place holder for rotating array "a" */
	int * b = (int *) malloc(max_test_sz * sizeof(int));

	for (int curr_tst_sz = 2; curr_tst_sz < max_test_sz; curr_tst_sz++)
	{
		printf("testing array size %d.\n", curr_tst_sz);
		/* populate the array */
		for (int j = 0; j < curr_tst_sz; j++)
		{
			a[j] = 2*j;
		}

		for (int pivot = 0; pivot < curr_tst_sz; pivot ++)
		{
			/* maybe we can do this in place without using the place holder array "b"? Think about it. */
			memcpy(b /*dest*/, a + pivot /*src*/, (curr_tst_sz - pivot) * sizeof(int) /*size*/);
			memcpy(b + (curr_tst_sz - pivot) /*dest*/, a /*src*/, pivot*sizeof(int) /*size*/);
			memcpy(a /*dest*/, b/*src*/, curr_tst_sz * sizeof(int));
			
			for (int i = 0; i < curr_tst_sz; i++)
			{
				int search_index;
				/* first search for existing items */
				bool res = search(a, curr_tst_sz, a[i], &search_index);
				if (!res)
				{
					printf("ERROR: search returned false for curr_tst_sz %d and item at index %d.\n", curr_tst_sz, i);
				}
				if (search_index != i)
				{
					printf("ERROR: search returned the (wrong) index %d for curr_tst_sz %d for item at index %d.\n", search_index, curr_tst_sz, i);
				}
				
				/* now search for non-existing items */
				/* test items lower than the lower bound */
				if (search(a, curr_tst_sz, -1, &search_index))
				{
					printf("ERROR: search returned index %d for curr_tst_sz %d for item %d.\n", search_index, curr_tst_sz, -1);
				}
				/* test for itmes that do not exist and are between lower bound and higher bound (=2 x curr_tst_sz) */
				for (int i = 0; i < curr_tst_sz; i++)
				{
					if (search(a, curr_tst_sz, i * 2 + 1, &search_index))
					{
						printf("ERROR: search returned index %d for curr_tst_sz %d for item %d.\n", search_index, curr_tst_sz, i * 2 + 1);
					}
				}
			}
		}
	}
	
	free(a);
	free(b);

}