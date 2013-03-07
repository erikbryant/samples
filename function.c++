#include <functional>
#include <iostream>

using namespace std;

void aFunction( void )
{
  cout << "This is aFunction()" << endl;
}

int main( int argc, char *argv[] )
{
  function<void ()> myFunc;

  myFunc = aFunction;

  myFunc();
}
