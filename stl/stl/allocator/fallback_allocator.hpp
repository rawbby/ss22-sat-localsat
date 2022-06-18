#ifndef STL_FALLBACK_ALLOCATOR_HPP
#define STL_FALLBACK_ALLOCATOR_HPP

#include "allocator.hpp"

namespace stl {

template<typename primary_allocator_type, typename secondary_allocator_type>
struct fallback_allocator_type
  : primary_allocator_type
  , secondary_allocator_type
{
  static_assert(owning_allocator_concept<primary_allocator_type>, "Invalid small Allocator passed to Fallback Allocator!");
  static_assert(allocator_concept<secondary_allocator_type>, "Invalid large Allocator passed to Fallback Allocator!");

  MI fallback_allocator_type() noexcept = default;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  MI void Free(memory_type<type_type> memory) noexcept;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  MNI bool_type Owns(memory_type<type_type> memory) const;
};

}

// include implementation
#include "fallback_allocator.inl"

#endif
