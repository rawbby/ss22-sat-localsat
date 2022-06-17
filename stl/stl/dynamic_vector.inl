#ifndef STL_DYNAMIC_VECTOR_INL
#define STL_DYNAMIC_VECTOR_INL

#include "dynamic_vector.hpp"

namespace stl {

/*
 * satisfy the viewable concept
 */

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline size_type
dynamic_vector_type<type_type, allocator_type>::Count() const noexcept
{
  return View().Count();
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline const type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline const type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) const noexcept
{
  return *At(index);
}
template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline type_type*
dynamic_vector_type<type_type, allocator_type>::begin() noexcept
{
  return View().begin();
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline type_type*
dynamic_vector_type<type_type, allocator_type>::end() noexcept
{
  return View().end();
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline view_type<type_type>
dynamic_vector_type<type_type, allocator_type>::View() noexcept
{
  return { (type_type*)data.data, count };
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline view_type<const type_type>
dynamic_vector_type<type_type, allocator_type>::View() const noexcept
{
  return { (type_type*)data.data, count };
}

/*
 * utilities
 */

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Count(size_type new_count) noexcept
{
  const auto new_capacity = Size(new_count * sizeof(type_type));
  auto capacity = Size(data.count);

  if (capacity < new_capacity) {

    // if count is not initialized use one cache line minimum
    capacity = capacity ? capacity : Size(alignment_cache_line_tag::alignment);

    // double the count until the new size is in the capacity
    while (capacity < new_capacity)
      capacity <<= 1;

    auto new_data = allocator->ReAllocate(data, capacity);
    Assert(new_data.data, "Failed to re allocate dynamic StaticVector!");

    data = new_data;
  }

  count = new_count;
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Push(type_type type) noexcept
{
  Count(Count() + Size(1));
  *Peak() = type;
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Pop() noexcept
{
  Count(Count() - Size(1));
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline const type_type*
dynamic_vector_type<type_type, allocator_type>::Peak() const noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline type_type*
dynamic_vector_type<type_type, allocator_type>::Peak() noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Remove(size_type index) noexcept
{
  *At(index) = *Peak();
  Pop();
}

/*
 * factories
 */

template<typename type_type, typename allocator_type>
[[maybe_unused]] [[nodiscard]] inline dynamic_vector_type<type_type, allocator_type>
DynamicVector(allocator_type* allocator) noexcept
{
  return { .allocator = allocator };
}

}

#endif
