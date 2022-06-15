#ifndef STL_RANGE_INL
#define STL_RANGE_INL

#include "range.hpp"

namespace stl {

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type::range_iter_type(const range_iter_type& iter) noexcept
  : i(iter.i)
{
}

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type::range_iter_type(size_type i) noexcept
  : i(i)
{
}

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

[[maybe_unused]] constexpr inline range_iter_type
range_iter_type::operator++(int) noexcept
{
  return { i++ };
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

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type
range_type::begin() noexcept
{
  return { lower };
}

[[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type
range_type::end() noexcept
{
  return { upper };
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline range_type
Range(size_type lower, size_type upper) noexcept
{
  Assert(lower <= upper, "Invalid Parameter for Range! lower > upper.");
  return { lower, upper };
}

}

#endif
