/*
 *
 * String Compression: Implement a method to perform basic string compression using the counts
 * of repeated characters. For example, the string aabcccccaaa would become a2blc5a3. If the
 * "compressed" string would not become smaller than the original string, your method should return
 * the original string. You can assume the string has only uppercase and lowercase letters (a - z).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_compression(char * input, unsigned int input_sz, char ** output, unsigned int * output_sz);

void string_decompression(char * input, unsigned int input_sz, char ** output, unsigned int * output_sz);

void print_compressed_string(char * input, unsigned int input_sz);

int main()
{
	char * s = "daabbbcccccaaab";
	char * compressed;
	unsigned int compressed_sz;
	string_compression(s, strlen(s), &compressed, &compressed_sz);
	print_compressed_string(compressed, compressed_sz);
	char * decompressed;
	unsigned int decompressed_sz;
	string_decompression(compressed, compressed_sz, &decompressed, &decompressed_sz);
	printf("decompressed string: %s.\n", decompressed);

	free(compressed);
	return 0;
}

/* Somehow we have to let the user know if the output string is the same as the input string */
/* (in case the compression algorithm gives a string with longer length) */
/* The convention we will have is if the first character in the string is '\0' then the string is compressed */
/* otherwise it is not */
void string_compression(char * input, unsigned int input_sz, char ** output, unsigned int * output_sz)
{
	if (!input || input_sz <= 4 )
	{
		*output = input;
		*output_sz = input_sz;
		return;
	}

	/* first see if the compressed len of the string is smaller than the initial size */
	unsigned int out_sz = 1;	/* 1 for the first '\0' character */
	unsigned int char_sz = sizeof(char) * 8;
	char prev_ch = input[0];
	unsigned short prev_ch_occurences = 1;
	for (int i = 1; i < input_sz; i ++)
	{
		char curr_ch = input[i];
		if (curr_ch == prev_ch && prev_ch_occurences < char_sz)
		{
			prev_ch_occurences ++;
		}
		else
		{
			out_sz ++;		/* ++ for writing prev_ch_occurences */
			out_sz ++;		/* ++ for writing the char */
			prev_ch_occurences = 1;
			prev_ch = curr_ch;
		}
	}

	out_sz ++;		/* ++ for writing prev_ch_occurences for the last chunk */
	out_sz ++;		/* ++ for writing the char in the last chunk*/

	if (out_sz >= input_sz + 1)
	{
		*output = input;
		*output_sz = input_sz;
		return;
	}
	char * res = (char *) malloc(out_sz * sizeof(char));
	res[0] = '\0';
	unsigned int res_offset = 1;
	prev_ch = input[0];
	prev_ch_occurences = 1;
	for (int i = 1; i < input_sz; i ++)
	{
		char curr_ch = input[i];
		if (curr_ch == prev_ch && prev_ch_occurences < char_sz)
		{
			prev_ch_occurences ++;
		}
		else
		{
			res[res_offset] = prev_ch;
			res[res_offset + 1] = prev_ch_occurences;
			prev_ch_occurences = 1;
			prev_ch = curr_ch;
			res_offset +=2;
		}
	}
	res[res_offset] = prev_ch;
	res[res_offset + 1] = prev_ch_occurences;
	
	*output = res;
	*output_sz = out_sz;
}

void string_decompression(char * input, unsigned int input_sz, char ** output, unsigned int * output_sz)
{
	if (!input || input_sz <= 4 || input[0] != '\0')
	{
		*output = input;
		*output_sz = input_sz;
		return;
	}

	unsigned int decompressed_sz = 0;
	unsigned int i = 1;	/* skip the first '0' in the compressed string */
	while (i < input_sz)
	{
		char a = input[i];
		i ++;
		a = input[i];
		unsigned int chunk_sz = (unsigned int) (a - 0);
		decompressed_sz += chunk_sz;
		i++;
	}

	char * res = (char *) malloc( (decompressed_sz + 1) * sizeof(char));
	i = 1;	/* skip the first '0' in the compressed string */
	unsigned int out_pos = 0;
	while (i < input_sz)
	{
		char a = input[i];
		i ++;
		char b = input[i];
		unsigned int chunk_sz = (unsigned int) (b - 0);
		i++;
		
		/* Is there a faster way to copy 'chunk_sz' characters into a buffer? */
		for (unsigned int j = 0; j < chunk_sz; j ++)
		{
			res[out_pos] = a;
			out_pos ++;
		}
	}

	res[decompressed_sz] = '\0';
	*output = res;
	*output_sz = decompressed_sz + 1;
}

void print_compressed_string(char * input, unsigned int input_sz)
{
	if (!input || !input_sz)
	{
		return;
	}
	printf("compressed string: ");
	if (input_sz <= 4 || input[0] != '\0')
	{
		printf("%s.\n", input);
		return;
	}
	unsigned int i = 1;
	while (i < input_sz)
	{
		char a = input[i];
		i ++;
		printf("%c", a);
		unsigned short occurences = input[i];
		printf("%d", occurences);
		i++;
	}
	printf(".\n");
}