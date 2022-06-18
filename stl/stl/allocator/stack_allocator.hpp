#ifndef STL_STACK_ALLOCATOR_HPP
#define STL_STACK_ALLOCATOR_HPP

#include "allocator.hpp"
#include "../static_array.hpp"

namespace stl {

template<size_type capacity, typename alignment_tag = alignment_no_tag>
struct stack_allocator_type
{
  // As this struct is not aligned we need to extend the boundaries
  // of the struct to guarantee that capacity is usable!
  MCI static auto extended_capacity = capacity + alignment_tag::lo_mask;

  stl::static_array_type<byte_type, extended_capacity> data;
  byte_type* top;

  MCI stack_allocator_type() noexcept;

  template<typename type_type = byte_type>
  MNCI memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  MCI void Free(memory_type<type_type> memory) noexcept;

  MCI void FreeAll() noexcept;

  template<typename type_type = byte_type>
  MNCI memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  MNCI bool_type Owns(memory_type<type_type> memory) const noexcept;
};

}

// include implementation
#include "stack_allocator.inl"

#endif
