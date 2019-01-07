/*
 *
 * Pond Sizes: You have an integer matrix representing a plot of land, where the value at that location
 * represents the height above sea level. A value of zero indicates water. A pond is a region of
 * water connected vertically, horizontally, or diagonally. The size of the pond is the total number of
 * connected water cells. Write a method to compute the sizes of all ponds in the matrix.
 * EXAMPLE
 * Input:
 * 0 2 1 0
 * 0 1 0 1
 * 1 1 0 1
 * 0 1 0 1
 * Output: 2, 4, 1 (in any order)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* the solution to the question */
int resolve_plot(short int * plot, int w, int h, int curr_x, int curr_y);


/* some administrative functions, definitions */
char * cmd_line;
#define cmd_line_sz (256)
bool read_plot(short int ** plot, int * w, int * h);
void print_plot(short int * plot, int w, int h);
void print_help();
int main()
{
	print_help();

	cmd_line = (char *) malloc(cmd_line_sz * sizeof(char));		/* 256 characters are enough for us */
	while (true)
	{
		int w, h;
		short int * plot;
		bool quit = read_plot(&plot, &w, &h);
		if (quit)
		{
			if (plot)
			{
				free(plot);
			}
			break;
		}
		print_plot(plot, w, h);
		for (int i = 0; i < w; i ++)
		{
			for (int j = 0; j < h; j ++)
			{
				int res = resolve_plot(plot, w, h, i, j);
				if (res)
				{
					printf("found a solution: %d.\n", res);
				}
			}
		}
		printf("resolved plot looks like this: ************************\n");
		print_plot(plot,w,h);
		free(plot);
	}

	free(cmd_line);
	return 0;
}

/* the solution to the question */
int resolve_plot(short int * plot, int w, int h, int curr_x, int curr_y)
{
	/* use recursion */
	/* all the square in the plot have positive values */
	/* we will use -1 to mark a square that was already visited */
	if (plot[w * curr_y + curr_x] == -1)
	{
		return 0;
	}
	if (plot[w * curr_y + curr_x] > 0)
	{
		return 0;
	}
	int res = 0;
	/* mark this square as being visited */
	plot[w * curr_y + curr_x] = -1;
	res ++;
	/* recurse to the top (if possible ) */
	if (curr_y > 0)
	{
		res += resolve_plot(plot, w, h, curr_x, curr_y-1);
		if (curr_x > 0)
		{
			res += resolve_plot(plot, w, h, curr_x - 1,curr_y-1);
		}
		if (curr_x < w -1)
		{
			res += resolve_plot(plot, w, h, curr_x + 1, curr_y-1);
		}
	}
	/* recurse one row lower (if possible) */
	if (curr_y < h - 1)
	{
		res += resolve_plot(plot, w, h, curr_x, curr_y + 1);
		if (curr_x > 0)
		{
			res += resolve_plot(plot, w, h, curr_x-1, curr_y + 1);
		}
		if (curr_x < w - 1)
		{
			res += resolve_plot(plot, w, h, curr_x+1, curr_y + 1);
		}
	}
	/* check the node to the left (if possible) */
	if (curr_x > 0)
	{
		res += resolve_plot(plot,w,h,curr_x-1, curr_y);
	}
	/* check the node to the right (is possible) */
	if (curr_x < w - 1)
	{
		res += resolve_plot(plot, w, h, curr_x+1, curr_y);
	}
	return res;
}

/* some administrative functions */

/* will read the plot from the command line */
/* returns true if it is time to quit the program */
bool read_plot(short int ** plot, int * w, int * h)
{
	size_t sz = cmd_line_sz;
	bool quit = false;
	int plot_w = 0, plot_h = 0;
	*plot = NULL, *w = 0, *h = 0;
	getline(&cmd_line, &sz, stdin);
	if (cmd_line[0] == 'q')
	{
		return true;
	}

	plot_w = atoi(cmd_line);
	int i = 0;
	while (cmd_line[i]!= ' ')
	{
		i++;
	}
	plot_h = atoi(cmd_line + i);

	*plot = (short int*) malloc(plot_w * plot_h * sizeof(short int));

	printf("width is %d and height is %d.\n", plot_w, plot_h);
	for (int i = 0; i < plot_h; i ++)
	{
		getline(&cmd_line, &sz, stdin);
		if (cmd_line[0] == 'q')
		{
			quit = true;
			break;
		}
		for (int j = 0; j < plot_w; j++)
		{
			(*plot)[i * plot_w + j] = (short int) (cmd_line[2 * j] - '0');
		}
	}
	*w = plot_w;
	*h = plot_h;
	return quit;
}

void print_plot(short int * plot, int w, int h)
{
	printf("Printing plot with width %d and height %d.\n", w, h);
	for (int i = 0; i < h; i ++)
	{
		printf("\t%d",plot[i * w + 0]);
		for (int j = 1; j < w; j ++)
		{
			printf(" ,%d", plot[i * w + j]);
		}
		printf("\n");
	}
}

void print_help()
{
	printf("Enter the plot width and height on the first line.\n");
	printf("Then enter the each row in the plot one line at a time.\n");
	printf("The height should be one digit from 0 to 9.\n");
	printf("Each line should have the same number of digits.\n");
	printf("Type 'q' on a line by itself to resolve the last entered question and quit the program.\n");
}
