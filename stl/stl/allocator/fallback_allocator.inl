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
  if (P::Owns(memory))
    return P::template ReAllocate<T>(memory, count);
  else
    return S::template ReAllocate<T>(memory, count);
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
