//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(int argc, char *argv[])
{
  vector<int> v(3); // Declare a vector of 3 elements.
  v[0] = 7;
  v[1] = v[0] + 3;
  v[2] = v[0] + v[1];
  for (int i = 0; i < 3; ++i)
  {
    cout << "A[" << i << "] = " << v[i] << endl;
  }

  return 0;
}
