/*
 *
 * Number Max: Write a method that finds the maximum of two numbers. You should not use if-else
 * or any other comparison operator.
 *
 */

#include <stdio.h>
#include <limits.h>

int my_max(int a, int b);
int abs_value(int a);
int main()
{
	int a, b;
	
	a = 1; b = 1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = 1; b = 2;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = 2; b = 1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = -1; b = 1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = 1; b = -1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = 1; b = 0;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = 0; b = 1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));

	a = -10; b = 1;
	printf("max of %d and %d is %d.\n", a, b, my_max(a,b));
	
	return 0;
}

int my_max(int a, int b)
{
	return ( (a+b+abs_value(a-b)) / 2);
}

/* returns the absolute value for integer a */
/* assumes negative numbers are coded in 2's complement */
int abs_value(int a)
{
    unsigned int mask = 0x80000000; /* need to be unsigned int */
    int b = (a & mask)>>31; 		/* b = 0 if a >= 0; 1 otherwise */
    b = b * -1;						/* b = 0 if a >= 0, -1 otherwise;*/
    b = b * a; 						/* b = 0 if a >= 0, -a otherwise;*/
    int c = (-a & mask)>>31;		/* c = 0 if a <= 0; 1 otherwise*/
    c = c * a;						/* c = 0 if a<=0; a otherwise*/
    return b + c;
}
