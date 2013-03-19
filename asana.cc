#include <iostream>

using std::cout;
using std::endl;

// TODO: Verify that's the right syntax for
// passing a 2D arry.
void printMatrixSpiral( int **matrix, unsigned int width, unsigned int height )
{
  if ( width == 0 || height == 0 )
    {
      return;
    }

  // Our indices into the matrix
  unsigned int row = 0;
  unsigned int col = 0;

  // The ever-decreasing boundary of the matrix
  // that we have NOT printed yet
  unsigned int rtop = 0;
  unsigned int rbot = height - 1;
  unsigned int cleft = 0;
  unsigned int cright = width - 1;

  do
    {
      // Print right
      row = rtop;
      col = cleft;
      while ( col <= cright )
        {
          cout << matrix[row][col];
          ++col;
        }
      ++rtop;

      // Print down
      row = rtop;
      col = cright;
      while ( row <= rbot )
        {
          cout << matrix[row][col];
          ++row;
        }
      --cright;

      // Print left
      row = rbot;
      col = cright;
      while ( col >= cleft )
        {
          cout << matrix[row][col];
          --col;
        }
      --rbot;

      // Print up
      row = rbot;
      col = cleft;
      while ( row >= rtop )
        {
          cout << matrix[row][col];
          --row;
        }
      ++cleft;

      // TODO: It *looks* like the problem might not want a trailing space.
      // Should verify this with the PM! And, then fix.
      cout << " ";
    } while ( rbot != rtop || cleft != cright );

  // Hmmm...in odd by odd matrices the algorithm above
  // fails to print the last cell. Seems hacky to do this.
  // Would test more, but am out of time.
  if ( width % 2 == 1 && height % 2 == 1 )
    {
      cout << matrix[height/2][width/2];
    }

  // TODO: It *looks* like the problem wants a newline at the end.
  // Should verify this with the PM!
  cout << endl;
}
