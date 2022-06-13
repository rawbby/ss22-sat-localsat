#ifndef STL_RANGE_INL
#define STL_RANGE_INL

#include "range.hpp"

namespace stl {

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline range_type
Range(size_type lower, size_type upper) noexcept
{
  return { lower, upper };
}

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

[[maybe_unused]] [[nodiscard]] constexpr inline size_type
range_iterator_type::Next() noexcept
{
  return i++;
}
[[maybe_unused]] [[nodiscard]] constexpr inline bool
range_iterator_type::HasNext() const noexcept
{
  return i < n;
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline range_iterator_type
Iterator(range_type range) noexcept
{
  return { range.lower, range.upper };
}

}

#endif
