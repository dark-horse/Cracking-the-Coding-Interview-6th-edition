/*
 *
 * Operations: Write methods to implement the multiply, subtract, and divide operations for integers.
 * The results of all of these are integers. Use only the add operator
 *
 */

#include <stdio.h>

int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

int main()
{
	for (int i = 0; i < 10000; i ++)
	{
		for (int j = 0; j < 10000; j ++)
		{
			if (i-j != subtract(i,j))
			{
				printf("Error in subtraction: we show %d-%d=%d, but the answer should be %d.\n", i, j, subtract(i,j), i-j);
			}
			if (i*j != multiply(i,j))
			{
				printf("Error in multiplication: we show %d x %d=%d, but the answer should be %d.\n", i, j, multiply(i,j), i*j);
			}
			if (-i*j != multiply(i,-j))
			{
				printf("Error in multiplication: we show %d x %d=%d, but the answer should be %d.\n", i, -j, multiply(i,-j), -i*j);
			}
			if (-i*j != multiply(-i,j))
			{
				printf("Error in multiplication: we show %d x %d=%d, but the answer should be %d.\n", -i, j, multiply(-i,j), -i*j);
			}
			if (i*j != multiply(i,j))
			{
				printf("Error in multiplication: we show %d x %d=%d, but the answer should be %d.\n", -i, -j, multiply(-i,-j), i*j);
			}
			if (j != 0 && i/j != divide(i,j))
			{
				printf("Error in division: we show %d / %d=%d, but the answer should be %d.\n", i, j, divide(i,j), i/j);
			}
			if (j != 0 && i/(-j) != divide(i,-j))
			{
				printf("Error in division: we show %d / %d=%d, but the answer should be %d.\n", i, -j, divide(i,-j), i/(-j));
			}
			if (j != 0 && (-i)/j != divide(-i,j))
			{
				printf("Error in division: we show %d / %d=%d, but the answer should be %d.\n", -i, j, divide(-i,j), (-i)/j);
			}
			if (j != 0 && (-i)/(-j) != divide(-i,-j))
			{
				printf("Error in division: we show %d / %d=%d, but the answer should be %d.\n", -i, -j, divide(-i,-j), (-i)/(-j));
			}
		}
	}
	return 0;
}

int subtract(int a, int b)
{
	return a + 1 + ~b;
}

int multiply(int a, int b)
{
	if (!a || !b)
	{
		return 0;
	}

	unsigned int mask = 0x80000000;
	int sign_a = 1, sign_b = 1;
	if (a & mask)
	{
		sign_a = -1;
		a = subtract(0,a);
	}
	if (b & mask)
	{
		sign_b = -1;
		b = subtract(0,b);
	}
	int res = 0;
	int cumm = b;
	while (a)
	{
		if (a & 1)
		{
			res += cumm;
		}
		cumm = cumm + cumm;
		a = a >> 1;
	}
	
	if (sign_a != sign_b)
	{
		return subtract(0, res);
	}
	else
	{
		return res;
	}
}

int divide(int a, int b)
{
	if (!b)
	{
		/* error - divide by 0 */
		return -1;/*what's a good error code????*/
	}
	if (!a)
	{
		return 0;
	}

	/* it is easier to work with positive numbers */
	unsigned int mask = 0x80000000;
	int sign_a = 1, sign_b = 1;
	if (a & mask)
	{
		sign_a = -1;
		a = subtract(0,a);
	}
	if (b & mask)
	{
		sign_b = -1;
		b = subtract(0,b);
	}

	int res = 0;
	while (a>=b)
	{
		int counter = 1;
		int tmp = b << 1;
		while (a > tmp)
		{
			counter = counter << 1;
			tmp = tmp << 1;
		}
		res += counter;
		tmp = tmp >> 1;
		a = subtract(a, tmp);
	}

	if (sign_a != sign_b)
	{
		return subtract(0,res);
	}
	else
	{
		return res;
	}
}