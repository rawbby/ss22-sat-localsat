#ifndef STL_DYNAMIC_ARRAY_INL
#define STL_DYNAMIC_ARRAY_INL

#include "dynamic_array.hpp"

namespace stl {

template<typename type_type, typename allocator_type>
MNI size_type
dynamic_array_type<type_type, allocator_type>::Count() const noexcept
{
  return data.count;
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_array_type<type_type, allocator_type>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_array_type<type_type, allocator_type>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_array_type<type_type, allocator_type>::begin() const noexcept
{
  return View().At(0);
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_array_type<type_type, allocator_type>::end() const noexcept
{
  return View().At(data.count);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_array_type<type_type, allocator_type>::begin() noexcept
{
  return View().At(0);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_array_type<type_type, allocator_type>::end() noexcept
{
  return View().At(data.count);
}

template<typename type_type, typename allocator_type>
MNI const type_type&
dynamic_array_type<type_type, allocator_type>::operator[](size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type, typename allocator_type>
MNI type_type&
dynamic_array_type<type_type, allocator_type>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, typename allocator_type>
MNI view_type<type_type>
dynamic_array_type<type_type, allocator_type>::View() noexcept
{
  return { data.data, data.count };
}

template<typename type_type, typename allocator_type>
MNI view_type<const type_type>
dynamic_array_type<type_type, allocator_type>::View() const noexcept
{
  return { data.data, data.count };
}

}

#endif
