#ifndef STL_VIEW_HPP
#define STL_VIEW_HPP

#include "stl.hpp"

namespace stl {

template<typename type_type>
struct view_type
{
  type_type* data;
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

  // utilities
  MNCI view_type<const type_type> Range(size_type lower, size_type upper) const noexcept;
  MNCI view_type<type_type> Range(size_type lower, size_type upper) noexcept;
  MNCI view_type<const type_type> Range(size_type upper) const noexcept;
  MNCI view_type<type_type> Range(size_type upper) noexcept;
  [[maybe_unused]] constexpr inline void MemSet(i32_type value) noexcept;
  [[maybe_unused]] constexpr inline void MemCopy(view_type<type_type> dst) const noexcept;
};

/*
 * view concepts
 */

template<typename view_convertible_type, typename type_type>
concept view_convertible_concept = (
  // clang-format off
  requires(view_convertible_type view_convertible) {
    { view_convertible.View() } -> std::same_as<view_type<type_type>>;
  } &&
  requires(const view_convertible_type view_convertible) {
    { view_convertible.View() } -> std::same_as<view_type<const type_type>>;
  }
  // clang-format on
);

template<typename viewable_type, typename type_type>
concept viewable_concept = (
  // clang-format off
  requires(viewable_type viewable) {
    { viewable.At(Size(0)) } -> std::same_as<type_type*>;
    { viewable[Size(0)] } -> std::same_as<type_type&>;
  } &&
  requires(const viewable_type viewable) {
    { viewable.Count() } -> std::same_as<size_type>;
    { viewable.At(Size(0)) } -> std::same_as<const type_type*>;
    { viewable[Size(0)] } -> std::same_as<const type_type&>;
  }
  // clang-format on
);

/*
 * basic factories
 */

template<typename type_type>
MNCI view_type<const type_type>
View(const type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
MNCI view_type<type_type>
View(type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
MNCI view_type<const type_type>
View(const type_type* data, size_type upper) noexcept;

template<typename type_type>
MNCI view_type<type_type>
View(type_type* data, size_type upper) noexcept;

}

// include implementation
#include "view.inl"

#endif
