#ifndef STL_VIEW_INL
#define STL_VIEW_INL

#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline size_type
view_type<type_type>::Count() const noexcept
{
  return size;
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
  memset(data, value, Count() * sizeof(type_type));
}

template<typename type_type>
[[maybe_unused]] constexpr inline void
view_type<type_type>::MemCopy(view_type<type_type> dst) const noexcept
{
  Assert(dst.Count() == Count(), "Can not MemCopy from uneven sized Views!");
  memcpy(dst.data, data, Count() * sizeof(type_type));
}

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
view_iterator_type<type_type>::Next()
{
  Assert(HasNext(), "Can not fetch Next from empty Iterator!");
  --count;
  return data++;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
view_iterator_type<type_type>::HasNext()
{
  return count > 0;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_iterator_type<type_type>
Iterator(view_type<type_type> view) noexcept
{
  return { view.data, view.size };
}

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
View(const type_type* data, size_type lower, size_type upper) noexcept
{
  return { *data[lower], upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(type_type* data, size_type lower, size_type upper) noexcept
{
  return { *data[lower], upper - lower };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
View(view_type<type_type> view, size_type lower, size_type upper) noexcept
{
  Assert(upper >= lower, "View can not be initialized in reverse Order!");
  Assert(upper >= Size(0), "View Can not be access with a negative Index!");
  Assert(upper <= view.Count(), "View Can not be access with an Index larger its Count!");
  return { view.At(lower), upper - lower };
}

}

#endif
