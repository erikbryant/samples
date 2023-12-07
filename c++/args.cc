//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
  cout << "Hello, world!" << endl;
  for (int i = 0; i < argc; i++)
  {
    cout << "argv[" << i << "]: " << argv[i] << endl;
  }
}
