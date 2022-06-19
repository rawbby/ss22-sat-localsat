#ifndef STL_ARRAY_INL
#define STL_ARRAY_INL

#include "static_array.hpp"
#include <type_traits>

namespace stl {

template<typename type_type, size_type capacity>
constexpr size_type
static_array_type<type_type, capacity>::Count() const noexcept
{
  return capacity;
}

template<typename type_type, size_type capacity>
constexpr const type_type*
static_array_type<type_type, capacity>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, size_type capacity>
constexpr type_type*
static_array_type<type_type, capacity>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, size_type capacity>
constexpr const type_type*
static_array_type<type_type, capacity>::begin() const noexcept
{
  return &(data[0]);
}

template<typename type_type, size_type capacity>
constexpr const type_type*
static_array_type<type_type, capacity>::end() const noexcept
{
  return &(data[capacity]);
}

template<typename type_type, size_type capacity>
constexpr type_type*
static_array_type<type_type, capacity>::begin() noexcept
{
  return &(data[0]);
}

template<typename type_type, size_type capacity>
constexpr type_type*
static_array_type<type_type, capacity>::end() noexcept
{
  return &(data[capacity]);
}

template<typename type_type, size_type capacity>
MNCI const type_type&
static_array_type<type_type, capacity>::operator[](size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type, size_type capacity>
MNCI type_type&
static_array_type<type_type, capacity>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, size_type capacity>
constexpr view_type<type_type>
static_array_type<type_type, capacity>::View() noexcept
{
  return { data, capacity };
}

template<typename type_type, size_type capacity>
constexpr view_type<const type_type>
static_array_type<type_type, capacity>::View() const noexcept
{
  return { data, capacity };
}

/*
 * factories
 */

template<typename type_type, size_type capacity>
constexpr static_array_type<type_type, capacity>
StaticArray() noexcept
{
  if (std::is_constant_evaluated())
    return {};
  static_array_type<type_type, capacity> array;
  return array;
}

}

#endif
