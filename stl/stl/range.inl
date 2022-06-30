#ifndef STL_RANGE_INL
#define STL_RANGE_INL

#include "range.hpp"

namespace stl {

/*
 * satisfy the iterator concept
 */

template<typename integral_type>
MNCI integral_type
range_iter_type<integral_type>::operator*() const noexcept
{
  return i;
}

template<typename integral_type>
[[maybe_unused]] constexpr inline range_iter_type<integral_type>&
range_iter_type<integral_type>::operator++() noexcept
{
  i++;
  return *this;
}

template<typename integral_type>
[[maybe_unused]] constexpr inline range_iter_type<integral_type> // NOLINT(cert-dcl21-cpp)
range_iter_type<integral_type>::operator++(int) noexcept
{
  return range_iter_type(i++);
}

template<typename integral_type>
MNCI bool
range_iter_type<integral_type>::operator==(const range_iter_type<integral_type>& other) const noexcept
{
  return i == other.i;
}

template<typename integral_type>
MNCI bool
range_iter_type<integral_type>::operator!=(const range_iter_type<integral_type>& other) const noexcept
{
  return i != other.i;
}

/*
 * utilities
 */

template<typename integral_type>
MNCI size_type
range_type<integral_type>::Count() const noexcept
{
  return upper - lower;
}

template<typename integral_type>
MNCI integral_type
range_type<integral_type>::operator[](size_type index) const noexcept
{
  Assert(index >= 0, "Index out of Bounds!");
  Assert(index < Count(), "Index out of Bounds!");
  return lower + index;
}

/*
 * satisfy the iterable concept
 */

template<typename integral_type>
MNCI range_iter_type<integral_type>
range_type<integral_type>::begin() const noexcept
{
  return range_iter_type(lower);
}

template<typename integral_type>
MNCI range_iter_type<integral_type>
range_type<integral_type>::end() const noexcept
{
  return range_iter_type(upper);
}

/*
 * factories
 */

template<typename integral_type>
MNCI range_type<integral_type>
Range(integral_type lower, integral_type upper) noexcept
{
  Assert(lower <= upper, "Invalid Parameter for Range! lower > upper.");
  return { lower, upper };
}

}

#endif
