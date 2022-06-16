#ifndef STL_ARRAY_HPP
#define STL_ARRAY_HPP

#include "stl.hpp"
#include "view.hpp"

namespace stl {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

template<typename type_type, size_type capacity>
struct array_type
{
  // === member ===
  type_type data[capacity];

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  // === magic methods ===

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Capacity() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* At(size_type index) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* At(size_type index) noexcept;

  // === transparent methods ===

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* begin() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* end() noexcept;

  //   ____    ___    _   _  __     __  _____   ____    ____    ___    ___    _   _
  //  / ___|  / _ \  | \ | | \ \   / / | ____| |  _ \  / ___|  |_ _|  / _ \  | \ | |
  // | |     | | | | |  \| |  \ \ / /  |  _|   | |_) | \___ \   | |  | | | | |  \| |
  // | |___  | |_| | | |\  |   \ V /   | |___  |  _ <   ___) |  | |  | |_| | | |\  |
  //  \____|  \___/  |_| \_|    \_/    |_____| |_| \_\ |____/  |___|  \___/  |_| \_|

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> ToView() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> ToView() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> ToView(size_type upper) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> ToView(size_type upper) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> ToView(size_type lower, size_type upper) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> ToView(size_type lower, size_type upper) const noexcept;
};

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline array_type<type_type, capacity>
Array() noexcept;

}

// include implementation
#include "array.inl"

#endif
