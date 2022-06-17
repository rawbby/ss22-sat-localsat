#ifndef STL_DYNAMIC_VECTOR_HPP
#define STL_DYNAMIC_VECTOR_HPP

#include "allocator/alignment.hpp"
#include "allocator/allocator.hpp"
#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
struct dynamic_vector_type
{
  allocator_type* allocator;
  memory_type data;
  size_type count;

  inline ~dynamic_vector_type() noexcept { allocator->Free(data); }

  // satisfy the viewable concept
  [[maybe_unused]] [[nodiscard]] inline size_type Count() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type* At(size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type* At(size_type index) noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type& operator[](size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] inline type_type* begin() noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type* end() noexcept;

  // satisfy the view convertible concept
  [[maybe_unused]] [[nodiscard]] inline view_type<const type_type> View() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline view_type<type_type> View() noexcept;

  // utilities
  [[maybe_unused]] inline void Count(size_type new_count) noexcept;
  [[maybe_unused]] inline void Push(type_type type) noexcept;
  [[maybe_unused]] inline void Pop() noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type* Peak() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type* Peak() noexcept;
  [[maybe_unused]] inline void Remove(size_type index) noexcept;
};

// factories
template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] [[nodiscard]] inline dynamic_vector_type<type_type, allocator_type>
DynamicVector(allocator_type* allocator) noexcept;

}

// include implementation
#include "dynamic_vector.inl"

#endif
