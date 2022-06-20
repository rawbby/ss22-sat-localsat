#ifndef STL_FALLBACK_ALLOCATOR_INL
#define STL_FALLBACK_ALLOCATOR_INL

#include "fallback_allocator.hpp"

namespace stl {

template<typename P, typename S>
template<typename T>
MNI memory_type<T>
fallback_allocator_type<P, S>::Allocate(size_type count) noexcept
{
  auto memory = P::template Allocate<T>(count);
  if (!memory.data)
    memory = S::template Allocate<T>(count);
  return memory;
}

template<typename P, typename S>
template<typename T>
MI void
fallback_allocator_type<P, S>::Free(memory_type<T> memory) noexcept
{
  if (P::template Owns<T>(memory))
    P::template Free<T>(memory);
  else
    S::template Free<T>(memory);
}

template<typename P, typename S>
template<typename T>
MNI memory_type<T>
fallback_allocator_type<P, S>::ReAllocate(memory_type<T> memory, size_type count) noexcept
{
  if (P::Owns(memory)) {

    auto new_memory = P::template ReAllocate<T>(memory, count);
    if (new_memory.data)
      return new_memory;

    new_memory = S::template Allocate<T>(count);
    if (new_memory.data) {
      auto smaller_count = memory.count < count ? memory.count : count;
      memcpy(new_memory.data, memory.data, smaller_count * sizeof(T));
      P::template Free<T>(memory);
    }

    return new_memory;
  } else {
    return S::template ReAllocate<T>(memory, count);
  }
}

template<typename P, typename S>
template<typename T>
MNI bool_type
fallback_allocator_type<P, S>::Owns(memory_type<T> memory) const
{
  return P::Owns(memory) || S::Owns(memory);
}

}

#endif
