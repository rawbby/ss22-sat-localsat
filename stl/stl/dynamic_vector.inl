#ifndef STL_DYNAMIC_VECTOR_INL
#define STL_DYNAMIC_VECTOR_INL

#include "dynamic_vector.hpp"

namespace stl {

namespace detail {

MNCI size_type
InitialCapacity(size_type type_bytes)
{
  auto lcm = [](auto l, auto u) {
    auto lcm = u;
    auto i = Size(2);
    while (lcm % l)
      lcm = u * i++;
    return lcm;
  };

  const auto a = type_bytes;
  const auto b = Size(alignment_cache_line_tag::alignment);

  if (a > b)
    return lcm(a, b);
  else
    return lcm(b, a);
}

}

/*
 * satisfy the viewable concept
 */

template<typename type_type, typename allocator_type>
MNI size_type
dynamic_vector_type<type_type, allocator_type>::Count() const noexcept
{
  return View().Count();
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, typename allocator_type>
MNI const type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) const noexcept
{
  return *At(index);
}
template<typename type_type, typename allocator_type>
MNI type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::begin() const noexcept
{
  return View().begin();
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::end() const noexcept
{
  return View().end();
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::begin() noexcept
{
  return View().begin();
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::end() noexcept
{
  return View().end();
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, typename allocator_type>
MNI view_type<type_type>
dynamic_vector_type<type_type, allocator_type>::View() noexcept
{
  return { data.data, count };
}

template<typename type_type, typename allocator_type>
MNI view_type<const type_type>
dynamic_vector_type<type_type, allocator_type>::View() const noexcept
{
  return { data.data, count };
}

/*
 * utilities
 */

template<typename type_type, typename allocator_type>
MNI size_type
dynamic_vector_type<type_type, allocator_type>::Capacity() const noexcept
{
  return data.count;
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Capacity(size_type new_count) noexcept
{
  constexpr auto init_cap = detail::InitialCapacity(sizeof(type_type));

  if (data.count < new_count) {

    // maybe initialize count and
    // double the count until new_count is satisfied
    auto the_count = data.count ? data.count : init_cap;
    while (the_count < new_count)
      the_count <<= 1;

    if (data.count)
      data = allocator->template ReAllocate<type_type>(data, the_count);
    else
      data = allocator->template Allocate<type_type>(the_count);

    Assert(data.data, "Failed to re allocate dynamic Vector!");
  }
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Count(size_type new_count) noexcept
{
  Capacity(new_count);
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
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::Peak() const noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, typename allocator_type>
MNI type_type*
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

}

#endif
