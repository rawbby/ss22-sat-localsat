#ifndef STL_RANGE_HPP
#define STL_RANGE_HPP

#include <limits>

#include "static_vector.hpp"
#include "stl.hpp"

namespace stl {

/*
 * range iterator declaration
 */

struct range_iter_type
{
  size_type i;

  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type(const range_iter_type& iter) noexcept = default;
  [[maybe_unused]] [[nodiscard]] constexpr inline explicit range_iter_type(size_type i) noexcept
    : i(i)
  {
  }

  // satisfy the iterator concept
  [[maybe_unused]] [[nodiscard]] constexpr inline size_type operator*() const noexcept;
  [[maybe_unused]] constexpr inline range_iter_type& operator++() noexcept;
  [[maybe_unused]] constexpr inline range_iter_type operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const range_iter_type& other) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const range_iter_type& other) const noexcept;
};

/*
 * range declaration
 */

struct range_type
{
  size_type lower;
  size_type upper;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type begin() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type end() const noexcept;
};

// factories
[[maybe_unused]] [[nodiscard]] constexpr inline range_type
Range(size_type lower, size_type upper) noexcept;

}

// include implementation
#include "range.inl"

#endif
