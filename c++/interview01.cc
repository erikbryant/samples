#include <iostream>

using std::cout;
using std::endl;

void printMatrixSpiral(int matrix[3][3], unsigned int width, unsigned int height)
{
  if (width == 0 || height == 0)
  {
    return;
  }

  // Our indices into the matrix
  int row = 0;
  int col = 0;

  // The ever-decreasing boundary of the matrix
  // that we have NOT printed yet
  int rtop = 0;
  int rbot = height - 1;
  int cleft = 0;
  int cright = width - 1;

  while (1)
  {
    // Print right
    row = rtop;
    col = cleft;
    while (col <= cright)
    {
      cout << matrix[row][col] << " ";
      ++col;
    }
    ++rtop;

    if (rtop > rbot || cleft > cright)
    {
      break;
    }

    // Print down
    row = rtop;
    col = cright;
    while (row <= rbot)
    {
      cout << matrix[row][col] << " ";
      ++row;
    }
    --cright;

    if (rtop > rbot || cleft > cright)
    {
      break;
    }

    // Print left
    row = rbot;
    col = cright;
    while (col >= cleft)
    {
      cout << matrix[row][col] << " ";
      --col;
    }
    --rbot;

    if (rtop > rbot || cleft > cright)
    {
      break;
    }

    // Print up
    row = rbot;
    col = cleft;
    while (row >= rtop)
    {
      cout << matrix[row][col] << " ";
      --row;
    }
    ++cleft;

    if (rtop > rbot || cleft > cright)
    {
      break;
    }
  }

  // TODO: It *looks* like the problem wants a newline at the end.
  // Should verify this with the PM!
  cout << endl;
}

int main(int argc, char *argv[])
{
  int matrix_3_3[3][3] =
      {
          {1, 2, 3},
          {8, 9, 4},
          {7, 6, 5}};

  printMatrixSpiral(matrix_3_3, 1, 1);
  printMatrixSpiral(matrix_3_3, 1, 2);
  printMatrixSpiral(matrix_3_3, 1, 3);
  cout << endl;
  printMatrixSpiral(matrix_3_3, 2, 1);
  printMatrixSpiral(matrix_3_3, 2, 2);
  printMatrixSpiral(matrix_3_3, 2, 3);
  cout << endl;
  printMatrixSpiral(matrix_3_3, 3, 1);
  printMatrixSpiral(matrix_3_3, 3, 2);
  printMatrixSpiral(matrix_3_3, 3, 3);

  return 0;
}
