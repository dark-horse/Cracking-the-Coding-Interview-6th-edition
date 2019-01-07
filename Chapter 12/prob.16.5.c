/*
 *
 * Factorial Zeros: Write an algorithm which computes the number of trailing zeros in n factorial.
 *
 */

#include <stdio.h>

void factorization_in_2_and_5(unsigned int a, int * power_of_2, int * power_of_5);
void factorial_zero(unsigned int a, int * power_of_2, int * power_of_5);
int min(int a, int b);

int main()
{
	for (unsigned int i = 1; i < 40; i ++)
	{
		int power_of_2, power_of_5;
		factorial_zero(i,&power_of_2, &power_of_5);
		printf("number of trailing zeros for %d! is %d.\n", i, min(power_of_2,power_of_5));
	}
	return 0;
}

void factorial_zero(unsigned int a, int * power_of_2, int * power_of_5)
{
	/* some base cases */
	if (a == 1 || a == 0)
	{
		*power_of_2 = 0;
		*power_of_5 = 0;
		return;
	}
	
	/* recurse */
	factorial_zero(a - 1, power_of_2, power_of_5);
	int res_2, res_5;
	factorization_in_2_and_5(a, &res_2, &res_5);
	*power_of_2 += res_2;
	*power_of_5 += res_5;
}

void factorization_in_2_and_5(unsigned int a, int * power_of_2, int * power_of_5)
{
	/* first, the power of 2 in a */
	int res_2 = 0;
	unsigned int tmp = a;
	while ( (tmp & 1) == 0)
	{
		res_2 ++;
		tmp = tmp >> 1;
	}
	*power_of_2 = res_2;
	
	/* now the power of 5 */
	int res_5 = 0;
	tmp = a;
	while ( (tmp %5) == 0)
	{
		res_5 ++;
		tmp = tmp / 5;
	}
	*power_of_5 = res_5;
}

int min(int a, int b)
{
	return a<b?a:b;
}
