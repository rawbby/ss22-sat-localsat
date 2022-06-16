#ifndef STL_FALLBACK_ALLOCATOR_HPP
#define STL_FALLBACK_ALLOCATOR_HPP

#include "../def.hpp"
#include "alignment.hpp"
#include "memory.hpp"

namespace stl {

template<typename primary_allocator_type, typename secondary_allocator_type>
struct fallback_allocator_type
  : primary_allocator_type
  , secondary_allocator_type
{
  [[maybe_unused]] inline fallback_allocator_type() noexcept
    : primary_allocator_type()
    , secondary_allocator_type()
  {
  }

  [[maybe_unused]] [[nodiscard]] inline memory_type Allocate(size_type count) noexcept
  {
    auto memory = primary_allocator_type::Allocate(count);
    if (!memory.data)
      memory = secondary_allocator_type::Allocate(count);
    return memory;
  }

  [[maybe_unused]] inline void Free(memory_type memory) noexcept
  {
    if (primary_allocator_type::Owns(memory))
      primary_allocator_type::Free(memory);
    else
      secondary_allocator_type::Free(memory);
  }

  [[maybe_unused]] [[nodiscard]] inline memory_type ReAllocate(memory_type memory, size_type count) noexcept
  {
    if (primary_allocator_type::Owns(memory))
      return primary_allocator_type::ReAllocate(memory, count);
    else
      return secondary_allocator_type::ReAllocate(memory, count);
  }

  [[maybe_unused]] [[nodiscard]] inline bool Owns(memory_type memory) const
  {
    return primary_allocator_type::Owns(memory) || secondary_allocator_type::Owns(memory);
  }
};

template<typename primary_allocator_type, typename secondary_allocator_type>
[[maybe_unused]] constexpr inline fallback_allocator_type<primary_allocator_type, secondary_allocator_type>
FallbackAllocator()
{
  return {};
}

}

#endif
