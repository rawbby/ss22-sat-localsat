#ifndef STL_DYNAMIC_VECTOR_HPP
#define STL_DYNAMIC_VECTOR_HPP

#include "alloc/alignment.hpp"
#include "alloc/allocator.hpp"
#include "stl.hpp"
#include "view.hpp"

namespace stl {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
struct dynamic_vector_type
{
  // === member ===
  allocator_type* allocator;
  memory_type data;
  size_type count;

  inline ~dynamic_vector_type() noexcept { allocator->Free(data); }

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  // === magic methods ===

  [[maybe_unused]] [[nodiscard]] inline size_type Count() const noexcept;

  [[maybe_unused]] inline void Count(size_type new_count) noexcept;

  [[maybe_unused]] [[nodiscard]] inline const type_type* At(size_type index) const noexcept;

  [[maybe_unused]] [[nodiscard]] inline type_type* At(size_type index) noexcept;

  // === transparent methods ===

  [[maybe_unused]] inline void Push(type_type type) noexcept;

  [[maybe_unused]] inline void Pop() noexcept;

  [[maybe_unused]] inline void Remove(size_type index) noexcept;

  [[maybe_unused]] [[nodiscard]] inline const type_type* Peak() const noexcept;

  [[maybe_unused]] [[nodiscard]] inline type_type* Peak() noexcept;

  // === iterator methods ===

  [[maybe_unused]] [[nodiscard]] inline type_type* begin() noexcept;

  [[maybe_unused]] [[nodiscard]] inline type_type* end() noexcept;

  //   ____    ___    _   _  __     __  _____   ____    ____    ___    ___    _   _
  //  / ___|  / _ \  | \ | | \ \   / / | ____| |  _ \  / ___|  |_ _|  / _ \  | \ | |
  // | |     | | | | |  \| |  \ \ / /  |  _|   | |_) | \___ \   | |  | | | | |  \| |
  // | |___  | |_| | | |\  |   \ V /   | |___  |  _ <   ___) |  | |  | |_| | | |\  |
  //  \____|  \___/  |_| \_|    \_/    |_____| |_| \_\ |____/  |___|  \___/  |_| \_|

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> ToView() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> ToView() const noexcept;
};

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] [[nodiscard]] inline dynamic_vector_type<type_type, allocator_type>
DynamicVector(allocator_type* allocator) noexcept;

}

// include implementation
#include "dynamic_vector.inl"

#endif
