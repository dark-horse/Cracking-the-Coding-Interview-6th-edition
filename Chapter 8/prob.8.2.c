/*
 * Robot in a Grid: Imagine a robot sitting on the upper left corner of grid with r rows and c columns.
 * The robot can only move in two directions, right and down, but certain cells are "off limits" such that
 * the robot cannot step on them. Design an algorithm to find a path for the robot from the top left to
 * the bottom right.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* the function for this  assigment */
void solve_grid(unsigned short * grid, unsigned int x, unsigned int y, unsigned int rows, unsigned int cols);

/* "administrative" functions */
/* the convention for this exercise is that 0s represent obstacles */
/* 1s represent a path, every other number is an empty cell in the grid */
void print_grid(unsigned short * grid, unsigned int rows, unsigned int cols);
void print_grid_char(unsigned short ch);
unsigned short * create_grid(unsigned short rows, unsigned short cols);

int main()
{
	unsigned int rows = 10;
	unsigned int cols = 10;
	unsigned short * grid = create_grid(rows,cols);
	/* start putting some obstacles */
	/* obstacles are represented by 0s (they print better ) */
	memset(grid + 0 * rows + 1, 0, (cols-1)*sizeof(unsigned short));
	memset(grid + 1 * rows + 1, 0, (cols-1)*sizeof(unsigned short));
	memset(grid + 2 * rows + 1, 0, (cols-1)*sizeof(unsigned short));
	
	printf("grid before solution.\n");
	print_grid(grid, rows, cols);
	
	solve_grid(grid, 0, 0, rows, cols);
	printf("grid after solution.\n");
	print_grid(grid, rows, cols);

	free (grid);
	return 0;
}

/* maybe we should return a boolean if there is at least one solution? */
void solve_grid(unsigned short * grid, unsigned int x, unsigned int y, unsigned int rows, unsigned int cols)
{
	if (!grid || !rows || !cols || x >= rows || y >= cols)
	{
		return;
	}
	unsigned short prev = grid[x*rows + y];
	/* mark our territory */
	grid[x * rows + y] = 1;
	if(y < cols-1 && grid[x*rows + y + 1] != 0)
	{
		solve_grid(grid, x, y+1, rows, cols);
	}
	if (x < rows - 1 && grid[(x+1) * rows + y] != 0)
	{
		solve_grid(grid,x+1, y, rows, cols);
	}
	grid[x*rows+y] = prev;
}


void print_grid(unsigned short * grid, unsigned int rows, unsigned int cols)
{
	if (!grid || !rows || !cols)
	{
		return;
	}

	for (unsigned int i = 0; i < rows; i ++)
	{
		print_grid_char(grid[i * cols + 0]);
		for (unsigned j = 1; j < cols; j ++)
		{
			printf("; ");
			print_grid_char(grid[i * cols + j]);
		}
		printf("\n");
	}
}

void print_grid_char(unsigned short ch)
{
	if (ch == 0 || ch == 1)
	{
		printf("%d", ch);
	}
	else
	{
		printf(" ");
	}
}

unsigned short * create_grid(unsigned short rows, unsigned short cols)
{
	unsigned short * res = (unsigned short *) malloc (rows * cols * sizeof(unsigned short));
	memset(res, 2, rows * cols * sizeof(unsigned short));
	return res;
}