#include <iostream>
#include <vector>

using namespace std;

int main( int argc, char* argv[] )
{

  cout << "Hello, world." << endl;

  vector<int> v(3);            // Declare a vector of 3 elements.
  v[0] = 7;
  v[1] = v[0] + 3;
  v[2] = v[0] + v[1];
  for (int i = 0; i < 3; ++i)
    {
      cout << "A[" << i << "] = " << v[i] << endl;
    }

  return 0;
}
