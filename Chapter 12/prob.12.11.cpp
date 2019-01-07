/*
 *
 * 20 Alloc: Write a function in C called my2DA1loc which allocates a two-dimensional array. Minimize
 * the number of calls to malloc and make sure that the memory is accessible by the notation
 * arr[i][j ].
 */

#include <stdio.h>
#include <stdlib.h>

template < class T > class two_d_alloc
{
private:
  T * my_array;
  int num_rows;
  int num_cols;
public:
  two_d_alloc (int rows, int cols)
  {
    num_rows = rows;
    num_cols = cols;
    my_array = new T[num_rows * num_cols];
  };
  ~two_d_alloc()
  {
    delete [] my_array;
	my_array = NULL;
	num_rows = 0;
	num_cols = 0;
  }
  T *operator[] (int i)
  {
    return my_array + i * num_cols;
  };
  void print_cell(int row, int col)
  {
    printf("value at row %d and cell %d is %.\n",row, col, my_array[row * num_cols + col]);
  };
  void print_all()
  {
    for (int i = 0; i < num_rows; i ++) 
    {
        for (int j = 0; j < num_cols; j++)
        {
            printf("\t%d",my_array[i * num_cols + j]);
        }
        printf("\n");
    }
  };
};

int main ()
{
  two_d_alloc < int >t = two_d_alloc<int> (2, 3);
  t[0][0] = 0;
  t[0][1] = 1;
  t[0][2] = 2;
  t[1][0] = 3;
  t[1][1] = 4;
  t[1][2] = 5;
  
  t.print_all();

  return 0;
}