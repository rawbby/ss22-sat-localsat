#ifndef STL_RANGE_HPP
#define STL_RANGE_HPP

#include <limits>

#include "static_vector.hpp"
#include "stl.hpp"

namespace stl {

/*
 * range iterator declaration
 */

template<typename integral_type>
struct range_iter_type
{
  integral_type i;

  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type(const range_iter_type& iter) noexcept = default;
  [[maybe_unused]] [[nodiscard]] constexpr inline explicit range_iter_type(integral_type i) noexcept
    : i(i)
  {
  }

  // satisfy the iterator concept
  [[maybe_unused]] [[nodiscard]] constexpr inline integral_type operator*() const noexcept;
  [[maybe_unused]] constexpr inline range_iter_type& operator++() noexcept;
  [[maybe_unused]] constexpr inline range_iter_type operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const range_iter_type& other) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const range_iter_type& other) const noexcept;
};

/*
 * range declaration
 */

template<typename integral_type>
struct range_type
{
  integral_type lower;
  integral_type upper;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type<integral_type> begin() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type<integral_type> end() const noexcept;
};

// factories
template<typename integral_type>
[[maybe_unused]] [[nodiscard]] constexpr inline range_type<integral_type>
Range(integral_type lower, integral_type upper) noexcept;

}

// include implementation
#include "range.inl"

#endif
