/*
 * Living People: Given a list of people with their birth and death years, implement a method to
 * compute the year with the most number of people alive. You may assume that all people were born
 * between 1900 and 2000 (inclusive). If a person was alive during any portion of that year, they should
 * be included in that year's count. For example, Person (birth= 1908, death= 1909) is included in the
 * counts for both 1908 and 1909.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define beg_year (1900)
#define end_year (2018)

bool process_cmd_line(char * cmd_line, unsigned int *birth, unsigned int * death);
unsigned int year_most_people_alive(unsigned int * arr, unsigned int arr_sz);
void update_population_arr(unsigned int * arr, unsigned int arr_sz, unsigned int birth, unsigned int death);
void print_help();

int main()
{
	print_help();
	char * cmd_line = (char *) malloc(512 * sizeof(char));
	unsigned int arr_sz = end_year - beg_year + 1;
	unsigned int * arr = (unsigned int *) malloc( arr_sz * sizeof(unsigned int));
	memset(arr, 0, arr_sz * sizeof(unsigned int));
	while (true)
	{
		size_t sz;
		getline(&cmd_line, & sz, stdin);
		unsigned int birth, death;
		bool quit = process_cmd_line(cmd_line, &birth, &death);
		update_population_arr(arr, arr_sz, birth, death);
		if (quit)
		{
			break;
		}
	}

	printf("year with most people alive is %d.\n", year_most_people_alive(arr, arr_sz) + beg_year);

	free(arr);
	free(cmd_line);
	return 0;
}

unsigned int year_most_people_alive(unsigned int * arr, unsigned int arr_sz)
{
	int most_people_alive = arr[0];
	int index = 0;
	for (int i = 1; i < arr_sz; i++)
	{
		if (arr[i] > most_people_alive)
		{
			most_people_alive = arr[i];
			index = i;
		}
	}
	return index;
}

void update_population_arr(unsigned int *arr, unsigned int arr_sz, unsigned int birth, unsigned int death)
{
	if (birth > end_year || birth < beg_year || death < birth)
	{
		/* invalid input */
		return;
	}
	unsigned int beg = birth - beg_year;
	unsigned int end = death ? death - beg_year + 1: arr_sz;
	for (int i = beg; i < end; i ++)
	{
		arr[i] ++;
	}
}

/* returns true if it is time to quit */
bool process_cmd_line(char * cmd_line, unsigned int * birth, unsigned int * death)
{
	if (*cmd_line == 'q')
	{
		return true;
	}
	while (*cmd_line < '0' || *cmd_line > '9')
	{
		cmd_line ++;
	}
	*birth = atoi(cmd_line);

	/* skip to the next integer (death integer) if available */
	while ( *cmd_line >='0' && *cmd_line <= '9')
	{
		cmd_line ++;
	}
	while ((*cmd_line < '0' || *cmd_line > '9') && *cmd_line)
	{
		cmd_line ++;
	}
	if (*cmd_line < '0' || *cmd_line>'9')
	{
		*death = 0;
	}
	else
	{
		*death = atoi(cmd_line);
	}

	return false;
}

void print_help()
{
	printf("on one line at a time, input the birth and, if available, death year for one person.\n");
	printf("type q to calculate the year with  most people alive and to exit the program.\n");
}