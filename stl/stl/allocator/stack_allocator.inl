#ifndef STL_STACK_ALLOCATOR_INL
#define STL_STACK_ALLOCATOR_INL

#include "stack_allocator.hpp"

namespace stl {

template<size_type capacity, typename alignment_tag>
[[maybe_unused]] [[nodiscard]] constexpr inline stack_allocator_type<capacity, alignment_tag>::stack_allocator_type() noexcept
  : data()
  , top(&(data[0]))
{
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type>
stack_allocator_type<capacity, alignment_tag>::Allocate(size_type count) noexcept
{
  top = alignment_tag::align(top);
  if (&(top[count * sizeof(type_type)]) > &(data[extended_capacity]))
    return {};

  auto memory = Memory((type_type*)top, count * sizeof(type_type));
  top = &(top[count * sizeof(type_type)]);

  return memory;
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
[[maybe_unused]] constexpr inline void
stack_allocator_type<capacity, alignment_tag>::Free(memory_type<type_type> memory) noexcept
{
  // sanitize
  [[maybe_unused]] const auto top_ = alignment_tag::align(top);
  [[maybe_unused]] const auto end_ = alignment_tag::align(&(memory.data[memory.count * sizeof(type_type)]));
  Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only free Memory on Top of the Stack!");

  top = &(memory.data[0]);
}

template<size_type capacity, typename alignment_tag>
[[maybe_unused]] constexpr inline void
stack_allocator_type<capacity, alignment_tag>::FreeAll() noexcept
{
  top = &(data[0]);
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline memory_type<type_type>
stack_allocator_type<capacity, alignment_tag>::ReAllocate(memory_type<type_type> memory, size_type count) noexcept
{
  // sanitize
  [[maybe_unused]] const auto top_ = alignment_tag::align(top);
  [[maybe_unused]] const auto end_ = alignment_tag::align(&(memory.data[memory.count * sizeof(type_type)]));
  Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only reallocate Memory on Top of the Stack!");

  if (&(memory.data[count * sizeof(type_type)]) > &(data[extended_capacity]))
    return {};

  memory.count = count;
  top = &(memory.data[count * sizeof(type_type)]);
  return memory;
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
stack_allocator_type<capacity, alignment_tag>::Owns(memory_type<type_type> memory) const noexcept
{
  return (&(data[0]) <= memory.data) && (memory.data < &(data[extended_capacity]));
}

template<size_type capacity, typename alignment_tag>
[[maybe_unused]] [[nodiscard]] constexpr inline stack_allocator_type<capacity, alignment_tag>
StackAllocator()
{
  return {};
}

}

#endif
