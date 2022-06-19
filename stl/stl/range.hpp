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

  MNCI range_iter_type(const range_iter_type& iter) noexcept = default;
  MNCI explicit range_iter_type(integral_type i) noexcept
    : i(i)
  {
  }

  // satisfy the iterator concept
  MNCI integral_type operator*() const noexcept;
  [[maybe_unused]] constexpr inline range_iter_type& operator++() noexcept;
  [[maybe_unused]] constexpr inline range_iter_type operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  MNCI bool operator==(const range_iter_type& other) const noexcept;
  MNCI bool operator!=(const range_iter_type& other) const noexcept;
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
  MNCI range_iter_type<integral_type> begin() const noexcept;
  MNCI range_iter_type<integral_type> end() const noexcept;
};

// factories
template<typename integral_type>
MNCI range_type<integral_type>
Range(integral_type lower, integral_type upper) noexcept;

}

// include implementation
#include "range.inl"

#endif
