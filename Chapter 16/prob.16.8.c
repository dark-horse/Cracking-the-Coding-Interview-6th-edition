/*
 * 
 * English Int: Given any integer, print an English phrase that describes the integer (e.g., "One Thousand,
 * Two Hundred Thirty Four").
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define beg_year (1900)
#define end_year (2018)

/* the assignment question */
void int_to_english_phrase(int a);
void print_tens(int a);
void print_hundreds(int a);

char * tens_to_english_tbl[] = {"Zero", "Ten", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
char * one_digit_to_english_tbl[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
char * teens_to_english_tbl[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifthteen", "Sixteen", "Seventeen", "Eigtheen", "Nineteen"};

bool process_cmd_line(char * cmd_line, int * a);
void print_help();

int main()
{
	print_help();
	char * cmd_line = (char *) malloc(512 * sizeof(char));
	while (true)
	{
		size_t sz;
		getline(&cmd_line, & sz, stdin);
		int a;
		bool quit = process_cmd_line(cmd_line, &a);
		if (quit)
		{
			break;
		}
		int_to_english_phrase(a);
	}

	free(cmd_line);
	return 0;
}

/* the assignment question */
void int_to_english_phrase(int a)
{
	if (!a)
	{
		printf("Zero\n");
		return;
	}

	if (a < 0)
	{
		printf("Minus ");
		a = 0 - a;
	}
	/* an integer can have at most billions */
	int billions = 0, millions = 0, thousands = 0, ones = 0;
	ones = a % 1000;
	thousands = (a / 1000) % 1000;
	millions = (a / 1000000) % 1000;
	billions = (a / 1000000000) % 1000;
	if (billions)
	{
		print_hundreds(billions);
		printf("Billion%s", billions == 1 ? " " : "s ");
	}
	if (millions)
	{
		print_hundreds(millions);
		printf("Million%s", millions == 1 ? " " : "s ");
	}
	if (thousands)
	{
		print_hundreds(thousands);
		printf("Thousand%s", thousands == 1 ? " " : "s ");
	}
	print_hundreds(ones);
	printf("\n");
}

/* a is a number between 0 and 999 */
void print_hundreds(int a)
{
	int b = a / 100;
	if (b)
	{
		printf("%s Hundred", one_digit_to_english_tbl[b]);
		if (b > 1)
		{
			printf("s");
		}
		printf(" ");
	}
	print_tens(a % 100);
}

/* a is a number between 0 and 99 */
void print_tens(int a)
{
	if (a >= 10 && a < 20)
	{
		printf("%s ",teens_to_english_tbl[a-10]);
		return;
	}
	int b = a / 10;
	if (b)
	{
		printf("%s ", tens_to_english_tbl[b]);
	}
	a = a % 10;
	if (a)
	{
		printf("%s ", one_digit_to_english_tbl[a]);
	}
}

/* returns true if it is time to quit */
bool process_cmd_line(char * cmd_line, int * a)
{
	if (*cmd_line == 'q')
	{
		return true;
	}
	*a = atoi(cmd_line);

	return false;
}

void print_help()
{
	printf("on one line at a time, input the the integer to be printed as an English phrase.\n");
	printf("type q to calculate the year with  most people alive and to exit the program.\n");
}