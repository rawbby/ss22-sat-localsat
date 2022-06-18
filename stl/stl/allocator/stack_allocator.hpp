#ifndef STL_STACK_ALLOCATOR_HPP
#define STL_STACK_ALLOCATOR_HPP

#include "../def.hpp"
#include "../util.hpp"
#include "alignment.hpp"
#include "memory.hpp"

namespace stl {

template<size_type capacity, typename alignment_tag = alignment_no_tag>
struct stack_allocator_type
{
  // As this struct is not aligned we need to extend the boundaries
  // of the struct to guarantee that capacity is usable!
  static constexpr auto extended_capacity = capacity + alignment_tag::lo_mask;

  byte_type data[extended_capacity];
  byte_type* top;

  [[maybe_unused]] constexpr inline stack_allocator_type() noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] constexpr inline void Free(memory_type<type_type> memory) noexcept;

  [[maybe_unused]] constexpr inline void FreeAll() noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] constexpr inline bool Owns(memory_type<type_type> memory) const noexcept;
};

template<size_type capacity, typename alignment_tag = alignment_no_tag>
[[maybe_unused]] constexpr inline stack_allocator_type<capacity, alignment_tag>
StackAllocator();

}

// include implementation
#include "stack_allocator.inl"

#endif
