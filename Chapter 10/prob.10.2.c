/*
 *
 *Group Anagrams: Write a method to sort an array of strings so that all the anagrams are next to
 * each other.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int helper_arr[36];

void sort_strings(char * * a, int a_len);
void quick_sort(char * * a, int left, int right);
int partition(char * * a, int left, int right);
int str_cmp(char * a, char * b);
int helper_arr_index(char c);

/* some "administrative" functions and types */
typedef struct resizable_arrays
{
	char ** arr;
	int arr_sz;
	int items_count;
} resizable_array;

void print_string_arr(char ** a, int a_len);
void add_string(resizable_array * a, char * s);
void free_resizable_arr(resizable_array * a);

int main()
{
	resizable_array a;
	memset(&a, 0, sizeof(resizable_array));
	printf("test comparison function.\n");
	printf("comparison for abc and bac is %d.\n", str_cmp("abc", "bac"));
	printf("comparison for abc and cba is %d.\n", str_cmp("abc", "cba"));
	printf("comparison for bac and cab is %d.\n", str_cmp("bac", "cab"));
	printf("comparison for bac and cba is %d.\n", str_cmp("bac", "cba"));
	printf("comparison for abc and cab is %d.\n", str_cmp("abc", "cab"));
	
	printf("comparison for aac and caa is %d.\n", str_cmp("aac", "caa"));
	printf("comparison for aca and aac is %d.\n", str_cmp("aca", "aac"));
	
	printf("comparison for bac and aac is %d.\n", str_cmp("bac", "aac"));
	printf("comparison for aac and bac is %d.\n", str_cmp("aac", "bac"));

	printf("comparison for aabac and abc is %d.\n", str_cmp("aabac", "abc"));
	printf("comparison for abc and aabac is %d.\n", str_cmp("abc", "aabac"));
	printf("comparison for bacas and abc is %d.\n", str_cmp("bacas", "abc"));
	printf("comparison for abc and baca is %d.\n", str_cmp("abc", "bacas"));

	
	add_string(&a, "abc");
	add_string(&a, "cba");
	add_string(&a, "aac");
	add_string(&a, "caa");
	add_string(&a, "bac");
	add_string(&a, "abac");
	add_string(&a, "baac");
	add_string(&a, "bacas");
	add_string(&a, "aca");
	add_string(&a, "cab");
	add_string(&a, "aabac");
	add_string(&a, "aac");
	
	printf("printing the array before sorting.\n");
	print_string_arr(a.arr, a.items_count);
	printf("sort the array and print it after sorting.\n");
	sort_strings(a.arr, a.items_count);
	print_string_arr(a.arr, a.items_count);
	
	free_resizable_arr(&a);


	return 0;
}

/****************************************************/
/*                                                  */
/*              SORTING IMPLEMENTATION              */
/*                                                  */
/****************************************************/

/* we are trying to sort strings so that anagrams are next to each other */
/* to do that, we need a comparison function that compares anagrams equal to each other */
/* the algorithm we will choose to compare strings assumes: */
/* 1. anagrams are case insensitive */
/* 2. anagrams contain only the latin 26 letters and 10 digits */
/* 3. the comparison function has to be total: */
/*    3.a str_cmp(a,b) = 0 - str_cmp(b,a) */
/*    3.b if(str_cmp(a,b) <= 0 and str_cmp(b,c)<=0 then str_cmp(a,c)<=0) */
/* We will use an array of 36 = 26 + 10 integers; */
/*           each slot will contain the number of occurences of the letter in the strings */
int str_cmp(char *a, char *b)
{
	if (!a || !b)
	{
		if(a)
		{
			return 1;
		}
		if(b)
		{
			return -1;
		}
		return 0;
	}
	
	int a_len = strlen(a), b_len = strlen(b);
	if (a_len != b_len)
	{
		return a_len < b_len ? -1:1;
	}

	memset(helper_arr, 0, 36 * sizeof(int));

	for (int i = 0; i < a_len; i++)
	{
		char c = a[i];
		if (c>='A' && c<='Z')
		{
			c = (char) (c-'A'+'a');
		}
		int index = helper_arr_index(c);
		if(index == -1)
		{
			/* invalid input */
			return -1;
		}
		helper_arr [index] ++;
	}

	for (int i = 0; i < b_len; i++)
	{
		char c = b[i];
		if (c>='A' && c<='Z')
		{
			c = (char) (c-'A'+'a');
		}
		int index = helper_arr_index(c);
		if(index == -1)
		{
			/* invalid input */
			return -1;
		}
		helper_arr [index] --;
	}

	for (int i = 0; i < 36; i ++)
	{
		if (helper_arr[i] != 0)
		{
			return helper_arr[i];
		}
	}

	/* "a" and "b" are anagrams. So return equality */
	return 0;
}

int helper_arr_index(char c)
{
	if (c>= 'A' && c<='Z')
	{
		c = (char) ((int) (c-'A'+'a'));
	}
	int index;
	if (c>='a' && c < 'z')
	{
		index = (int)(c-'a');
	}
	else if (c>='0' && c<='9')
	{
		index = 26 + (int) (c-'0');
	}
	else
	{
		/* invalid input */
		return index = -1;
	}
	
	return index;
}

void sort_strings(char * * a, int a_len)
{
	quick_sort(a, 0, a_len-1);
}

void quick_sort(char ** a, int left, int right)
{
	int index = partition(a, left, right);
	if (left < index-1)
	{
		quick_sort(a, left, index-1);
	}
	if (index < right)
	{
		quick_sort(a, index, right);
	}
}

int partition(char * * a, int left, int right)
{
	/* pick the pivot */
	char * pivot = a[(left + right)/2];
	while (left <= right)
	{
		while(str_cmp(a[left], pivot) < 0) left++;

		while(str_cmp(a[right], pivot) > 0) right --;
		
		if (left <= right)
		{
			char * tmp = a[right];
			a[right] = a[left];
			a[left] = tmp;
			left++;
			right --;
		}
	}
	
	return left;
}

/****************************************************/
/*                                                  */
/*             ADMINISTRATIVE FUNCTIONS             */
/*                                                  */
/****************************************************/
void print_string_arr(char ** a, int a_len)
{
	printf("printing the string array of size %d.\n", a_len);
	for(int i = 0; i < a_len; i++)
	{
		printf("\t%s\n",a[i]);
	}
}

void add_string(resizable_array * a, char * s)
{
	if (a->items_count == a->arr_sz)
	{
		a->arr_sz += 32;
		a->arr = realloc(a->arr, a->arr_sz * sizeof(int));
	}
	int s_len = strlen(s);
	char * new_s = (char *) malloc((s_len+1)*sizeof(char));
	memcpy(new_s /*dest*/, s/*src*/, s_len+1);
	a->arr[a->items_count] = new_s;
	a->items_count ++;
}

void free_resizable_arr(resizable_array * a)
{
	for (int i = 0; i < a->items_count; i++)
	{
		free(a->arr[i]);
	}
	free(a->arr);
}