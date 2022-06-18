#ifndef STL_DYNAMIC_ARRAY_HPP
#define STL_DYNAMIC_ARRAY_HPP

#include "def.hpp"
#include "view.hpp"

#include "allocator/alignment.hpp"
#include "allocator/allocator.hpp"
#include "allocator/heap_allocator.hpp"
#include "allocator/memory.hpp"

namespace stl {

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
  requires allocator_concept<allocator_type>
struct dynamic_array_type
{
  memory_type<type_type> data;
  allocator_type* allocator;

  dynamic_array_type(allocator_type* allocator, size_type count)
    : allocator(allocator)
    , data(allocator->template Allocate<type_type>(count))
  {
  }

  inline ~dynamic_array_type() noexcept
  {
    if (data.data)
      allocator->Free(data);
  }

  // satisfy the viewable concept
  [[maybe_unused]] [[nodiscard]] inline size_type Count() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type* At(size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type* At(size_type index) noexcept;
  [[maybe_unused]] [[nodiscard]] inline const type_type& operator[](size_type index) const noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  [[maybe_unused]] [[nodiscard]] inline type_type* begin() noexcept;
  [[maybe_unused]] [[nodiscard]] inline type_type* end() noexcept;

  // satisfy the view convertible concept
  [[maybe_unused]] [[nodiscard]] inline view_type<const type_type> View() const noexcept;
  [[maybe_unused]] [[nodiscard]] inline view_type<type_type> View() noexcept;
};

// factories
template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] [[nodiscard]] inline dynamic_array_type<type_type, allocator_type>
DynamicArray(allocator_type* allocator, size_type count) noexcept;

}

// include implementation
#include "dynamic_array.inl"

#endif
