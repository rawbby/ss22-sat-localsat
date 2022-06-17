#ifndef STL_RANGE_INL
#define STL_RANGE_INL

#include "range.hpp"

namespace stl {

/*
 * satisfy the iterator concept
 */

[[maybe_unused]] [[nodiscard]] constexpr inline size_type
range_iter_type::operator*() const noexcept
{
  return i;
}

[[maybe_unused]] constexpr inline range_iter_type&
range_iter_type::operator++() noexcept
{
  i++;
  return *this;
}

[[maybe_unused]] constexpr inline range_iter_type // NOLINT(cert-dcl21-cpp)
range_iter_type::operator++(int) noexcept
{
  return range_iter_type(i++);
}

[[maybe_unused]] [[nodiscard]] constexpr inline bool
range_iter_type::operator==(const range_iter_type& other) const noexcept
{
  return i == other.i;
}

[[maybe_unused]] [[nodiscard]] constexpr inline bool
range_iter_type::operator!=(const range_iter_type& other) const noexcept
{
  return i != other.i;
}

/*
 * satisfy the iterable concept
 */

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type
range_type::begin() const noexcept
{
  return range_iter_type(lower);
}

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type
range_type::end() const noexcept
{
  return range_iter_type(upper);
}

/*
 * factories
 */

[[maybe_unused]] [[nodiscard]] constexpr inline range_type
Range(size_type lower, size_type upper) noexcept
{
  Assert(lower <= upper, "Invalid Parameter for Range! lower > upper.");
  return { lower, upper };
}

}

#endif
