/*
 *
 * Permutations without Dups: Write a method to compute all permutations of a string of unique
 * characters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_permutations(char * src, int offset, int line_len);
void print_help();

int main()
{
	print_help();
	size_t size = 1024;
	char * line = (char*) malloc(size * sizeof(char));
	while (1)
	{
		getline(&line, &size, stdin);
		int line_len = strlen(line);
		/* remove the new line from the input (getline returns a string with newline in it) */
		line[line_len-1] = '\0';
		line_len --;
		
		if (strncmp(line, "q\0", 2) == 0)
		{
			break;
		}
		printf("input line:%s.\n", line);

		print_permutations(line, 0, line_len);
	}
	
	printf("free the buffer.\n");
	free(line);

	return 0;
}


void print_permutations(char * src, int offset, int line_len)
{
	/*base case */
	if (offset == line_len)
	{
		printf("%s\n", src);
		return;
	}

	for (int i = offset; i < line_len; i ++)
	{
		char tmp_1 = src[i];
		char tmp_2 = src[offset];

		src[i] = tmp_2;
		src[offset] = tmp_1;

		print_permutations(src, offset + 1, line_len);

		src[i] = tmp_1;
		src[offset] = tmp_2;
	}
}

void print_help()
{
	printf("enter a string with unique characters. The program will print all permutations. To exit press q on a line by itself.\n");
}
