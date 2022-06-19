#ifndef STL_DYNAMIC_VECTOR_HPP
#define STL_DYNAMIC_VECTOR_HPP

#include "allocator/alignment.hpp"
#include "allocator/allocator.hpp"
#include "stl.hpp"
#include "view.hpp"

namespace stl {

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
struct dynamic_vector_type
{
  allocator_type* allocator;
  memory_type<type_type> data;
  size_type count;

  MI dynamic_vector_type(allocator_type* allocator)
    : allocator(allocator)
    , data()
    , count(Size(0))
  {
  }

  MI dynamic_vector_type(dynamic_vector_type&& vector)
    : allocator(vector.allocator)
    , data(vector.data)
    , count(vector.count)
  {
    vector.data = memory_type<type_type>();
    vector.count = Size(0);
  }

  MI ~dynamic_vector_type() noexcept
  {
    if (data.data)
      allocator->Free(data);
  }

  MI dynamic_vector_type<type_type, allocator_type>& operator=(dynamic_vector_type&& vector){
    std::swap(allocator, vector.allocator);
    std::swap(data, vector.data);
    std::swap(count, vector.count);
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

  // utilities
  MNI size_type Capacity() const noexcept;
  MI void Capacity(size_type new_count) noexcept;
  MI void Count(size_type new_count) noexcept;
  MI void Push(type_type type) noexcept;
  MI void Pop() noexcept;
  MNI const type_type* Peak() const noexcept;
  MNI type_type* Peak() noexcept;
  MI void Remove(size_type index) noexcept;
};

/*
 * factories
 */

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] inline void
DynamicVector(dynamic_vector_type<type_type, allocator_type>* vector, allocator_type* allocator, size_type initial_capacity) noexcept;

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] [[nodiscard]] inline dynamic_vector_type<type_type, allocator_type>
DynamicVector(allocator_type* allocator) noexcept;

template<typename type_type, typename allocator_type = heap_allocator_type<alignment_no_tag>>
[[maybe_unused]] [[nodiscard]] inline dynamic_vector_type<type_type, allocator_type>
DynamicVector(allocator_type* allocator, size_type initial_capacity) noexcept;

}

// include implementation
#include "dynamic_vector.inl"

#endif
