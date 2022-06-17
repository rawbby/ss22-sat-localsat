#ifndef STL_SEGREGATOR_HPP
#define STL_SEGREGATOR_HPP

#include "../def.hpp"

namespace stl {

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
struct segregator_type
  : small_allocator_type
  , large_allocator_type
{
  [[maybe_unused]] inline segregator_type() noexcept
    : small_allocator_type()
    , large_allocator_type()
  {
  }

  [[maybe_unused]] [[nodiscard]] inline memory_type Allocate(size_type count) noexcept
  {
    if (count < threshold)
      return small_allocator_type::Allocate(count);
    else
      return large_allocator_type::Allocate(count);
  }

  [[maybe_unused]] inline void Free(memory_type memory) noexcept
  {
    if (memory.count < threshold)
      return small_allocator_type::Free(memory);
    else
      return large_allocator_type::Free(memory);
  }

  [[maybe_unused]] [[nodiscard]] inline memory_type ReAllocate(memory_type memory, size_type count) noexcept
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

  [[maybe_unused]] [[nodiscard]] inline bool Owns(memory_type memory) const
  {
    if (memory.count < threshold)
      return small_allocator_type::Owns(memory);
    else
      return large_allocator_type::Owns(memory);
  }
};

}

#endif
