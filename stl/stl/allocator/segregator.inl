#ifndef STL_SEGREGATOR_INL
#define STL_SEGREGATOR_INL

#include "allocator.hpp"
#include "segregator.hpp"

namespace stl {

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline memory_type<type_type>
segregator_type<threshold, small_allocator_type, large_allocator_type>::Allocate(size_type count) noexcept
{
  if (count < threshold)
    return small_allocator_type::Allocate(count);
  else
    return large_allocator_type::Allocate(count);
}

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
template<typename type_type>
[[maybe_unused]] inline void
segregator_type<threshold, small_allocator_type, large_allocator_type>::Free(memory_type<type_type> memory) noexcept
{
  if (memory.count < threshold)
    return small_allocator_type::Free(memory);
  else
    return large_allocator_type::Free(memory);
}

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline memory_type<type_type>
segregator_type<threshold, small_allocator_type, large_allocator_type>::ReAllocate(memory_type<type_type> memory, size_type count) noexcept
{
  if (memory.count < threshold && count < threshold)
    return small_allocator_type::ReAllocate(memory, count);

  if (memory.count >= threshold && count >= threshold)
    return large_allocator_type::ReAllocate(memory, count);

  if (memory.count >= threshold && count < threshold) {
    auto new_memory = small_allocator_type::Allocate(count);
    memcpy(new_memory.data, memory.data, count);
    return new_memory;
  }

  auto new_memory = large_allocator_type::Allocate(count);
  memcpy(new_memory.data, memory.data, memory.count);
  return new_memory;
}

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline bool
segregator_type<threshold, small_allocator_type, large_allocator_type>::Owns(memory_type<type_type> memory) const
{
  if (memory.count < threshold)
    return small_allocator_type::Owns(memory);
  else
    return large_allocator_type::Owns(memory);
}

}

#endif
