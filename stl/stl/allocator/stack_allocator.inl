#ifndef STL_STACK_ALLOCATOR_INL
#define STL_STACK_ALLOCATOR_INL

#include "../util.hpp"
#include "stack_allocator.hpp"

namespace stl {

template<size_type capacity, typename alignment_tag>
MNCI
stack_allocator_type<capacity, alignment_tag>::stack_allocator_type() noexcept
  : data()
{
  top = data.begin();
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
MNCI memory_type<type_type>
stack_allocator_type<capacity, alignment_tag>::Allocate(size_type count) noexcept
{
  top = alignment_tag::align(top);
  if (&(top[count * sizeof(type_type)]) > data.end())
    return {};

  auto memory = memory_type<type_type>((type_type*)top, count);
  top = &(top[count * sizeof(type_type)]);

  return memory;
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
MCI void
stack_allocator_type<capacity, alignment_tag>::Free(memory_type<type_type> memory) noexcept
{
  // sanitize
  [[maybe_unused]] const auto top_ = (void*)alignment_tag::align(top);
  [[maybe_unused]] const auto end_ = (void*)alignment_tag::align(&(memory.data[memory.count]));
  Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only free Memory on Top of the Stack!");

  top = (byte_type*)&(memory.data[0]);
}

template<size_type capacity, typename alignment_tag>
MCI void
stack_allocator_type<capacity, alignment_tag>::FreeAll() noexcept
{
  top = &(data[0]);
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
MNCI memory_type<type_type>
stack_allocator_type<capacity, alignment_tag>::ReAllocate(memory_type<type_type> memory, size_type count) noexcept
{
  // sanitize
  [[maybe_unused]] const auto top_ = (void*)alignment_tag::align(top);
  [[maybe_unused]] const auto end_ = (void*)alignment_tag::align(&(memory.data[memory.count * sizeof(type_type)]));
  Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only reallocate Memory on Top of the Stack!");

  if ((void*)&(memory.data[count * sizeof(type_type)]) > (void*)data.end())
    return {};

  memory.count = count;
  top = (byte_type*) &(memory.data[count * sizeof(type_type)]);
  return memory;
}

template<size_type capacity, typename alignment_tag>
template<typename type_type>
MNCI bool_type
stack_allocator_type<capacity, alignment_tag>::Owns(memory_type<type_type> memory) const noexcept
{
  return (data.begin() <= (byte_type*)memory.data && (byte_type*)memory.data < data.end());
}

}

#endif
