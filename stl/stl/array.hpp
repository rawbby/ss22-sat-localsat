#ifndef STL_ARRAY_HPP
#define STL_ARRAY_HPP

#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type, size_type capacity>
struct array_type
{
  type_type data[capacity];

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
};

// factories
template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline array_type<type_type, capacity>
Array() noexcept;

}

// include implementation
#include "array.inl"

#endif
