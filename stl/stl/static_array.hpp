#ifndef STL_ARRAY_HPP
#define STL_ARRAY_HPP

#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type, size_type capacity>
struct static_array_type
{
  type_type data[capacity];

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
};

// factories
template<typename type_type, size_type capacity>
MNCI static_array_type<type_type, capacity>
StaticArray() noexcept;

}

// include implementation
#include "static_array.inl"

#endif
