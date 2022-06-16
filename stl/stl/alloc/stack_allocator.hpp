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

  // TODO replace raw array with stl array
  byte_type data[extended_capacity];
  byte_type* top;

  [[maybe_unused]] inline stack_allocator_type() noexcept
    : data()
    , top(&(data[0]))
  {
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type Allocate(size_type count) noexcept
  {
    top = alignment_tag::align(top);
    if (&(top[count]) > &(data[extended_capacity]))
      return {};

    auto memory = Memory(top, count);
    top = &(top[count]);

    return memory;
  }

  [[maybe_unused]] constexpr inline void Free(memory_type memory) noexcept
  {
    // sanitize
    [[maybe_unused]] const auto top_ = alignment_tag::align(top);
    [[maybe_unused]] const auto end_ = alignment_tag::align(&(memory.data[memory.count]));
    Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only free Memory on Top of the Stack!");

    top = &(memory.data[0]);
  }

  constexpr inline void FreeAll() noexcept { top = &(data[0]); }

  [[maybe_unused]] [[nodiscard]] constexpr inline memory_type ReAllocate(memory_type memory, size_type count) noexcept
  {
    // sanitize
    [[maybe_unused]] const auto top_ = alignment_tag::align(top);
    [[maybe_unused]] const auto end_ = alignment_tag::align(&(memory.data[memory.count]));
    Assert(top_ == end_, "Runtime Error: Invalid usage of StackAllocator. Can only reallocate Memory on Top of the Stack!");

    if (&(memory.data[count]) > &(data[extended_capacity]))
      return {};

    memory.count = count;
    top = &(memory.data[count]);
    return memory;
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline bool Owns(memory_type memory) const noexcept
  {
    return (&(data[0]) <= memory.data) && (memory.data < &(data[extended_capacity]));
  }
};

template<size_type capacity, typename alignment_tag_ = alignment_no_tag>
[[maybe_unused]] constexpr inline stack_allocator_type<capacity, alignment_tag_>
StackAllocator()
{
  return {};
}

}

#endif
