#ifndef STL_ARRAY_INL
#define STL_ARRAY_INL

#include "array.hpp"
#include <type_traits>

namespace stl {

template<typename type_type, size_type capacity>
constexpr size_type
array_type<type_type, capacity>::Capacity() const noexcept
{
  return capacity;
}

template<typename type_type, size_type capacity>
constexpr const type_type*
array_type<type_type, capacity>::At(size_type index) const noexcept
{
  return ToView().At(index);
}

template<typename type_type, size_type capacity>
constexpr type_type*
array_type<type_type, capacity>::At(size_type index) noexcept
{
  return ToView().At(index);
}

template<typename type_type, size_type capacity>
constexpr type_type*
array_type<type_type, capacity>::begin() noexcept
{
  return ToView().At(0);
}

template<typename type_type, size_type capacity>
constexpr type_type*
array_type<type_type, capacity>::end() noexcept
{
  return ToView().At(capacity);
}

//   ____    ___    _   _  __     __  _____   ____    ____    ___    ___    _   _
//  / ___|  / _ \  | \ | | \ \   / / | ____| |  _ \  / ___|  |_ _|  / _ \  | \ | |
// | |     | | | | |  \| |  \ \ / /  |  _|   | |_) | \___ \   | |  | | | | |  \| |
// | |___  | |_| | | |\  |   \ V /   | |___  |  _ <   ___) |  | |  | |_| | | |\  |
//  \____|  \___/  |_| \_|    \_/    |_____| |_| \_\ |____/  |___|  \___/  |_| \_|

template<typename type_type, size_type capacity>
constexpr view_type<type_type>
array_type<type_type, capacity>::ToView() noexcept
{
  return View(data, capacity);
}

template<typename type_type, size_type capacity>
constexpr view_type<const type_type>
array_type<type_type, capacity>::ToView() const noexcept
{
  return View(data, capacity);
}

template<typename type_type, size_type capacity>
constexpr view_type<type_type>
array_type<type_type, capacity>::ToView(size_type upper) noexcept
{
  return View(ToView(), upper);
}

template<typename type_type, size_type capacity>
constexpr view_type<const type_type>
array_type<type_type, capacity>::ToView(size_type upper) const noexcept
{
  return View(ToView(), upper);
}

template<typename type_type, size_type capacity>
constexpr view_type<type_type>
array_type<type_type, capacity>::ToView(size_type lower, size_type upper) noexcept
{
  return View(ToView(), lower, upper);
}

template<typename type_type, size_type capacity>
constexpr view_type<const type_type>
array_type<type_type, capacity>::ToView(size_type lower, size_type upper) const noexcept
{
  return View(ToView(), lower, upper);
}

//  _____      _       ____   _____    ___    ____    ___   _____   ____
// |  ___|    / \     / ___| |_   _|  / _ \  |  _ \  |_ _| | ____| / ___|
// | |_      / _ \   | |       | |   | | | | | |_) |  | |  |  _|   \___ \
// |  _|    / ___ \  | |___    | |   | |_| | |  _ <   | |  | |___   ___) |
// |_|     /_/   \_\  \____|   |_|    \___/  |_| \_\ |___| |_____| |____/

template<typename type_type, size_type capacity>
constexpr array_type<type_type, capacity>
Array() noexcept
{
  if (std::is_constant_evaluated())
    return {};
  array_type<type_type, capacity> array;
  return array;
}

}

#endif
