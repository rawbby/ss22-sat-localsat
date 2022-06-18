#ifndef STL_MEMORY_HPP
#define STL_MEMORY_HPP

#include "../def.hpp"

namespace stl {

template<typename type_type = byte_type>
struct memory_type
{
  type_type* data;
  size_type count;

  memory_type(type_type* data, size_type count)
    : data(data)
    , count(count)
  {
  }

  memory_type()
    : data(nullptr)
    , count(0)
  {
  }
};

}

#endif
