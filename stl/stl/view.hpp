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
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> Range(size_type lower, size_type upper) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> Range(size_type lower, size_type upper) noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> Range(size_type upper) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> Range(size_type upper) noexcept;
  [[maybe_unused]] constexpr inline void MemSet(i32_type value) noexcept;
  [[maybe_unused]] constexpr inline void MemCopy(view_type<type_type> dst) const noexcept;
};

/*
 * view concepts
 */

// clang-format off
template<typename view_convertible_type, typename type_type>
concept view_convertible_concept =
                            requires(view_convertible_type view_convertible) {
                              { view_convertible.View() } -> std::same_as<view_type<type_type>>;
                            } &&
                            requires(const view_convertible_type view_convertible) {
                              { view_convertible.View() } -> std::same_as<view_type<const type_type>>;
                            };
template<typename viewable_type, typename type_type>
concept viewable_concept = view_convertible_concept<viewable_type, type_type> &&
                            requires(viewable_type viewable) {
                              { viewable.At(Size(0)) } -> std::same_as<type_type*>;
                              { viewable[Size(0)] } -> std::same_as<type_type&>;
                            } &&
                            requires(const viewable_type viewable) {
                              { viewable.Count() } -> std::same_as<size_type>;
                              { viewable.At(Size(0)) } -> std::same_as<const type_type*>;
                              { viewable[Size(0)] } -> std::same_as<const type_type&>;
                            };
// clang-format on

/*
 * basic factories
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type upper) noexcept;

}

// include implementation
#include "view.inl"

#endif
