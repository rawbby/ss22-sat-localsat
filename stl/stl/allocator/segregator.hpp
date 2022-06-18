#ifndef STL_SEGREGATOR_HPP
#define STL_SEGREGATOR_HPP

#include "allocator.hpp"

namespace stl {

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
struct segregator_type
  : small_allocator_type
  , large_allocator_type
{
  static_assert(threshold > Size(0), "Threshold lower one is not allowed for Segregator!");
  static_assert(allocator_concept<small_allocator_type>, "Invalid small Allocator passed to Segregator!");
  static_assert(allocator_concept<large_allocator_type>, "Invalid large Allocator passed to Segregator!");

  MI segregator_type() noexcept = default;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  MI void Free(memory_type<type_type> memory) noexcept;

  template<typename type_type = byte_type>
  MNI memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  MNI bool_type Owns(memory_type<type_type> memory) const;

private:

  template<typename type_type = byte_type>
  MNCI bool_type UseSmall(size_type count) const noexcept;

  template<typename type_type = byte_type>
  MNCI bool_type UseLarge(size_type count) const noexcept;
};

}

// include implementation
#include "segregator.inl"

#endif
