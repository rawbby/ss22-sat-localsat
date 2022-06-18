#ifndef STL_SEGREGATOR_INL
#define STL_SEGREGATOR_INL

#include "allocator.hpp"
#include "segregator.hpp"

namespace stl {

template<size_type threshold, typename S, typename L>
template<typename T>
MNI memory_type<T>
segregator_type<threshold, S, L>::Allocate(size_type count) noexcept
{
  if (UseSmall<T>(count))
    return S::template Allocate<T>(count);
  else
    return L::template Allocate<T>(count);
}

template<size_type threshold, typename S, typename L>
template<typename T>
MI void
segregator_type<threshold, S, L>::Free(memory_type<T> memory) noexcept
{
  if (memory.count * sizeof(T) <= threshold)
    return S::template Free<T>(memory);
  else
    return L::template Free<T>(memory);
}

template<size_type threshold, typename S, typename L>
template<typename T>
MNI memory_type<T>
segregator_type<threshold, S, L>::ReAllocate(memory_type<T> memory, size_type count) noexcept
{
  // continue using small allocator
  if (UseSmall<T>(memory.count) && UseSmall<T>(count))
    return S::template ReAllocate<T>(memory, count);

  // continue using large allocator
  if (!UseSmall<T>(memory.count) && !UseSmall<T>(count))
    return L::template ReAllocate<T>(memory, count);

  // switch from small to large allocator
  if (UseSmall<T>(memory.count)) {

    auto new_memory = L::template Allocate<T>(count);
    if (new_memory.data) {
      memcpy(new_memory.data, memory.data, memory.count * sizeof(T));
      S::template Free<T>(memory);
      return new_memory;
    }

    return {};
  }

  // switch from large to small allocator
  auto new_memory = S::template Allocate<T>(count);
  if (new_memory.data) {
    memcpy(new_memory.data, memory.data, count * sizeof(T));
    L::template Free<T>(memory);
    return new_memory;
  }

  return {};
}

template<size_type threshold, typename S, typename L>
template<typename T>
MNI bool_type
segregator_type<threshold, S, L>::Owns(memory_type<T> memory) const
{
  if (memory.count * sizeof(T) <= threshold)
    return S::Owns(memory);
  else
    return L::Owns(memory);
}

template<size_type threshold, typename S, typename L>
template<typename T>
MNCI bool_type
segregator_type<threshold, S, L>::UseSmall(size_type count) const noexcept
{
  return count * sizeof(T) <= threshold;
}

template<size_type threshold, typename S, typename L>
template<typename T>
MNCI bool_type
segregator_type<threshold, S, L>::UseLarge(size_type count) const noexcept
{
  return count * sizeof(T) > threshold;
}

}

#endif
