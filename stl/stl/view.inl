#ifndef STL_VIEW_INL
#define STL_VIEW_INL

#include "stl.hpp"
#include "view.hpp"

#include <cstring>

namespace stl {

/*
 * satisfy the viewable concept
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline size_type
view_type<type_type>::Count() const noexcept
{
  return count;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type*
view_type<type_type>::At(size_type index) const noexcept
{
  Assert(index >= Size(0), "View Can not be access with a negative Index!");
  Assert(index < Count(), "View Can not be access with an Index larger its Count!");
  return &(data[index]);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_type<type_type>::At(size_type index) noexcept
{
  Assert(index >= Size(0), "View Can not be access with a negative Index!");
  Assert(index < Count(), "View Can not be access with an Index larger its Count!");
  return &(data[index]);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type&
view_type<type_type>::operator[](size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type&
view_type<type_type>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the iterable concept
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_type<type_type>::begin() noexcept
{
  return At(0);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_type<type_type>::end() noexcept
{
  return &(data[Count()]);
}

/*
 * utilities
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
view_type<type_type>::Range(size_type lower, size_type upper) const noexcept
{
  return { At(lower), upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
view_type<type_type>::Range(size_type lower, size_type upper) noexcept
{
  return { At(lower), upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
view_type<type_type>::Range(size_type upper) const noexcept
{
  return { At(0), upper };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
view_type<type_type>::Range(size_type upper) noexcept
{
  return { At(0), upper };
}

template<typename type_type>
[[maybe_unused]] constexpr inline void
view_type<type_type>::MemSet(i32_type value) noexcept
{
  if (!std::is_constant_evaluated()) {
    memset(data, value, Count() * sizeof(type_type));
    return;
  }

  auto* p = static_cast<stl::byte_type*>(static_cast<void*>(data));
  const auto n = Count() * sizeof(type_type);
  for (auto i = Size(0); i < n; ++i)
    p[i] = Byte(value);
}

template<typename type_type>
[[maybe_unused]] constexpr inline void
view_type<type_type>::MemCopy(view_type<type_type> dst) const noexcept
{
  Assert(dst.Count() == Count(), "Can not MemCopy from uneven sized Views!");

  if (!std::is_constant_evaluated()) {
    memcpy(dst.data, data, Count() * sizeof(type_type));
    return;
  }

  const auto n = Count();
  for (auto i = Size(0); i < n; ++i)
    *dst.At(i) = *At(i);
}

/*
 * factories
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type upper) noexcept
{
  return { data, upper };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type upper) noexcept
{
  return { data, upper };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type lower, size_type upper) noexcept
{
  return { &(data[lower]), upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type lower, size_type upper) noexcept
{
  return { &(data[lower]), upper - lower };
}

}

#endif
