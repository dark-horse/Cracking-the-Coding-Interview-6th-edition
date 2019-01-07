/*
 * Recursive Multiply: Write a recursive function to multiply two positive integers without using the
 * "*" operator.You can use addition, subtraction, and bit shifting, but you should minimize the number
 * of those operations.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int multiply(int a, int b);

void print_help();
bool read_int_stdin(int * a);

int main()
{
	print_help();
	while (true)
	{
		int a, b;
		bool calc = read_int_stdin(&a);
		if (!calc)
		{
			break;
		}
		calc = read_int_stdin(&b);
		if (!calc)
		{
			break;
		}
		printf("multiplying %d and %d yields %d. Computer shows %d.\n", a, b, multiply(a, b), a * b);
	}
	return 0;
}

/* calculate the multiplication of a and b using only bit shifting and addition */
int multiply(int a, int b)
{
	/* it is easier to work with positive numbers */
	int sign_a = 1, sign_b = 1;
	if (a < 0)
	{
		sign_a = -1;
		a = 0 - a;
	}
	if (b < 0)
	{
		sign_b = -1;
		b = 0 - b;
	}
	
	/* we will not use recursion even though this problem is in the recursion chapter*/
	int res = 0;
	int cumm = b;
	while (a)
	{
		/* see if a's least significant bit is 1 or 0 */
		if (a & 1)
		{
			res += cumm;
		}
		cumm = cumm + cumm;
		a = a >> 1;
	}

	if (sign_a != sign_b)
	{
		res = 0 - res;
	}
	return res;
}

void print_help()
{
	printf("Enter numbers on each line. For every two numbers the program will calculate the multiplication. Type q to exit the program.\n");
}

bool read_int_stdin(int * a)
{
	int sign = 1;
	bool res = true;
	* a= 0;
	while (true)
	{
		char c = getchar();
		if (c == '\n')
		{
			break;
		}
		if (c == 'q')
		{
			res = false;
			break;
		}
		if (c == '-')
		{
			if (sign == 1 && (*a) == 0)
			{
				/*only the first '-' sign counts*/
				sign = -1;
				continue;
			}
			else
			{
				break;
			}
		}
		if (c <'0' || c > '9')
		{
			break;
		}
		(*a) = (*a) * 10;
		(*a) += (int) (c - '0');
	}
	
	(*a) = (*a) * sign;

	return res;
}