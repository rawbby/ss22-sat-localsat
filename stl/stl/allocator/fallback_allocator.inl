#ifndef STL_FALLBACK_ALLOCATOR_INL
#define STL_FALLBACK_ALLOCATOR_INL

#include "fallback_allocator.hpp"

namespace stl {

template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> && allocator_concept<secondary_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline memory_type<type_type>
fallback_allocator_type<primary_allocator_type, secondary_allocator_type>::Allocate(size_type count) noexcept
{
  auto memory = primary_allocator_type::template Allocate<type_type>(count);
  if (!memory.data)
    memory = secondary_allocator_type::template Allocate<type_type>(count);
  return memory;
}

template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> && allocator_concept<secondary_allocator_type>
template<typename type_type>
[[maybe_unused]] inline void
fallback_allocator_type<primary_allocator_type, secondary_allocator_type>::Free(memory_type<type_type> memory) noexcept
{
  if (primary_allocator_type::Owns(memory))
    primary_allocator_type::Free(memory);
  else
    secondary_allocator_type::Free(memory);
}
template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> && allocator_concept<secondary_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline memory_type<type_type>
fallback_allocator_type<primary_allocator_type, secondary_allocator_type>::ReAllocate(memory_type<type_type> memory, size_type count) noexcept
{
  if (primary_allocator_type::Owns(memory))
    return primary_allocator_type::template ReAllocate<type_type>(memory, count);
  else
    return secondary_allocator_type::template ReAllocate<type_type>(memory, count);
}
template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> && allocator_concept<secondary_allocator_type>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] inline bool
fallback_allocator_type<primary_allocator_type, secondary_allocator_type>::Owns(memory_type<type_type> memory) const
{
  return primary_allocator_type::Owns(memory) || secondary_allocator_type::Owns(memory);
}

template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> &&
           allocator_concept<secondary_allocator_type> [
           [maybe_unused]] constexpr inline fallback_allocator_type<primary_allocator_type, secondary_allocator_type>
  FallbackAllocator()
{
  return {};
}

}

#endif
