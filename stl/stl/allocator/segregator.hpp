#ifndef STL_SEGREGATOR_HPP
#define STL_SEGREGATOR_HPP

#include "../def.hpp"

namespace stl {

template<size_type threshold, typename small_allocator_type, typename large_allocator_type>
  requires allocator_concept<small_allocator_type> && allocator_concept<large_allocator_type>
struct segregator_type
  : small_allocator_type
  , large_allocator_type
{
  [[maybe_unused]] inline segregator_type() noexcept = default;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline memory_type<type_type> Allocate(size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] inline void Free(memory_type<type_type> memory) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline memory_type<type_type> ReAllocate(memory_type<type_type> memory, size_type count) noexcept;

  template<typename type_type = byte_type>
  [[maybe_unused]] [[nodiscard]] inline bool Owns(memory_type<type_type> memory) const;
};

}

// include implementation
#include "segregator.inl"

#endif
