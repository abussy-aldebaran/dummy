#include "dummy.hpp"

namespace
{
  template <typename T>
  void print()
  {
    std::cout << "first print: ";
    dummy::bar<T>().print();
    std::cout << "second print: ";
    dummy::bar<T>().print();
  }

}

int main()
{
  print<double>();
  print<float>();
  print<int>();

  return 0;
}
