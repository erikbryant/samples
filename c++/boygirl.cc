//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//
// Implementation of a sample interview question taken from somewhere,
// but I've forgotten the URL. Essentially...
// Every family had a child until that child is a boy. Then they stop.
// What percentage of children are boys?
//
// Working this out on paper I got 1/2 boys, 1/2 girls. This Monte
// Carlo simulation gives that same result!
//

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

unsigned int haveChildren(void)
{
  unsigned int girls = 0;

  // Boy == 0, girl == 1
  while (rand() % 2 == 1)
  {
    girls++;
  }

  return girls;
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  unsigned int i = 0;
  unsigned int boys = 0;
  unsigned int girls = 0;

  for (i = 0; i < 10000000; ++i)
  {
    girls += haveChildren();
    boys += 1;
  }

  cout << "Boys: " << boys << " Girls: " << girls << endl;
}
