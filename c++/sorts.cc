//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>

using std::cout;
using std::endl;
using std::swap;

template <typename T>
void qsort(T *array, int low, int high)
{
  if (low >= high)
  {
    return;
  }

  int m = low;
  int i = 0;

  for (i = low + 1; i <= high; ++i)
  {
    if (array[i] < array[low])
    {
      ++m;
      swap(array[i], array[m]);
    }
  }
  swap(array[low], array[m]);

  qsort(array, low, m - 1);
  qsort(array, m + 1, high);
}

template <typename T>
void InsertionSort(T *array, int len)
{
  int i = 0;
  int j = 0;

  for (i = 0; i < len; ++i)
  {
    for (j = i; j > 0 && array[j] < array[j - 1]; --j)
    {
      swap(array[j], array[j - 1]);
    }
  }
}

template <typename T>
void printArray(T *array, unsigned int length)
{
  unsigned int i = 0;

  for (i = 0; i < length; ++i)
  {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  int a[] = {2, 8, 4, 9, 1, 3, 45, 98, 1, 40};
  unsigned int ARRAY_LEN_A = sizeof(a) / sizeof(int);

  char b[] = {'a', 'e', 'c', 'q', 't', 'f'};
  unsigned int ARRAY_LEN_B = sizeof(b) / sizeof(char);

  printArray(a, ARRAY_LEN_A);
  //  qsort( a, 0, ARRAY_LEN_A - 1 );
  InsertionSort(a, ARRAY_LEN_A);
  printArray(a, ARRAY_LEN_A);

  printArray(b, ARRAY_LEN_B);
  //  qsort( b, 0, ARRAY_LEN_B - 1 );
  InsertionSort(b, ARRAY_LEN_B);
  printArray(b, ARRAY_LEN_B);
}
