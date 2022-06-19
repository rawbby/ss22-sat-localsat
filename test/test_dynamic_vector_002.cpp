#include "test_util.hpp"

#include <stl/vector.hpp>

template<typename vector_type, typename type_type>
void
TestPush(vector_type& vector, stl::size_type index)
{
  static_assert(stl::vector_concept<type_type, vector_type>);
  vector.Push(index);
  stl::Assert(vector.Count() == index, TEST_FAILURE_MESSAGE());
  stl::Assert(*vector.Peak() == index, TEST_FAILURE_MESSAGE());
  stl::Assert(vector[vector.Count() - 1] == index, TEST_FAILURE_MESSAGE());
  stl::Assert(*(vector.end() - 1) == index, TEST_FAILURE_MESSAGE());
}

int
main()
{
  auto allocator = stl::heap_allocator_type();
  auto vector = stl::dynamic_vector_type<stl::size_type>(&allocator);
  stl::Assert(vector.Count() == 0, TEST_FAILURE_MESSAGE());

  for (stl::size_type i = 1; i < 0x4000; ++i)
    TestPush<decltype(vector), stl::size_type>(vector, i);

  auto view = vector.View();
  auto i = stl::Size(1);
  for (auto index : view)
    stl::Assert(index == i++, TEST_FAILURE_MESSAGE());
}
