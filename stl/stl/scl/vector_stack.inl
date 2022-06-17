#ifndef STL_VECTOR_STACK_INL
#define STL_VECTOR_STACK_INL

#include "vector_stack.hpp"

namespace stl {

/*
 * satisfy the iterator concept
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
vector_stack_iter_type<type_type>::operator*() const noexcept
{
  return { &(data[range[0]]), range[1] - range[0] };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
vector_stack_iter_type<type_type>::operator*() noexcept
{
  return { &(data[range[0]]), range[1] - range[0] };
}

template<typename type_type>
[[maybe_unused]] constexpr inline vector_stack_iter_type<type_type>&
vector_stack_iter_type<type_type>::operator++() noexcept
{
  range++;
  return *this;
}

template<typename type_type>
[[maybe_unused]] constexpr inline vector_stack_iter_type<type_type> // NOLINT(cert-dcl21-cpp)
vector_stack_iter_type<type_type>::operator++(int) noexcept
{
  return { data, range++ };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
vector_stack_iter_type<type_type>::operator==(const vector_stack_iter_type& other) const noexcept
{
  Assert(data == other.data, "Invalid iterator comparison!");
  return range == other.range;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
vector_stack_iter_type<type_type>::operator!=(const vector_stack_iter_type& other) const noexcept
{
  Assert(data == other.data, "Invalid iterator comparison!");
  return range != other.range;
}

/*
 * satisfy the viewable concept
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline size_type
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Count() const noexcept
{
  return ranges.Count() - Size(1);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>
vector_stack_type<type_type, stack_capacity, buffer_capacity>::At(size_type index) const noexcept
{
  static_assert(view_convertible_concept<decltype(buffer), type_type>);
  Assert(index >= Size(0), "Stack Can not be access with a negative Index!");
  Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
  const auto lower = *ranges.At(index);
  const auto upper = *ranges.At(index + Size(1));
  return buffer.View().Range(lower, upper);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type>
vector_stack_type<type_type, stack_capacity, buffer_capacity>::At(size_type index) noexcept
{
  Assert(index >= Size(0), "Stack Can not be access with a negative Index!");
  Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
  const auto lower = *ranges.At(index);
  const auto upper = *ranges.At(index + Size(1));
  return buffer.View().Range(lower, upper);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline const type_type&
vector_stack_type<type_type, stack_capacity, buffer_capacity>::operator[](size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline type_type&
vector_stack_type<type_type, stack_capacity, buffer_capacity>::operator[](size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type>
vector_stack_type<type_type, stack_capacity, buffer_capacity>::begin() noexcept
{
  return { buffer.data, ranges.data };
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type>
vector_stack_type<type_type, stack_capacity, buffer_capacity>::end() noexcept
{
  return { buffer.data, &(ranges.data[Count()]) };
}

/*
 * utilities
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Push(type_type type) noexcept
{
  buffer.Push(type);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Push() noexcept
{
  ranges.Push(buffer.Count());
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Pop() noexcept
{
  ranges.Pop();
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>*
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Peak() const noexcept
{
  Assert(Count() > Size(0), "Can not peak an empty Stack!");
  const auto lower = ranges.At(ranges.Size() - Size(2));
  const auto upper = ranges.At(ranges.Size() - Size(1));
  return View(buffer).Range(lower, upper);
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>*
vector_stack_type<type_type, stack_capacity, buffer_capacity>::Peak() noexcept
{
  Assert(Count() > Size(0), "Can not peak an empty Stack!");
  const auto lower = ranges.At(ranges.Count() - Size(2));
  const auto upper = ranges.At(ranges.Count() - Size(1));
  return View(buffer).Range(lower, upper);
}

/*
 * factories
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
VectorStack(vector_stack_type<type_type, stack_capacity, buffer_capacity>* stack) noexcept
{
  StaticVector(&stack->buffer);
  StaticVector(&stack->ranges);
  stack->ranges.Push(Size(0));
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_type<type_type, stack_capacity, buffer_capacity>
VectorStack() noexcept
{
  vector_stack_type<type_type, stack_capacity, buffer_capacity> stack;
  VectorStack(&stack);
  return stack;
}

}

#endif
