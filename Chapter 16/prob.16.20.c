/*
 *
 * On old cell phones, users typed on a numeric keypad and the phone would provide a list of
 * words that matched these numbers. Each digit mapped to a set of O - 4 letters. Implement an algorithm
 * to return a list of matching words, given a sequence of digits. You are provided a list of valid
 * words (provided in whatever data structure you'd like). The mapping is shown in the diagram below
 * EXAMPLE
 * Input: 8733
 * Output: tree, used
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/* keep the math simple: assume each digit has 4 letter correponding to it */
#define digit_2_letter_tbl_sz (40)
#define digit_2_letter_sz (4)

char digit_2_letter_tbl[] =
{	
	'\0','\0','\0','\0', /* 0 */
	'\0','\0','\0','\0', /* 1 */
	'a', 'b', 'c', '\0', /* 2 */
	'd', 'e', 'f', '\0', /* 3 */
	'g', 'h', 'i', '\0', /* 4 */
	'j', 'k', 'l', '\0', /* 5 */
	'm', 'n', 'o', '\0', /* 6 */
	'p', 'q', 'r', 's',  /* 7 */
	't', 'u', 'v', '\0', /* 8 */
	'w', 'x', 'y', 'z'   /* 9 */
};

/* I will use a trie to read words from a file and store the words in the file */
/* The valid characters are 'a' - 'z' */
#define num_chars ((int) ('z'-'a') + 1)
#define char_index(x) ((unsigned int) (x-'a'))
typedef struct tries
{
	char root;
	struct tries ** next;
	bool word; /*true if the path from the root to this node is a complete word */
} trie;
/*****************************************/
/*             TRIE FUNCTIONS            */
/*****************************************/
trie * create_trie(char root);
void add_word(char * word, trie * t);
bool valid_word(char * word, trie * t);
trie * read_trie(char *file_name);
void free_trie(trie *t);

/*****************************************/
/*              THE SOLUTION             */
/*****************************************/
bool matching_words(char * dig_seq, unsigned int dig_seq_sz, char * matching_word, int offset, trie *t);
int digit_2_letter_len(unsigned int digit);
char digit_2_letter(unsigned int digit, int offset);

int main()
{
	trie * t = read_trie("dict.txt");
	char match_word[128];
	matching_words("8733\0", 4, match_word, 0, t);
	matching_words("32339\0", 5, match_word, 0, t);
	free_trie(t);
	free(t);
	return 0;
}

/*****************************************/
/*              THE SOLUTION             */
/*****************************************/
bool matching_words(char * dig_seq, unsigned int dig_seq_sz, char * matching_word, int offset, trie *t)
{
	if (!dig_seq || !dig_seq_sz)
	{
		return false;
	}

	/* some base cases */
	if (offset == dig_seq_sz)
	{
		if (t->word)
		{
			matching_word[offset] = '\0';
			printf("%s\n", matching_word);
			return true;
		}
		else
		{
			return false;
		}
	}
	char c = dig_seq[offset];

	if ( c < '0' || c > '9')
	{
		return false;
	}
	
	if (t->next == NULL)
	{
		return false;
	}

	unsigned int digit = (unsigned int) (c - '0');
	int dig_2_letter_len = digit_2_letter_len(digit);
	bool res = false;
	for (int i = 0; i < dig_2_letter_len; i ++)
	{
		char match_ch = digit_2_letter(digit, i);
		unsigned int index = char_index(match_ch);
		if (t->next[index] == NULL)
		{
			continue;
		}
		/* a match so far */
		matching_word[offset] = match_ch;
		if (matching_words(dig_seq, dig_seq_sz, matching_word, offset + 1, t->next[index]))
		{
			res = true;
		}
	}

	return res;
}

/* for a digit this method returns the number of letters that correspond to the digit on an old cell phone key pad*/
int digit_2_letter_len(unsigned int digit)
{
	if (digit == 1 || digit == 0)
	{
		return 0;
	}
	if (digit == 7 || digit == 9)
	{
		return 4;
	}
	if (digit > 1 && digit < 9)
	{
		return 3;
	}

	return -1;	/* error case */
}

char digit_2_letter(unsigned int digit, int offset)
{
	if (digit > 9)
	{
		return '\0';	/* error case */
	}
	if (offset > digit_2_letter_len(digit))
	{
		return '\0';	/* error case */
	}
	return digit_2_letter_tbl[digit_2_letter_sz * digit + offset];
}

/*****************************************/
/*             TRIE FUNCTIONS            */
/*****************************************/
trie * create_trie(char root)
{
	trie * res = (trie *) malloc(sizeof(trie));
	res->root = root;
	res->next = NULL;
	res->word = false;
	return res;
}

void add_word(char * word, trie * t)
{
	trie * node = t;
	int len = strlen(word);
	for (int i = 0; i < len; i ++)
	{
		char c = word[i];
		if (c>='A' && c <= 'Z')
		{
			c = c - 'A' + 'a';
		}
		if (c<'a' || c > 'z')
		{
			return;
		}
		if (node->next == NULL)
		{
			trie ** next = (trie **) malloc(num_chars * sizeof(trie*));
			memset(next, 0, num_chars * sizeof(trie*));
			node->next = next;
		}
		int offset = (int) (c - 'a');
		if (node->next[offset] == NULL)
		{
			trie * t = create_trie(c);
			node->next[offset] = t;
		}
		node = node->next[offset];
	}
	node->word = true;
}

bool valid_word(char * word, trie * t)
{
	int len = strlen(word);
	int i = 0;
	while (i < len)
	{
		if (!t->next  || t->next[(int) (word[i]-'a')] == NULL)
		{
			return false;
		}
		t = t->next[(int) (word[i]-'a')];
		i ++;
	}
	return t->word;
}

trie * read_trie(char * file_name)
{
	FILE * f = fopen(file_name, "r");
	if (!f)
	{
		return NULL;
	}
	trie * res = create_trie('0');
	char * buf = (char *) malloc(128 * sizeof(char)); /* no word in english is more than 128 characters */
	size_t sz;
	while (true)
	{
		size_t get = getline(&buf, &sz, f);
		if (get == -1 || get ==0)
		{
			/* end of file */
			break;
		}
		buf[strlen(buf)-1] = '\0';	/* strip the new line character */
		add_word(buf, res);
	}

	fclose(f);
	free(buf);

	return res;
}

void free_trie(trie *t)
{
	if (!t || !t->next)
	{
		return;
	}
	for (int i = 0; i < num_chars; i ++)
	{
		free_trie(t->next[i]);
		free(t->next[i]);
	}

	free(t->next);
	memset(t, 0, sizeof(trie));
}
