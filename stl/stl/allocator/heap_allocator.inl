#ifndef SRL_HEAP_ALLOCATOR_INL
#define SRL_HEAP_ALLOCATOR_INL

#include "heap_allocator.hpp"

namespace stl {

template<typename alignment_tag>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type>
heap_allocator_type<alignment_tag>::Allocate(size_type count) const noexcept
{
  type_type* data;
#ifdef WIN32
  data = (type_type*)_aligned_malloc(count * sizeof(type_type), alignment_tag::alignment);
#else
  data = (type_type*)std::aligned_alloc(alignment_tag::alignment, count * sizeof(type_type));
#endif

  if (!data)
    return {};

  return { data, count };
}

template<typename alignment_tag>
template<typename type_type>
[[maybe_unused]] constexpr inline void
heap_allocator_type<alignment_tag>::Free(memory_type<type_type> memory) const noexcept
{
#ifdef WIN32
  _aligned_free(memory.data);
#else
  std::free(memory.data);
#endif
}

template<typename alignment_tag>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type>
heap_allocator_type<alignment_tag>::ReAllocate(memory_type<type_type> memory, size_type count) const noexcept
{
  byte_type* data;
#ifdef WIN32
  data = static_cast<type_type*>(_aligned_realloc(memory.data, count * sizeof(type_type), alignment_tag::alignment));
#else
  // TODO no guarentee that the memory is still aligned?
  data = static_cast<type_type*>(std::realloc(memory.data, count * sizeof(type_type)));
#endif

  if (!data)
    return {};

  return { data, count };
}

template<typename alignment_tag>
[[maybe_unused]] constexpr inline heap_allocator_type<alignment_tag>
HeapAllocator()
{
  return {};
}

}

#endif
