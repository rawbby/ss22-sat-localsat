#ifndef SLS_VECTOR_STACK_INL
#define SLS_VECTOR_STACK_INL

#include "vector_stack.hpp"

#include "stl/stl.hpp"
#include "stl/range.hpp"

namespace sls {

/*
 * satisfy the iterator concept
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<const type_type>
vector_stack_iter_type<type_type>::operator*() const noexcept
{
  return { &(data[range[0]]), range[1] - range[0] };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<type_type>
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
  stl::Assert(data == other.data, "Invalid iterator comparison!");
  return range == other.range;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
vector_stack_iter_type<type_type>::operator!=(const vector_stack_iter_type& other) const noexcept
{
  stl::Assert(data == other.data, "Invalid iterator comparison!");
  return range != other.range;
}

/*
 * satisfy the viewable concept
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::size_type
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Count() const noexcept
{
  return ranges.Count() - stl::Size(1);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type>
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::At(stl::size_type index) const noexcept
{
  static_assert(stl::view_convertible_concept<decltype(buffer), type_type>);
  stl::Assert(index >= stl::Size(0), "Stack Can not be access with a negative Index!");
  stl::Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
  const auto lower = *ranges.At(index);
  const auto upper = *ranges.At(index + stl::Size(1));
  return buffer.View().Range(lower, upper);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::view_type<type_type>
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::At(stl::size_type index) noexcept
{
  stl::Assert(index >= stl::Size(0), "Stack Can not be access with a negative Index!");
  stl::Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
  const auto lower = *ranges.At(index);
  const auto upper = *ranges.At(index + stl::Size(1));
  return buffer.View().Range(lower, upper);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline const type_type&
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::operator[](stl::size_type index) const noexcept
{
  return *At(index);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline type_type&
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::operator[](stl::size_type index) noexcept
{
  return *At(index);
}

/*
 * satisfy the iterable concept
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<type_type>
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::begin() noexcept
{
  return { buffer.begin(), ranges.begin() };
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<type_type>
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::end() noexcept
{
  return { buffer.begin(), ranges.end() };
}

/*
 * utilities
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::size_type
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Capacity() const noexcept
{
  return ranges.Capacity();
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] inline void
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Capacity(stl::size_type new_count) noexcept
{
  ranges.Capacity(new_count);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] inline void
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Count(stl::size_type new_count) noexcept
{
  ranges.Count(new_count + stl::Size(1));
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] inline void
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Push(type_type type) noexcept
{
  buffer.Push(type);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] inline void
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Push() noexcept
{
  ranges.Push(buffer.Count());
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] inline void
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Pop() noexcept
{
  ranges.Pop();
  buffer.Count(*ranges.Peak());
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type>*
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Peak() const noexcept
{
  stl::Assert(Count() > stl::Size(0), "Can not peak an empty Stack!");
  const auto lower = ranges.At(ranges.Size() - stl::Size(2));
  const auto upper = ranges.At(ranges.Size() - stl::Size(1));
  return View(buffer).Range(lower, upper);
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type> [
                                                               [maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type>*
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>::Peak() noexcept
{
  stl::Assert(Count() > stl::Size(0), "Can not peak an empty Stack!");
  const auto lower = ranges.At(ranges.Count() - stl::Size(2));
  const auto upper = ranges.At(ranges.Count() - stl::Size(1));
  return View(buffer).Range(lower, upper);
}

/*
 * factories
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
[[maybe_unused]] inline void
VectorStack(vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>* stack) noexcept
{
  StaticVector(&stack->buffer);
  StaticVector(&stack->ranges);
  stack->ranges.Push(stl::Size(0));
}

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
[[maybe_unused]] [[nodiscard]] inline vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>
VectorStack() noexcept
{
  vector_stack_type<type_type, buffer_vector_type, ranges_vector_type> stack;
  VectorStack(&stack);
  return stack;
}

}

#endif
