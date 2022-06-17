#ifndef STL_VIEW_INL
#define STL_VIEW_INL

#include "stl.hpp"
#include "view.hpp"

#include <cstring>

namespace stl {

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

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_type<type_type>::begin() noexcept
{
  return data;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_type<type_type>::end() noexcept
{
  return &(data[count]);
}

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

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

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_type<type_type> view, size_type lower, size_type upper) noexcept
{
  Assert(upper >= lower, "View can not be initialized in reverse Order!");
  Assert(upper >= Size(0), "View Can not be access with a negative Index!");
  Assert(upper <= view.Count(), "View Can not be access with an Index larger its Count!");
  return { &(view.data[lower]), upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_type<type_type> view, size_type upper) noexcept
{
  Assert(upper >= Size(0), "View Can not be access with a negative Index!");
  Assert(upper <= view.Count(), "View Can not be access with an Index larger its Count!");
  return { view.data, upper };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_type<type_type> view) noexcept
{
  return { view.data, view.count };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const view_convertible_concept<type_type> auto& view_convertible, size_type lower, size_type upper) noexcept
{
  return View(view_convertible.ToView(), lower, upper);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_convertible_concept<type_type> auto& view_convertible, size_type lower, size_type upper) noexcept
{
  return View(view_convertible.ToView(), lower, upper);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const view_convertible_concept<type_type> auto& view_convertible, size_type upper) noexcept
{
  return View(view_convertible.ToView(), upper);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_convertible_concept<type_type> auto& view_convertible, size_type upper) noexcept
{
  return View(view_convertible.ToView(), upper);
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const view_convertible_concept<type_type> auto& view_convertible) noexcept
{
  return view_convertible.ToView();
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_convertible_concept<type_type> auto& view_convertible) noexcept
{
  return view_convertible.ToView();
}

}

#endif
