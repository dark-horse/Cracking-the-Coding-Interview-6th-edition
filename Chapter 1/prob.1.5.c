/*
 *
 * There are three types of edits that can be performed on strings: insert a character,
 * remove a character, or replace a character. Given two strings, write a function to check if they are
 * one edit (or zero edits) away.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_strings_equal_len(char * s1, char * s2, int len);
bool check_strings_one_bigger(char * s1, char * s2, int len);
void print_help();

int main()
{
	print_help();
	
	#define inp_ln (128)
	char s1[inp_ln];
	char s2[inp_ln];
	int s1_len, s2_len;
	#undef inp_ln

	while(true)
	{
		bool success;
		s1_len = 0;
		s2_len = 0;
		/* read the two strings from standard input */
		/* assume the strings are separated by blank spaces*/
		char c = getc(stdin);
		while (c == ' ')
		{
			c = getc(stdin);
		}
		while (c != ' ')
		{
			s1[s1_len] = c;
			s1_len ++;
			c = getc(stdin);
		}
		while (c == ' ')
		{
			c = getc(stdin);
		}
		while (c != ' ' && c != '\n')
		{
			s2[s2_len] = c;
			s2_len ++;
			c = getc(stdin);
		}
		while (c != '\n')
		{
			c = getc(stdin);
		}
		s1[s1_len] = '\0';
		s2[s2_len] = '\0';
		printf("strings read are \"%s\" and \"%s\".\n", s1, s2);
		if (s1_len == s2_len)
		{
			success = check_strings_equal_len(s1, s2, s1_len);
		}
		else if (s1_len == s2_len + 1)
		{
			success = check_strings_one_bigger(s1,s2,s1_len);
		}
		else if (s2_len == s1_len + 1)
		{
			success = check_strings_one_bigger(s2,s1,s2_len);
		}
		else
		{
			success = false;
		}
		
		printf ("strings \"%s\" and \"%s\" are %s one edit or less away from each other.\n", s1, s2, success ? "" : "NOT");
	}

	return 0;
}

bool check_strings_equal_len(char * s1, char * s2, int len)
{
	int diff_chars_count = 0;
	for (int i = 0; i < len; i ++)
	{
		if (s1[i] != s2[i])
		{
			if (diff_chars_count)
			{
				return false;
			}
			diff_chars_count ++; /* maybe s1 and s2 differ by one character - replace character edit */
		}
	}
	
	return true;
}

/* checks if s1 is s2 + insert a character */
/* s1 len is bigger by 1 than s2 len */
bool check_strings_one_bigger(char * s1, char * s2, int s1_len)
{
	bool first_diff_found = false;
	for (int i = 0; i < s1_len-1; i ++)
	{
		if (first_diff_found)
		{
			/* compare the current char in the shorter string with the char one space later in the longer string */
			if (s2[i] != s1[i+1])
			{
				return false;
			}
		}
		else
		{
			if (s1[i] != s2[i])
			{
				first_diff_found = true;
			}
		}
	}
	
	return true;
}

void print_help()
{
	printf("Enter two strings separated by space.\n");
	printf("The program will then check if the strings are one edit or less away from each other.\n");
	printf("To end the program, type Ctrl-C.\n");
}
