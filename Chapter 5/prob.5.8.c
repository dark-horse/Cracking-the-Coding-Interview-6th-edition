/*
 *
 * Draw Line: A monochrome screen is stored as a single array of bytes, allowing eight consecutive
 * pixels to be stored in one byte. The screen has width w, where w is divisible by 8 (that is, no byte will
 * be split across rows). The height of the screen, of course, can be derived from the length of the array
 * and the width. Implement a function that draws a horizontal line from ( xl, y) to ( x2, y).
 * The method signature should look something like:
 * drawline(byte[] screen, int width, int xl, int x2, int y)
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawline(char * screen, unsigned int width, unsigned int x1, unsigned int x2, unsigned int y); /*make everything unsigned so we don't have to worry about negative widts, coordinates, etc. */
void print_binary(unsigned char a);
void print_screen(char * screen, unsigned int height, unsigned int width);

int main()
{
	unsigned int width = 4 * 8;
	unsigned int height = 10;
	char* screen = (char *) malloc (height * width / 8 * sizeof(char));
	memset(screen, 0, height * width / 8);
	printf("the screen before drawing any lines\n");
	print_screen(screen, height, width);
	drawline(screen, width, 0, width-1,0); 	/*draw an entire line on the first line of the screen */
	drawline(screen, width, 0, 4, 1);		/*draw the first 4 pixels on the second line of the screen */
	drawline(screen, width, 0, 9, 2);		/*draw the first 9 pixels on the third line of the screen */
	drawline(screen, width, 7, 9, 3);		/*draw pixels 7,8,9 on the fourth line of the screen */
	drawline(screen, width, 7, 29, 4);		/*draw pixels 7 through 29 on the fifth line of the screen */
	drawline(screen, width, 7, 30, 5);		/*draw pixels 7 through 29 on the sixth line of the screen */
	drawline(screen, width, 7, 31, 6);		/*draw pixels 7 through 29 on the sixth line of the screen */
	drawline(screen, width, 29, 31, 7);		/*draw pixels 7 through 29 on the sixth line of the screen */
	drawline(screen, width, 21, 23, 8);		/*draw pixels 7 through 29 on the sixth line of the screen */
	drawline(screen, width, 21, 31, 9);		/*draw pixels 7 through 29 on the sixth line of the screen */
	
	printf("print the screen after all the drawing.\n");
	print_screen(screen, height, width);
	
	free(screen);
	return 0;
}

void drawline(char * screen, unsigned int width, unsigned int x1, unsigned int x2, unsigned int y)
{
	if (x1 >= width || x2 >= width)
	{
		return;
	}

	if (x2 < x1)
	{
		int tmp = x2;
		x2 = x1;
		x1 = tmp;
	}

	unsigned int x1_offset = (x1 / 8);
	unsigned int x1_remainder = x1 % 8;
	unsigned int x2_offset = (x2 / 8);
	unsigned int x2_remainder = (x2 % 8);
	if (x1_offset == x2_offset)
	{
		unsigned char mask1 = (0XFF >> x1_remainder) & (0xFF << (8 - x2_remainder - 1));
		screen[y * width / 8 + x1_offset] = mask1;
		return;
	}
	unsigned char mask = 0XFF >> x1_remainder;
	screen[y * width / 8 + x1_offset] = mask;
	if (x2_offset - x1_offset > 1)
	{
		memset(screen + y * width / 8 + x1_offset + 1, (unsigned char) 0xFF, (x2_offset-x1_offset-1));
	}
	mask = 0xFF << (8-x2_remainder-1);
	screen[y * width / 8 + x2_offset] = mask;
}



void print_binary(unsigned char a)
{
	int binary_sz = 8;		/* assume char has 8 bits */
	unsigned char mask = 0x80;
	for (int i = 0; i < binary_sz; i ++)
	{
		printf("%d", ( (a & mask) >> (binary_sz - 1) ));
		a = a << 1;
	}
}

void print_screen(char * screen, unsigned int height, unsigned int width)
{
	printf("\n************************************\n");
	for (unsigned int i = 0; i < height; i ++)
	{
		printf("row %d \t",i);
		for (unsigned int j = 0; j < width / 8; j ++)
		{
			print_binary(screen[i * width / 8 + j]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n************************************\n");
}
