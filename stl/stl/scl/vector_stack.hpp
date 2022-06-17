#ifndef STL_VECTOR_STACK_HPP
#define STL_VECTOR_STACK_HPP

#include "../stl.hpp"

#include "../static_vector.hpp"
#include "../view.hpp"

namespace stl {

/*
 * vector stack iterator declaration
 */

template<typename type_type>
struct vector_stack_iter_type
{
  type_type* data;
  size_type* range;

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(const vector_stack_iter_type& iter) noexcept
    : data(iter.data)
    , range(iter.range)
  {
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(type_type* data, size_type* range) noexcept
    : data(data)
    , range(range)
  {
  }

  // satisfy the iterator concept
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> operator*() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> operator*() noexcept;
  [[maybe_unused]] constexpr inline vector_stack_iter_type<type_type>& operator++() noexcept;
  [[maybe_unused]] constexpr inline vector_stack_iter_type<type_type> operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const vector_stack_iter_type& other) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const vector_stack_iter_type& other) const noexcept;
};

/*
 * vector stack declaration
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
struct vector_stack_type
{
  static_vector_type<type_type, buffer_capacity> buffer;
  static_vector_type<size_type, Size(1) + stack_capacity> ranges;

  // satisfy the viewable concept
  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Count() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> At(size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> At(size_type index) noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline const type_type& operator[](size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type> begin() noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type> end() noexcept;

  // utilities
  [[maybe_unused]] constexpr inline void Push(type_type type) noexcept;
  [[maybe_unused]] constexpr inline void Push() noexcept;
  [[maybe_unused]] constexpr inline void Pop() noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>* Peak() const noexcept;
  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>* Peak() noexcept;
};

/*
 * factories
 */

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
VectorStack(vector_stack_type<type_type, stack_capacity, buffer_capacity>* stack) noexcept;

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_type<type_type, stack_capacity, buffer_capacity>
VectorStack() noexcept;

}

// include implementation
#include "vector_stack.inl"

#endif
