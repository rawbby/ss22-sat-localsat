#ifndef STL_MEMORY_HPP
#define STL_MEMORY_HPP

#include "../def.hpp"

namespace stl {

struct memory_type
{
  byte_type* data;
  size_type count;
};

[[maybe_unused]] constexpr inline memory_type
Memory(byte_type* data, size_type count) noexcept
{
  return { data, count };
}

}

#endif
