#ifndef STL_SYS_HPP
#define STL_SYS_HPP

#include <cstdio>  // std::fputs, stdout
#include <cstdlib> // std::exit

#include "def.hpp"

namespace stl {

[[maybe_unused]] inline void
Exit(i32_type code) noexcept
{
  std::exit(code);
}

template<typename type_type>
[[maybe_unused]] inline void Put(type_type) noexcept;

template<typename type_type>
[[maybe_unused]] inline void
Put(const type_type*) noexcept;

template<>
[[maybe_unused]] inline void
Put(const char* str) noexcept
{
  std::fputs(str, stdout);
}

}

#endif
