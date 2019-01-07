/*
 * Parens: Implement an algorithm to print all valid (e.g., properly opened and closed) combinations
 * of n pairs of parentheses.
 * EXAMPLE
 * Input: 3
 * Output: ( ( () ) ) , ( () () ) , ( () ) () , () ( () ) , () () ()
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help();
int read_number_from_stdin();
void print_parens(int n, char * print_string, char * s);

int main()
{
	print_help();
	int n;
	int s_sz = 1024;
	char * s = (char *) malloc( (2 * s_sz +1)* sizeof(char));
	n = read_number_from_stdin();
	while (n)
	{
		if (n > s_sz)
		{
			s_sz = n;
			s = (char *) realloc(s, (2 * s_sz + 1) * sizeof(char));
		}
		s[2*n] = '\0';
		print_parens(n, s, s);
		n = read_number_from_stdin();
	}
	
	free (s);
	
	return 0;
}

/* this method calls the recursive method for n-1 twice and for n-2 once */
/* this makes the running time exponential. maybe it's not so bad because */
/* the number of unique string with balance parens is exponential anyway. */
void print_parens(int n, char * print_string, char * s)
{
	/* base case */
	if (n == 1)
	{
		s[0] = '(';
		s[1] = ')';
		printf("%s\n", print_string);
		return;
	}
	if (n==0)
	{
		printf("%s\n", print_string);
		return;
	}
		
	/* first case: n-string = ( n-1-string ) */
	s[0] = '(';
	s[2*n-1] = ')';
	print_parens(n-1, print_string, s + 1);
	
	/* second case: n-string = () n-1-string */
	s[0] = '(';
	s[0+1] = ')';
	print_parens(n-1,print_string, s+2);
	
	/* third case: n-string = ( n-2-string ) () */
	if (n>2	)
	{
		s[0] = '(';
		s[2*n-1] = ')';
		s[2*n-2] = '(';
		s[2*n-3] = ')';
		print_parens(n-2, print_string, s+1);
	}	
}

int read_number_from_stdin()
{
	char c = getchar();
	if (c < '0' || c > '9')
	{
		return 0;
	}
	int res = (int) (c - '0');
	
	while(1)
	{
		c = getchar();
		if (c == '\n')
		{
			return res;
		}

		if (c < '0' || c > '9')
		{
			continue;
		}

		res = res * 10;
		res += (int) (c - '0');
	}
}

void print_help()
{
	printf("Enter a number. The program will print all valid n pairs of parentheses. To end the program enter any character other than a number.\n");
}
