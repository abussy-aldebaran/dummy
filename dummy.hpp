#pragma once

#include <iostream>
#include <typeinfo>

namespace dummy
{
  int foo();

  template <typename T>
  struct bar
  {
    void print() const
    {
      std::cout << "template type: " << typeid(T).name() << std::endl;
      std::cout << "print: " << reinterpret_cast<void*>(&bar::print) << std::endl;
    }
  };

  extern template struct bar<double>;
  extern template struct bar<float>;

} // namespace dummy
