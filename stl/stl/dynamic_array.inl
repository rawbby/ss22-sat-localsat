#ifndef STL_DYNAMIC_ARRAY_INL
#define STL_DYNAMIC_ARRAY_INL

#include "dynamic_array.hpp"

namespace stl {

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
size_type
dynamic_array_type<type_type, allocator_type>::Count() const noexcept
{
  return data.count;
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
const type_type*
dynamic_array_type<type_type, allocator_type>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
type_type*
dynamic_array_type<type_type, allocator_type>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
type_type*
dynamic_array_type<type_type, allocator_type>::begin() noexcept
{
  return View().At(0);
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
type_type*
dynamic_array_type<type_type, allocator_type>::end() noexcept
{
  return View().At(data.count);
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type> [
    [maybe_unused]] [[nodiscard]] inline const type_type&
  dynamic_array_type<type_type, allocator_type>::operator[](size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type> [
    [maybe_unused]] [[nodiscard]] inline type_type&
  dynamic_array_type<type_type, allocator_type>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
view_type<type_type>
dynamic_array_type<type_type, allocator_type>::View() noexcept
{
  return { data.data, data.count };
}

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
view_type<const type_type>
dynamic_array_type<type_type, allocator_type>::View() const noexcept
{
  return { data.data, data.count };
}

/*
 * factories
 */

template<typename type_type, typename allocator_type>
  requires allocator_concept<allocator_type>
dynamic_array_type<type_type, allocator_type>
DynamicArray(allocator_type* allocator, size_type count) noexcept
{
  dynamic_array_type<type_type, allocator_type> array;
  array.data = allocator->Allocate<type_type>(count);
  array.allocator = allocator;
  return array;
}

}

#endif
