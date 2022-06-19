#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/range.hpp>
#include <stl/static_vector.hpp>
#include <stl/vector.hpp>

using type_type = stl::size_type;

void
test_vector(stl::vector_concept<type_type> auto& vec)
{
  for (auto i : stl::Range<type_type>(0, 0x4000)) {
    vec.Push(i);
    stl::Assert(vec.Count() == i + 1, TEST_FAILURE_MESSAGE());
    stl::Assert(*vec.Peak() == i, TEST_FAILURE_MESSAGE());
    stl::Assert(vec[vec.Count() - 1] == i, TEST_FAILURE_MESSAGE());
    stl::Assert(*(vec.end() - 1) == i, TEST_FAILURE_MESSAGE());
  }

  for (auto i : stl::Range<type_type>(0, 0x4000)) {
    stl::Assert(vec[i] == i, TEST_FAILURE_MESSAGE());
    stl::Assert(*vec.At(i) == i, TEST_FAILURE_MESSAGE());
  }

  auto i = stl::Size(0);
  for (const auto index : vec)
    stl::Assert(index == i++, TEST_FAILURE_MESSAGE());
}

int
main()
{
  stl::static_vector_type<type_type, 0x4000> static_vec{};
  test_vector(static_vec);

  stl::heap_allocator_type heap_allocator{};
  stl::dynamic_vector_type<type_type> dynamic_vec{ &heap_allocator };
  test_vector(dynamic_vec);
}
