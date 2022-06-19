#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>

template<typename vector_type>
void
TestPush(vector_type& vector, stl::size_type index)
{
  vector.Push(index);
  stl::Assert(vector.Count() == index, TEST_FAILURE_MESSAGE());
  stl::Assert(*vector.Peak() == index, TEST_FAILURE_MESSAGE());
  stl::Assert(vector[vector.Count()-1] == index, TEST_FAILURE_MESSAGE());
  stl::Assert(*(vector.end()-1) == index, TEST_FAILURE_MESSAGE());
}

int
main()
{
  auto allocator = stl::heap_allocator_type();
  auto vector = stl::dynamic_vector_type<stl::size_type>(&allocator);
  stl::Assert(vector.Count() == 0, TEST_FAILURE_MESSAGE());

  for (stl::size_type i = 1; i < 0x4000; ++i)
    TestPush(vector, i);

  auto view = vector.View();
  auto i = stl::Size(1);
  for (auto index : view)
    stl::Assert(index == i++, TEST_FAILURE_MESSAGE());
}
