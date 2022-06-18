#ifndef STL_MEMORY_HPP
#define STL_MEMORY_HPP

#include "../def.hpp"

namespace stl {

template<typename type_type = byte_type>
struct memory_type
{
  type_type* data;
  size_type count;
};

template<typename type_type = byte_type>
[[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type>
Memory(type_type* data, size_type count) noexcept
{
  return { data, count };
}

}

#endif
