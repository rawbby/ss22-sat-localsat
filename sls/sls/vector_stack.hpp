#ifndef SLS_VECTOR_STACK_HPP
#define SLS_VECTOR_STACK_HPP

#include "stl/stl.hpp"

#include "stl/vector.hpp"
#include "stl/view.hpp"

namespace sls {

/*
 * vector stack iterator declaration
 */

template<typename type_type>
struct vector_stack_iter_type
{
  type_type* data;
  stl::size_type* range;

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(const vector_stack_iter_type& iter) noexcept
    : data(iter.data)
    , range(iter.range)
  {
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(type_type* data, stl::size_type* range) noexcept
    : data(data)
    , range(range)
  {
  }

  // satisfy the iterator concept
  [[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<const type_type> operator*() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<type_type> operator*() noexcept;
  [[maybe_unused]] constexpr inline vector_stack_iter_type<type_type>& operator++() noexcept;
  [[maybe_unused]] constexpr inline vector_stack_iter_type<type_type> operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const vector_stack_iter_type& other) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const vector_stack_iter_type& other) const noexcept;
};

/*
 * vector stack declaration
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
  requires stl::vector_concept<buffer_vector_type, type_type> && stl::vector_concept<ranges_vector_type, stl::size_type>
struct vector_stack_type
{
  buffer_vector_type buffer;
  ranges_vector_type ranges;

  // satisfy the viewable concept
  [[maybe_unused]] [[nodiscard]] inline stl::size_type Count() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type> At(stl::size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline stl::view_type<type_type> At(stl::size_type index) noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type& operator[](stl::size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type& operator[](stl::size_type index) noexcept;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<type_type> begin() noexcept;
  [[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<type_type> end() noexcept;

  // utilities
  [[maybe_unused]] [[nodiscard]] inline stl::size_type Capacity() const noexcept;
  [[maybe_unused]] inline void Capacity(stl::size_type new_count) noexcept;
  [[maybe_unused]] inline void Count(stl::size_type new_count) noexcept;
  [[maybe_unused]] inline void Push(type_type type) noexcept;
  [[maybe_unused]] inline void Push() noexcept;
  [[maybe_unused]] inline void Pop() noexcept;
  [[maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type>* Peak() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline stl::view_type<const type_type>* Peak() noexcept;
};

/*
 * factories
 */

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
[[maybe_unused]] inline void
VectorStack(vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>* stack) noexcept;

template<typename type_type, typename buffer_vector_type, typename ranges_vector_type>
[[maybe_unused]] [[nodiscard]] inline vector_stack_type<type_type, buffer_vector_type, ranges_vector_type>
VectorStack() noexcept;

}

// include implementation
#include "vector_stack.inl"

#endif
