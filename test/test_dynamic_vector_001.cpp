#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>

template<typename vector_type>
void
TestPush(vector_type& vector, stl::size_type index)
{
  vector.Push(index);
  stl::Assert(vector.Count() == index, TEST_FAILURE_MESSAGE());
  stl::Assert(*vector.Peak() == index, TEST_FAILURE_MESSAGE());
}

int
main()
{
  auto allocator = stl::HeapAllocator();
  auto vector = stl::DynamicVector<stl::size_type>(&allocator);
  stl::Assert(vector.Count() == 0, TEST_FAILURE_MESSAGE());

  TestPush(vector, 1);
  TestPush(vector, 2);
  TestPush(vector, 3);
  TestPush(vector, 4);
  TestPush(vector, 5);
  TestPush(vector, 6);
  TestPush(vector, 7);
  TestPush(vector, 8);

  auto view = vector.View();
  auto i = stl::Size(1);
  for (auto index : view)
    stl::Assert(index == i++, TEST_FAILURE_MESSAGE());
}
