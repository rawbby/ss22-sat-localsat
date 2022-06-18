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
[[maybe_unused]] [[nodiscard]] constexpr inline size_type
static_vector_type<type_type, capacity>::Count() const noexcept
{
  return View().Count();
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type*
static_vector_type<type_type, capacity>::At(size_type index) const noexcept
{
  return View().At(index);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
static_vector_type<type_type, capacity>::At(size_type index) noexcept
{
  return View().At(index);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type&
static_vector_type<type_type, capacity>::operator[](size_type index) const noexcept
{
  return View()[index];
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type&
static_vector_type<type_type, capacity>::operator[](size_type index) noexcept
{
  return View()[index];
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
static_vector_type<type_type, capacity>::begin() noexcept
{
  return View().begin();
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
static_vector_type<type_type, capacity>::end() noexcept
{
  return View().end();
}

/*
 * satisfy the view convertible concept
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
static_vector_type<type_type, capacity>::View() noexcept
{
  return { &(data[0]), count };
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
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
  Count(Count() + Size(1));
  *Peak() = type;
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Pop() noexcept
{
  Count(Count() - Size(1));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type*
static_vector_type<type_type, capacity>::Peak() const noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type*
static_vector_type<type_type, capacity>::Peak() noexcept
{
  return At(Count() - Size(1));
}

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
static_vector_type<type_type, capacity>::Remove(size_type index) noexcept
{
  *At(index) = *Peak();
  Pop();
}

/*
 * factories
 */

template<typename type_type, size_type capacity>
[[maybe_unused]] constexpr inline void
StaticVector(static_vector_type<type_type, capacity>* vector) noexcept
{
  vector->count = Size(0);
}

template<typename type_type, size_type capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline static_vector_type<type_type, capacity>
StaticVector() noexcept
{
  if (std::is_constant_evaluated()) {
    static_vector_type<type_type, capacity> vector{};
    StaticVector(&vector);
    return vector;
  }

  static_vector_type<type_type, capacity> vector;
  StaticVector(&vector);
  return vector;
}

}

#endif
