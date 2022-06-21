#ifndef STL_STATIC_VECTOR_INL
#define STL_STATIC_VECTOR_INL

#include "static_vector.hpp"
#include "stl.hpp"
#include "view.hpp"

namespace stl {

/*
 * satisfy the viewable concept
 */

template<typename type_type, size_type capacity>
MNCI size_type
static_vector_type<type_type, capacity>::Count() const noexcept
{
  return count;
}

template<typename type_type, size_type capacity>
MNCI const type_type*
static_vector_type<type_type, capacity>::At(size_type index) const noexcept
{
  stl::Assert(index >= 0 && index < capacity, "Can not access Array out of Bounds!");
  return &(data[index]);
}

template<typename type_type, size_type capacity>
MNCI type_type*
static_vector_type<type_type, capacity>::At(size_type index) noexcept
{
  stl::Assert(index >= 0 && index < capacity, "Can not access Array out of Bounds!");
  return &(data[index]);
}

template<typename type_type, size_type capacity>
MNCI const type_type&
static_vector_type<type_type, capacity>::operator[](size_type index) const noexcept
{
  stl::Assert(index >= 0 && index < capacity, "Can not access Array out of Bounds!");
  return data[index];
}

template<typename type_type, size_type capacity>
MNCI type_type&
static_vector_type<type_type, capacity>::operator[](size_type index) noexcept
{
  stl::Assert(index >= 0 && index < capacity, "Can not access Array out of Bounds!");
  return data[index];
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, size_type capacity>
MNCI const type_type*
static_vector_type<type_type, capacity>::begin() const noexcept
{
  return &(data[0]);
}

template<typename type_type, size_type capacity>
MNCI const type_type*
static_vector_type<type_type, capacity>::end() const noexcept
{
  return &(data[count]);
}

template<typename type_type, size_type capacity>
MNCI type_type*
static_vector_type<type_type, capacity>::begin() noexcept
{
  return &(data[0]);
}

template<typename type_type, size_type capacity>
MNCI type_type*
static_vector_type<type_type, capacity>::end() noexcept
{
  return &(data[count]);
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, size_type capacity>
MNCI view_type<type_type>
static_vector_type<type_type, capacity>::View() noexcept
{
  return { &(data[0]), count };
}

template<typename type_type, size_type capacity>
MNCI view_type<const type_type>
static_vector_type<type_type, capacity>::View() const noexcept
{
  return { &(data[0]), count };
}

/*
 * utilities
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline size_type
static_vector_type<type_type, capacity>::Capacity() const noexcept
{
  return capacity;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Capacity(size_type new_count) noexcept
{
  Assert(new_count <= capacity, "Can not capacity StaticVector beyond its Capacity!");
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Count(size_type new_count) noexcept
{
  Assert(new_count <= capacity, "Can not capacity StaticVector beyond its Capacity!");
  count = new_count;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Push(type_type type) noexcept
{
  Assert(count < capacity + 1, "Can not capacity StaticVector beyond its Capacity!");
  data[count] = type;
  ++count;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Pop() noexcept
{
  stl::Assert(count, "Can not pop from empty Vector!");
  --count;
}

template<typename type_type, size_type capacity>
MNCI const type_type*
static_vector_type<type_type, capacity>::Peak() const noexcept
{
  stl::Assert(count, "Can not peak on empty Vector!");
  return &(data.data[count - 1]);
}

template<typename type_type, size_type capacity>
MNCI type_type*
static_vector_type<type_type, capacity>::Peak() noexcept
{
  stl::Assert(count, "Can not peak on empty Vector!");
  return &(data.data[count - 1]);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Remove(size_type index) noexcept
{
  stl::Assert(count, "Can not remove from empty Vector!");
  stl::Assert(index >= 0 && index < count, "Can not remove Vector out of Bounds!");
  data.data[index] = data.data[--count];
}

}

#endif
