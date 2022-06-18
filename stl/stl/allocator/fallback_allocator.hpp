#ifndef STL_FALLBACK_ALLOCATOR_HPP
#define STL_FALLBACK_ALLOCATOR_HPP

#include "../def.hpp"
#include "alignment.hpp"
#include "allocator.hpp"
#include "memory.hpp"

namespace stl {

template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> && allocator_concept<secondary_allocator_type>
struct fallback_allocator_type
  : primary_allocator_type
  , secondary_allocator_type
{
  [[maybe_unused]] inline fallback_allocator_type() noexcept = default;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] inline void Free(memory_type<type_type> memory) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline bool Owns(memory_type<type_type> memory) const;
};

template<typename primary_allocator_type, typename secondary_allocator_type>
  requires owning_allocator_concept<primary_allocator_type> &&
           allocator_concept<secondary_allocator_type> [
           [maybe_unused]] constexpr inline fallback_allocator_type<primary_allocator_type, secondary_allocator_type>
  FallbackAllocator();

}

// include implementation
#include "fallback_allocator.inl"

#endif
