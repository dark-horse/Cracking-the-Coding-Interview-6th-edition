/*
 *
 * Pattern Matching: You are given two strings, pattern and value. The pattern string consists of
 * just the letters a and b, describing a pattern within a string. For example, the string catcatgocatgo
 * matches the pattern aabab (where cat is a and go is b). It also matches patterns like a, ab, and b.
 * Write a method to determine if value matches pattern.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_pattern(char * value, char * pattern);

/* these checksums have the property that they fast to calculate, to compare and to compose */
/* given a pattern, we will try all different values for strings <a> and <b> and see if all checksums match */
/* if all the checksums match, then we will do a brute-force check */
void checksums(char * s, unsigned int s_sz, unsigned int *checksum1, unsigned int *checksum2, unsigned int *checksum3);

#define max(a,b) ((a)>(b) ? a : b)

bool brute_force_check(char * value, char * pattern, unsigned int a_len, unsigned int b_len);
void flip_a_b(char * pattern);


int main()
{
	bool res = brute_force_check("catcatgocatgo\0", "aabab\0", 3, 2);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatgocatgo\0", "bbaba\0", 2, 3);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatgocatgo\0", "ab\0", 3, 2);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatgocatgo\0", "aba\0", 6, 1);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatgocatgo\0", "aba\0", 1, 11);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatgocatgo\0", "aba\0", 5, 3);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatcatcatcat\0", "aba\0", 2, 1);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatcatcatcatcat\0", "aaa\0", 3, 0);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = brute_force_check("catcatcatcatcatcat\0", "aab\0", 3, 3);
	printf ("BRUTE FORCE CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");

	res = check_pattern("catcatgocatgo\0", "aabab\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatgocatgo\0", "bbaba\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatgocatgo\0", "ab\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatgocatgo\0", "aba\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatcatcatcat\0", "aba\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatcatcatcatcat\0", "aaa\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catcatcatcatcatcat\0", "aab\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catatatcatcatcat\0", "abbaa\0");
	printf ("NEW CHECK value matches pattern: %s\n", res ? "TRUE" : "FALSE");
	res = check_pattern("catatatcatcatcat\0", "abbaaa\0");
	printf ("NEW CHECK valuematches pattern: %s\n", res ? "TRUE" : "FALSE");

	return 0;
}

bool check_pattern(char * value, char * pattern)
{
	/* some base cases */
	if (!value || !pattern)
	{
		return false;
	}
	if (strncmp(pattern, "a\0", 2) == 0 || strncmp(pattern, "b\0", 2) == 0)
	{
		return true;
	}
	if (strlen(value) > 1 && (strncmp(pattern, "ab\0", 3) == 0 || strncmp(pattern, "ba\0", 3) == 0))
	{
		return true;
	}

	int value_sz = strlen(value);
	int pattern_sz = strlen(pattern);
	unsigned int val_c1, val_c2, val_c3;
	checksums(value, value_sz, &val_c1, &val_c2, &val_c3);

	unsigned int number_a_s = 0, number_b_s = 0;
	int first_a_offset = -1, first_b_offset = -1;
	
	for (int i = 0; i < pattern_sz; i ++)
	{
		if (pattern[i] == 'a')
		{
			number_a_s ++;
			first_a_offset = first_a_offset < 0 ? i : first_a_offset;
		}
		else if (pattern[i] == 'b')
		{
			number_b_s ++;
			first_b_offset = first_b_offset < 0 ? i : first_b_offset;
		}
	}

	/* assert number_a_s + number_b_s == pattern_sz (i.e. pattern has only a's and b's) */

	unsigned int max_code_sz = value_sz / max(number_a_s, number_b_s);
	for (int i = 1; i <= max_code_sz; i ++)
	{
		unsigned int a_c1 = 0, a_c2 = 0, a_c3 = 0;
		unsigned int b_c1 = 0, b_c2 = 0, b_c3 = 0;
		unsigned a_len = 0, b_len = 0;
		if (number_a_s > number_b_s)
		{
			a_len = i;
			b_len = number_b_s ? (value_sz - a_len * number_a_s) / number_b_s : 0;
		}
		else
		{
			b_len = i;
			a_len = number_a_s ? (value_sz - b_len * number_b_s) / number_a_s : 0;
		}
		if (a_len)
		{
			checksums(value + first_a_offset * b_len, a_len, &a_c1, &a_c2, &a_c3);
		}
		if (b_len)
		{
			checksums(value + first_b_offset * a_len, b_len, &b_c1, &b_c2, &b_c3);
		}
		if (a_c1 * number_a_s + b_c1 * number_b_s != val_c1)
		{
			continue;
		}
		if (a_c2 * number_a_s + b_c2 * number_b_s != val_c2)
		{
			continue;
		}
		if (a_c3 * number_a_s + b_c3 * number_b_s != val_c3)
		{
			continue;
		}
		if (brute_force_check(value, pattern, a_len, b_len))
		{
			return true;
		}
	}

	return false;
}

void checksums(char * s, unsigned int s_sz, unsigned int * checksum1, unsigned int *checksum2, unsigned int *checksum3)
{
	unsigned int c1 = 0, c2 = 0, c3 = 0;
	for (int i = 0; i < s_sz; i ++)
	{
		c1 ++;
		c2 += (unsigned int) s[i];
		c3 += (unsigned int) s[i] * (unsigned int) s[i];
	}
	*checksum1 = c1;
	*checksum2 = c2;
	*checksum3 = c3;
}

/* also assume pattern is not "a", "ab" */
bool brute_force_check(char * value, char * pattern, unsigned int a_len, unsigned int b_len)
{
	char *a = NULL;
	char *b = NULL;
	unsigned int pattern_offset = 0;
	unsigned int value_offset = 0;
	char c = pattern[pattern_offset];
	while (c)
	{
		if (c == 'b' && b == NULL)
		{
			b = value + value_offset;
			value_offset += b_len;
			pattern_offset ++;
			c = pattern[pattern_offset];
			continue;
		}

		if (c == 'a' && a == NULL)
		{
			a = value + value_offset;
			value_offset += a_len;
			pattern_offset ++;
			c = pattern[pattern_offset];
			continue;
		}

		if (c == 'a')
		{
			if (strncmp(a, value + value_offset, a_len))
			{
				return false;
			}
			value_offset += a_len;
		}
		else
		{
			if (strncmp(b, value + value_offset, b_len))
			{
				return false;
			}
			value_offset += b_len;
		}

		pattern_offset ++;
		c = pattern[pattern_offset];
	}
	return true;
}

void flip_a_b(char * pattern)
{
	while (*pattern)
	{
		if (*pattern == 'a')
		{
			*pattern = 'b';
		}
		else
		{
			*pattern = 'a';
		}
		pattern ++;
	}
}