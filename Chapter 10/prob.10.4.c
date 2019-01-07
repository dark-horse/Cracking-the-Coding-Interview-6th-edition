/*
 *
 * Sorted Search, No Size: You are given an array-like data structure Listy which lacks a size
 * method. It does, however, have an elementAt ( i) method that returns the element at index i in
 * 0( 1) time. If i is beyond the bounds of the data structure, it returns -1. (For this reason, the data
 * structure only supports positive integers.) Given a Li sty which contains sorted, positive integers,
 * find the index at which an element x occurs. If x occurs multiple times, you may return any index.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_list_size(Listy *l, int left, int right);

int main()
{
	return 0;
}

/* The hardest part of this problem is finding the size of the list. After that a binary search would do.*/
/* To find the size of the list we can use something similar to a binary search: */
/* start from the biggest possible index (MAX_INT) and see if there is an element there */
/* if not, cut down the list in two and recurse appropriately */
int find_list_size(Listy *l, int left, int right)
{
	/* base case 1 */
	if (l->elementAt(0) == -1)
	{
		return 0;
	}

	/* base case 2 */
	if (left == right || left == right - 1)
	{
		if (l->elementAt(right) != -1)
		{
			return right + 1;		/* +1 becase index is 0-based and we want size 0 to be for empty Listy */
		}
		else
		{
			return left + 1;		/* +1 becase index is 0-based and we want size 0 to be for empty Listy */
		}
	}

	int mid = (left + right / 2);
	if (l->elementAt(mid) == -1)
	{
		return find_list_size(l, left, mid-1);
	}
	
	if (l->elementAt(mid+1) == -1)
	{
		return mid + 1;		/* +1 becase index is 0-based and we want size 0 to be for empty Listy */
	}
	else
	{
		return find_list_size(l, mid+1, right);
	}
}