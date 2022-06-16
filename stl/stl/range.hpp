#ifndef STL_RANGE_HPP
#define STL_RANGE_HPP

#include <limits>

#include "static_vector.hpp"
#include "stl.hpp"

namespace stl {

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

struct range_iter_type
{
  size_type i;

  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type(const range_iter_type& iter) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline explicit range_iter_type(size_type i) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type operator*() const noexcept;

  [[maybe_unused]] constexpr inline range_iter_type& operator++() noexcept;

  [[maybe_unused]] constexpr inline const range_iter_type operator++(int) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const range_iter_type& other) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const range_iter_type& other) const noexcept;
};

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

struct range_type
{
  size_type lower;
  size_type upper;

  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type begin() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline range_iter_type end() const noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline range_type
Range(size_type lower, size_type upper) noexcept;

}

// include implementation
#include "range.inl"

#endif
