#ifndef STL_VIEW_HPP
#define STL_VIEW_HPP

#include "stl.hpp"
#include "vector.hpp"

namespace stl {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

template<typename type_type>
struct view_type
{
  type_type* data;
  size_type count;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  // === magic methods ===

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Count() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* At(size_type index) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* At(size_type index) noexcept;

  [[maybe_unused]] constexpr inline void MemSet(i32_type value) noexcept;

  [[maybe_unused]] constexpr inline void MemCopy(view_type<type_type> dst) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* begin() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* end() noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type lower, size_type upper) noexcept;

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_type<type_type> view, size_type lower, size_type upper) noexcept;

}

// include implementation
#include "view.inl"

#endif
