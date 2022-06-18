#ifndef STL_HEAP_ALLOCATOR_HPP
#define STL_HEAP_ALLOCATOR_HPP

#include "../def.hpp"
#include "alignment.hpp"
#include "memory.hpp"

#ifdef WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

namespace stl {

template<typename alignment_tag = alignment_no_tag>
struct heap_allocator_type
{
  constexpr inline heap_allocator_type() noexcept = default;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type> Allocate(size_type count) const noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] constexpr inline void Free(memory_type<type_type> memory) const noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type> ReAllocate(memory_type<type_type> memory,
                                                                                    size_type count) const noexcept;
};

template<typename alignment_tag = alignment_no_tag>
[[maybe_unused]] constexpr inline heap_allocator_type<alignment_tag>
HeapAllocator();

}

// include implementation
#include "heap_allocator.inl"

#endif
