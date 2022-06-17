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
  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Count() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* At(size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* At(size_type index) noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type& operator[](size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* begin() noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* end() noexcept;

  // satisfy the view convertible concept
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> View() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> View() noexcept;

  // utilities
  [[maybe_unused]] constexpr inline void Count(size_type new_count) noexcept;
  [[maybe_unused]] constexpr inline void Push(type_type type) noexcept;
  [[maybe_unused]] constexpr inline void Pop() noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* Peak() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* Peak() noexcept;
  [[maybe_unused]] constexpr inline void Remove(size_type index) noexcept;
};

/*
 * factories
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
StaticVector(static_vector_type<type_type, capacity>* vector) noexcept;

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline static_vector_type<type_type, capacity>
StaticVector() noexcept;

}

// include implementation
#include "static_vector.inl"

#endif
