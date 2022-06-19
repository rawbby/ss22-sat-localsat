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
struct dynamic_array_type
{
  static_assert(allocator_concept<allocator_type>, "Invalid Allocator passed to Dynamic Array!");

  memory_type<type_type> data;
  allocator_type* allocator;

  MI dynamic_array_type(allocator_type* allocator, size_type count)
    : allocator(allocator)
    , data(allocator->template Allocate<type_type>(count))
  {
  }

  MI dynamic_array_type(dynamic_array_type&& array)
    : allocator(array.allocator)
    , data(array.data)
  {
    array.data = memory_type<type_type>();
  }

  MI ~dynamic_array_type() noexcept
  {
    if (data.data)
      allocator->Free(data);
  }

  MI dynamic_array_type<type_type, allocator_type>& operator=(dynamic_array_type&& array)
  {
    std::swap(allocator, array.allocator);
    std::swap(data, array.data);
    return *this;
  }

  // satisfy the viewable concept
  MNI size_type Count() const noexcept;
  MNI const type_type* At(size_type index) const noexcept;
  MNI type_type* At(size_type index) noexcept;
  MNI const type_type& operator[](size_type index) const noexcept;
  MNI type_type& operator[](size_type index) noexcept;

  // satisfy the iterable concept
  MNI const type_type* begin() const noexcept;
  MNI const type_type* end() const noexcept;
  MNI type_type* begin() noexcept;
  MNI type_type* end() noexcept;

  // satisfy the view convertible concept
  MNI view_type<const type_type> View() const noexcept;
  MNI view_type<type_type> View() noexcept;
};

}

// include implementation
#include "dynamic_array.inl"

#endif
