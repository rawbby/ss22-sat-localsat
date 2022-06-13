#ifndef STL_VECTOR_HPP
#define STL_VECTOR_HPP

#include "stl.hpp"
#include "view.hpp"

#include <type_traits> // std::is_constant_evaluated

namespace stl {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

template<typename type_type, size_type capacity>
struct vector_type
{
  // === member ===

  type_type data[capacity];
  size_type count;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  // === magic methods ===

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Count() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline void Count(size_type new_count) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* At(size_type index) const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* At(size_type index) noexcept;

  // === transparent methods ===

  [[maybe_unused]] [[nodiscard]] constexpr inline void Push(type_type type) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline void Pop() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline void Remove(size_type index) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type* Peak() const noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* Peak() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* begin() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline type_type* end() noexcept;
};

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_type<type_type, capacity>
Vector() noexcept;

//   ____    ___    _   _  __     __  _____   ____    ____    ___    ___    _   _   ____
//  / ___|  / _ \  | \ | | \ \   / / | ____| |  _ \  / ___|  |_ _|  / _ \  | \ | | / ___|
// | |     | | | | |  \| |  \ \ / /  |  _|   | |_) | \___ \   | |  | | | | |  \| | \___ \
// | |___  | |_| | | |\  |   \ V /   | |___  |  _ <   ___) |  | |  | |_| | | |\  |  ___) |
//  \____|  \___/  |_| \_|    \_/    |_____| |_| \_\ |____/  |___|  \___/  |_| \_| |____/

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const vector_type<type_type, vector_capacity>* vector) noexcept;

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(vector_type<type_type, vector_capacity>* vector) noexcept;

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const vector_type<type_type, vector_capacity>* vector, size_type lower, size_type upper) noexcept;

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(vector_type<type_type, vector_capacity>* vector, size_type lower, size_type upper) noexcept;

}

// include implementation
#include "vector.inl"

#endif
