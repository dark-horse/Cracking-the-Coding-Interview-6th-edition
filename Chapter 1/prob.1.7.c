/*
 *
 * Given an image represented by an NxN matrix, where each pixel in the image is 4
 * bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void rotate_90_degrees(int * img_src, int * img_dest, int img_sz);
void rotate_90_degrees_in_place(int * img, int img_sz);
void rotate_side_90_degrees(int * img, int img_sz, int side_number);
void print_img(int * img, int img_sz);
int * create_sample_img(int img_sz);



int main()
{
	int img_sz = 4;
	int * sample_img = create_sample_img(img_sz);
	int * dest_img = (int *) malloc(img_sz * img_sz *sizeof(int));

	printf("input matrix.\n");
	print_img(sample_img, img_sz);

	/*do not rotate in place first */
	rotate_90_degrees(sample_img, dest_img, img_sz);
	/* result from usual rotation (not in place) */
	printf("rotated matrix.\n");
	print_img(dest_img, img_sz);

	/*now rotate in place*/
	rotate_90_degrees_in_place(sample_img, img_sz);
	printf("\n\nrotated after rotation in place.\n");
	print_img(sample_img, img_sz);
	
	/*check if both rotations have the same result */
	for (int i = 0; i < img_sz; i ++)
	{
		for (int j = 0; j < img_sz; j ++)
		{
			if (dest_img[i*img_sz + j] != sample_img[i*img_sz + j])
			{
				printf("rotations did not yield the same result. ERROR.\n");
			}
		}
	}
	
	free(sample_img);
	free(dest_img);
}


/* this function rotates an image 90 degrees clockwise */
void rotate_90_degrees(int * img_src, int * img_dest, int img_sz)
{
	/* i = vert in source, j = horiz in source */
	for (int i = 0; i < img_sz; i++)
	{
		for (int j = 0; j < img_sz; j++)
		{
			/* src */
			int src = img_src[img_sz * i + j];
			int dest_horiz_index = img_sz-1-i;
			int dest_vert_index = j;
			img_dest[img_sz * dest_vert_index + dest_horiz_index] = src;
		}
	}
}

/* function to print an image made of img_sz x img_sz pixels */
/* each pixel is 4-byte integer */
void print_img(int * img, int img_sz)
{
	printf ("**************************\n");
	printf ("printing image of size %d.\n", img_sz);
	
	for (int i = 0; i < img_sz; i++)
	{
		printf("\t");
		printf("%d", img[i * img_sz]);
		for (int j = 1; j < img_sz; j++)
		{
			printf(";\t%d", img[i * img_sz + j]);
		}
		printf("\n");
	}
	printf ("**************************\n");
}

/* this function rotates a matrix of img_sz x img_sz pixels 90 degrees clockwise */
/* the function does not need another array, it does everything in place */
/* the algorithm is to rotate the outer "sides" of the matrix at once */
void rotate_90_degrees_in_place(int * img, int img_sz)
{
	int j = img_sz / 2;
	for (int i = 0; i < j; i++)
	{
		rotate_side_90_degrees(img, img_sz, i);
	}
}

void rotate_side_90_degrees(int * img, int img_sz, int side_number)
{
	/* the size of the side */
	int side_sz = img_sz - 2 * side_number;
	/* the coordinates of the top left cell of these side */
	int top_left_y = side_number * img_sz + side_number;
	
	/* we will rotate four pixels at a time, so we need some temporary variables */
	int temp_1, temp_2, temp_3, temp_4;
	
	for (int i = 0; i < side_sz - 1; i ++)
	{
		/* the pixel on the top side */
		int top_side_addr = top_left_y + i;
		temp_1 = img[top_side_addr];
		/* the pixel on the right side */
		int right_side_addr = top_left_y + side_sz - 1 + i * img_sz;
		temp_2 = img[right_side_addr];
		/* the pixel on the bottom side */
		int bottom_side_addr = top_left_y + (side_sz - 1) * img_sz + side_sz - 1 - i;
		temp_3 = img[bottom_side_addr];
		/* the pixel on the left side */
		int left_side_addr = top_left_y + img_sz * (side_sz - 1 - i);
		temp_4 = img[left_side_addr];
		
		/* now move the four pixels around the clock */
		img[right_side_addr] = temp_1;
		img[bottom_side_addr] = temp_2;
		img[left_side_addr] = temp_3;
		img[top_side_addr] = temp_4;
	}
}

int * create_sample_img(int img_sz)
{
	int * res = (int *) malloc (img_sz * img_sz * sizeof(int));
	for (int i = 0; i < img_sz; i ++)
	{
		for (int j = 0; j < img_sz; j++)
		{
			res[i * img_sz +j] = i * img_sz +j;
		}
	}
	return res;
}