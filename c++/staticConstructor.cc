//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>

//
// A very simple example of using a static member function
// to create new instances of the class. Also known as the
// factory design pattern.
//
// There was a discussion about static constructors (a
// concept that doesn't exist in C++). I put this
// together to answer a point on that thread. Someone
// in another thread had metaphorically called factory
// functions static constructors and I wanted to bring
// the two discussions together. But, first, I wanted
// to try it.
//

using std::cout;
using std::endl;

class Foo
{
public:
  static Foo *makeFoo()
  {
    return new Foo;
  }
  void showValue()
  {
    cout << "This Foo's value is: " << bar << endl;
  }

private:
  int bar;
  Foo() : bar(99)
  {
  }
};

int main(int argc, char *argv[])
{
  Foo *myFoo = Foo::makeFoo();

  myFoo->showValue();

  return 0;
}
