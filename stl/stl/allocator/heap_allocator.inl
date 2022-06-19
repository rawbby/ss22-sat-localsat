#ifndef SRL_HEAP_ALLOCATOR_INL
#define SRL_HEAP_ALLOCATOR_INL

#include "heap_allocator.hpp"

#ifdef WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

namespace stl {

namespace detail {

template<typename T>
MNI T*
aligned_alloc(size_type count, size_type alignment)
{
#ifdef WIN32
  return (T*)_aligned_malloc(count * sizeof(T), alignment);
#else
  return (T*)std::aligned_alloc(alignment, count * sizeof(T));
#endif
}

template<typename T>
MI void
aligned_free(T* data)
{
#ifdef WIN32
  _aligned_free(data);
#else
  std::free(data);
#endif
}

template<typename T>
MI T*
aligned_realloc(T* data, size_type count, size_type alignment)
{
#ifdef WIN32
  return (T*)_aligned_realloc(data, count * sizeof(T), alignment);
#else
  return (T*)std::realloc(data, count * sizeof(T)); // TODO is alignment lost?
#endif
}

}

template<typename alignment_tag>
template<typename T>
MNI memory_type<T>
heap_allocator_type<alignment_tag>::Allocate(size_type count) const noexcept
{
  T* data = detail::aligned_alloc<T>(count, alignment_tag::alignment);
  return { data, data ? count : Size(0) };
}

template<typename alignment_tag>
template<typename T>
MI void
heap_allocator_type<alignment_tag>::Free(memory_type<T> memory) const noexcept
{
  detail::aligned_free(memory.data);
}

template<typename alignment_tag>
template<typename T>
MNI memory_type<T>
heap_allocator_type<alignment_tag>::ReAllocate(memory_type<T> memory, size_type count) const noexcept
{
  T* data = detail::aligned_realloc(memory.data, count, alignment_tag::alignment);
  return { data, data ? count : Size(0) };
}

}

#endif
