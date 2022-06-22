#ifndef STL_HEAP_ALLOCATOR_HPP
#define STL_HEAP_ALLOCATOR_HPP

#include "allocator.hpp"

namespace stl {

template<typename alignment_tag = alignment_no_tag>
struct heap_allocator_type
{
  MCI heap_allocator_type() noexcept = default;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> Allocate(size_type count) const noexcept;

  template<typename type_type = byte_type>
  MI void Free(memory_type<type_type> memory) const noexcept;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) const noexcept;
};

namespace detail {

auto global_heap_allocator = heap_allocator_type<>();

}

}

// include implementation
#include "heap_allocator.inl"

#endif
