#ifndef STL_VECTOR_INL
#define STL_VECTOR_INL

#include "stl.hpp"
#include "vector.hpp"
#include "view.hpp"

namespace stl {

//  __  __   _____   _____   _   _    ___    ____    ____
// |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
// | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
// | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
// |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline size_type
vector_type<type_type, capacity>::Count() const noexcept
{
  return View(this).Count();
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline void
vector_type<type_type, capacity>::Count(size_type new_count) noexcept
{
  Assert(count <= capacity, "Can not count Vector beyond its Capacity!");
  count = new_count;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type*
vector_type<type_type, capacity>::At(size_type index) const noexcept
{
  return View(this).At(index);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
vector_type<type_type, capacity>::At(size_type index) noexcept
{
  return View(this).At(index);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline void
vector_type<type_type, capacity>::Push(type_type type) noexcept
{
  Count(Count() + Size(1));
  *Peak() = type;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline void
vector_type<type_type, capacity>::Pop() noexcept
{
  Count(Count() - Size(1));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline void
vector_type<type_type, capacity>::Remove(size_type index) noexcept
{
  *At(index) = *Peak();
  Pop();
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type*
vector_type<type_type, capacity>::Peak() const noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
vector_type<type_type, capacity>::Peak() noexcept
{
  return At(Count() - Size(1));
}

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_type<type_type, capacity>
Vector() noexcept
{
  // in a [[maybe_unused]] [[nodiscard]] constexpr inline environment
  // zero initialize the whole s_vector->
  if (std::is_constant_evaluated())
    return {};

  // as zero initialization is not needed
  // we do not take the effort in a non
  // [[maybe_unused]] [[nodiscard]] constexpr inline environment.
  vector_type<type_type, capacity> vector;
  vector.count = Size(0);
  return vector;
}

//   ___   _____   _____   ____       _      _____    ___    ____
//  |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//   | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//   | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
//  |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_iterator_type<type_type>
Iterator(vector_type<type_type, capacity>* vector) noexcept
{
  return Iterator(View(vector));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_iterator_type<const type_type>
Iterator(const vector_type<type_type, capacity>* vector) noexcept
{
  return Iterator(View(vector));
}

//   ____    ___    _   _  __     __  _____   ____    ____    ___    ___    _   _   ____
//  / ___|  / _ \  | \ | | \ \   / / | ____| |  _ \  / ___|  |_ _|  / _ \  | \ | | / ___|
// | |     | | | | |  \| |  \ \ / /  |  _|   | |_) | \___ \   | |  | | | | |  \| | \___ \
// | |___  | |_| | | |\  |   \ V /   | |___  |  _ <   ___) |  | |  | |_| | | |\  |  ___) |
//  \____|  \___/  |_| \_|    \_/    |_____| |_| \_\ |____/  |___|  \___/  |_| \_| |____/

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const vector_type<type_type, vector_capacity>* vector) noexcept
{
  return { vector->data, vector->count };
}

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(vector_type<type_type, vector_capacity>* vector) noexcept
{
  return { vector->data, vector->count };
}

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const vector_type<type_type, vector_capacity>* vector, size_type lower, size_type upper) noexcept
{
  return View(View(vector), lower, upper);
}

template<typename type_type, size_type vector_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(vector_type<type_type, vector_capacity>* vector, size_type lower, size_type upper) noexcept
{
  return View(View(vector), lower, upper);
}

}

#endif
