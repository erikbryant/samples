#include <functional>
#include <iostream>

using namespace std;

void aFunction( const char *text )
{
  cout << "This is aFunction(), called with argument: /" << text << "/" << endl;
}

int main( int argc, char *argv[] )
{
  function<void ( const char * )> myFunc;

  myFunc = aFunction;

  myFunc( "testing..." );


  //
  // http://www.cprogramming.com/c++11/c++11-lambda-closures.html
  //
  // [] 	Capture nothing
  // [&]	Capture any referenced variable by reference
  // [=]	Capture any referenced variable by making a copy
  // [=, &foo]	Capture any referenced variable by making a copy, but capture variable foo by reference
  // [bar]	Capture bar by making a copy; don't copy anything else
  // [this]	Capture the this pointer of the enclosing class
  //

  function<void ( int )> func;
  int i = 4;
  func = [=](int curr) { cout << "[=] i currently = " << curr << ". My idea of i is = " << i << endl; };
  func(i);
  i = 10;
  func(i);
  func = [&](int curr) { cout << "[&] i currently = " << curr << ". My idea of i is = " << i << endl; };
  func(i);
  i = 20;
  func(i);
}
