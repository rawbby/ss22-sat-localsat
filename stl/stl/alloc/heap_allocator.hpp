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

  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type Allocate(size_type count) const noexcept
  {
    byte_type* data;
#ifdef WIN32
    data = static_cast<byte_type*>(_aligned_malloc(count, alignment_tag::alignment));
#else
    data = static_cast<byte_type*>(std::aligned_alloc(alignment_tag::alignment, count));
#endif

    if (!data)
      return {};

    return { data, count };
  }

  [[maybe_unused]] constexpr inline void Free(memory_type memory) const noexcept
  {
#ifdef WIN32
    _aligned_free(memory.data);
#else
    std::free(memory.data);
#endif
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type ReAllocate(memory_type memory, size_type count) const noexcept
  {
    byte_type* data;
#ifdef WIN32
    data = static_cast<byte_type*>(_aligned_realloc(memory.data, count, alignment_tag::alignment));
#else
    // TODO no guarentee that the memory is still aligned?
    data = static_cast<byte_type*>(std::realloc(memory.data, count));
#endif

    if (!data)
      return {};

    return { data, count };
  }
};

template<typename alignment_tag_ = alignment_no_tag>
[[maybe_unused]] constexpr inline heap_allocator_type<alignment_tag_>
HeapAllocator()
{
  return {};
}

}

#endif
