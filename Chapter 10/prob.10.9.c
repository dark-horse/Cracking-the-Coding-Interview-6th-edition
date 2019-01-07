/*
 *
 * Sorted Matrix Search: Given an M x N matrix in which each row and each column is sorted in
 * ascending order, write a method to find an element.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool sorted_matrix_search(int search_val, int * matrix, int a_rows, int a_cols, int quadrant_x_low, int quadrant_x_high, int quadrant_y_low, int quadrant_y_high, int * res_x, int *res_y);
bool sorted_arr_search(int search_val, int * arr, int low, int high, int * res);

int * create_sorted_matrix(int rows, int cols);
void print_matrix(int * matrix, int rows, int cols);

int main()
{
	int rows = 10, cols = 10;
	int * matrix = create_sorted_matrix(rows, cols);
	print_matrix(matrix, rows, cols);
	bool search_res;
	int search_x, search_y;
	search_res = sorted_matrix_search(55, matrix, rows, cols, 0, rows-1, 0, cols-1, &search_x, &search_y);
	printf("result of search is %s, x is %d and y is %d.\n", search_res ? "TRUE" : "FALSE", search_x, search_y);
	
	free(matrix);
	return 0;
}

/* we will divide the quadrant we are searching in top and bottom part */
/* based on the values of the begginning and end of the array we will decide which half of the quadrant to search further */
/* at each step we will search at most half of the current quadrant */
/* the running time is O(log (a_rows * a_cols)) */
bool sorted_matrix_search(int search_val, int * matrix, int a_rows, int a_cols, int quadrant_x_low, int quadrant_x_high, int quadrant_y_low, int quadrant_y_high, int * res_x, int *res_y)
{
	if (quadrant_x_low > quadrant_x_high || quadrant_y_low > quadrant_y_high)
	{
		return false;
	}
	if (quadrant_y_low == quadrant_y_high)
	{
		*res_y = quadrant_y_low;
		return sorted_arr_search(search_val, matrix + quadrant_y_low * a_cols, quadrant_x_low, quadrant_x_high, res_x);
	}

	int index_y = (quadrant_y_low + quadrant_y_high) / 2;
	if (matrix[index_y * a_cols + quadrant_x_low] > search_val)
	{
		/* look inside the top quadrant */
		return sorted_matrix_search(search_val, matrix, a_rows, a_cols, quadrant_x_low, quadrant_x_high, quadrant_y_low, index_y-1, res_x, res_y);
	}
	if (matrix[index_y * a_cols + quadrant_x_high] < search_val)
	{
		/*look inside the bottom quadrant */
		return sorted_matrix_search(search_val, matrix, a_rows, a_cols, quadrant_x_low, quadrant_x_high, index_y + 1, quadrant_y_high, res_x, res_y);
	}
	/*search on the index_y row in the matrix */
	*res_y = index_y;
	if (sorted_arr_search(search_val, matrix + index_y * a_cols, quadrant_x_low, quadrant_x_high, res_x))
	{
		return true;
	}
	/* res_x is column where search_val would have fitted in the array */
	/* look in the bottom right quadrant */
	if (sorted_matrix_search(search_val, matrix, a_rows, a_cols, quadrant_x_low, *res_x, index_y, quadrant_y_high, res_x, res_y))
	{
		return true;
	}
	return sorted_matrix_search(search_val, matrix, a_rows, a_cols, *res_x, quadrant_x_high, quadrant_y_low, index_y, res_x, res_y);
}

bool sorted_arr_search(int search_val, int * arr, int low, int high, int * res)
{
	/* base case */
	if (low > high)
	{
		return false;
	}

	int index = (low + high) / 2;
	*res = index;
	if (arr[index] == search_val)
	{
		return true;
	}
	if (arr[index] < search_val)
	{
		return sorted_arr_search(search_val, arr, index + 1, high, res);
	}
	else
	{
		return sorted_arr_search(search_val, arr, low, index - 1, res);
	}
}

int * create_sorted_matrix(int rows, int cols)
{
	if (!rows || !cols)
	{
		return NULL;
	}
	int * res = (int *) malloc(rows * cols * sizeof(int));
	for (int i = 0; i < rows; i ++)
	{
		for (int j = 0; j < cols; j ++)
		{
			res[i*cols +j] = i + 10 * j;
		}
	}
	return res;
}

void print_matrix(int * matrix, int rows, int cols)
{
	if (!matrix || !rows || !cols)
	{
		return;
	}
	for (int i = 0; i < rows; i ++)
	{
		printf("%d",matrix[i * cols + 0]);
		for (int j = 1; j < cols; j ++)
		{
			printf("\t;%d", matrix[i*cols + j]);
		}
		printf("\n");
	}
}