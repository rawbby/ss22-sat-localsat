#ifndef STL_STATIC_VECTOR_HPP
#define STL_STATIC_VECTOR_HPP

#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type, size_type capacity>
struct static_vector_type
{
  type_type data[capacity];
  size_type count;

  // satisfy the viewable concept
  MNCI size_type Count() const noexcept;
  MNCI const type_type* At(size_type index) const noexcept;
  MNCI type_type* At(size_type index) noexcept;
  MNCI const type_type& operator[](size_type index) const noexcept;
  MNCI type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  MNCI const type_type* begin() const noexcept;
  MNCI const type_type* end() const noexcept;
  MNCI type_type* begin() noexcept;
  MNCI type_type* end() noexcept;

  // satisfy the view convertible concept
  MNCI view_type<const type_type> View() const noexcept;
  MNCI view_type<type_type> View() noexcept;

  // utilities
  MNCI size_type Capacity() const noexcept;
  [[maybe_unused]] constexpr inline void Capacity(size_type new_count) noexcept;
  [[maybe_unused]] constexpr inline void Count(size_type new_count) noexcept;
  [[maybe_unused]] constexpr inline void Push(type_type type) noexcept;
  [[maybe_unused]] constexpr inline void Pop() noexcept;
  MNCI const type_type* Peak() const noexcept;
  MNCI type_type* Peak() noexcept;
  [[maybe_unused]] constexpr inline void Remove(size_type index) noexcept;
};

/*
 * factories
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
StaticVector(static_vector_type<type_type, capacity>* vector) noexcept;

template<typename type_type, size_type capacity>
MNCI static_vector_type<type_type, capacity>
StaticVector() noexcept;

}

// include implementation
#include "static_vector.inl"

#endif
