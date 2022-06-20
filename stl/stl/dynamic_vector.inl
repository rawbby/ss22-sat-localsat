#ifndef STL_DYNAMIC_VECTOR_INL
#define STL_DYNAMIC_VECTOR_INL

#include "dynamic_vector.hpp"

namespace stl {

template<typename type_type, typename allocator_type>
MI
dynamic_vector_type<type_type, allocator_type>::dynamic_vector_type(allocator_type* allocator) noexcept
  : allocator(allocator)
  , data()
  , count(Size(0))
{
}

template<typename type_type, typename allocator_type>
MI
dynamic_vector_type<type_type, allocator_type>::dynamic_vector_type(dynamic_vector_type&& vector) noexcept
  : allocator(nullptr)
  , data()
  , count(0)
{
  *this = std::move(vector);
}

template<typename type_type, typename allocator_type>
MI dynamic_vector_type<type_type, allocator_type>::~dynamic_vector_type() noexcept
{
  if (data.data)
    allocator->Free(data);
}

template<typename type_type, typename allocator_type>
MI dynamic_vector_type<type_type, allocator_type>&
dynamic_vector_type<type_type, allocator_type>::operator=(dynamic_vector_type&& vector) noexcept
{
  std::swap(allocator, vector.allocator);
  std::swap(data, vector.data);
  std::swap(count, vector.count);
  return *this;
}

/*
 * satisfy the viewable concept
 */

template<typename type_type, typename allocator_type>
MNI size_type
dynamic_vector_type<type_type, allocator_type>::Count() const noexcept
{
  return count;
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) const noexcept
{
  stl::Assert(index >= 0 && index < count, "Can not access Vector out of Bounds!");
  return &(data.data[index]);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::At(size_type index) noexcept
{
  stl::Assert(index >= 0 && index < count, "Can not access Vector out of Bounds!");
  return &(data.data[index]);
}

template<typename type_type, typename allocator_type>
MNI const type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) const noexcept
{
  stl::Assert(index >= 0 && index < count, "Can not access Vector out of Bounds!");
  return data.data[index];
}

template<typename type_type, typename allocator_type>
MNI type_type&
dynamic_vector_type<type_type, allocator_type>::operator[](size_type index) noexcept
{
  stl::Assert(index >= 0 && index < count, "Can not access Vector out of Bounds!");
  return data.data[index];
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::begin() const noexcept
{
  return &(data.data[0]);
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::end() const noexcept
{
  return &(data.data[count]);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::begin() noexcept
{
  return &(data.data[0]);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::end() noexcept
{
  return &(data.data[count]);
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
  constexpr auto initial_capacity = detail::initial_capacity<type_type>;

  if (data.count < new_count) {

    if (!data.count) {

      auto the_count = initial_capacity;
      while (the_count < new_count)
        the_count <<= 1;

      data = allocator->template Allocate<type_type>(the_count);

    } else {

      auto the_count = data.count;
      while (the_count < new_count)
        the_count <<= 1;

      data = allocator->template ReAllocate<type_type>(data, the_count);
    }

    Assert(data.data, "Failed to (re) allocate dynamic Vector!");
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
  Capacity(count + 1);
  data.data[count] = type;
  ++count;
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Pop() noexcept
{
  stl::Assert(count, "Can not pop from empty Vector!");
  --count;
}

template<typename type_type, typename allocator_type>
MNI const type_type*
dynamic_vector_type<type_type, allocator_type>::Peak() const noexcept
{
  stl::Assert(count, "Can not peak on empty Vector!");
  return &(data.data[count - 1]);
}

template<typename type_type, typename allocator_type>
MNI type_type*
dynamic_vector_type<type_type, allocator_type>::Peak() noexcept
{
  stl::Assert(count, "Can not peak on empty Vector!");
  return &(data.data[count - 1]);
}

template<typename type_type, typename allocator_type>
[[maybe_unused]] inline void
dynamic_vector_type<type_type, allocator_type>::Remove(size_type index) noexcept
{
  stl::Assert(count, "Can not remove from empty Vector!");
  stl::Assert(index >= 0 && index < count, "Can not remove Vector out of Bounds!");
  data.data[index] = data.data[--count];
}

}

#endif
