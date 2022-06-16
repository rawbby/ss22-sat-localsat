#include "test_util.hpp"

#include <stl/alloc/allocator.hpp>

int
main()
{
  auto allocator = stl::StackAllocator<0x4000, stl::alignment_cache_line_tag>();

  auto memory0 = allocator.Allocate(0x1000);
  stl::Assert(memory0.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory0.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory1 = allocator.Allocate(0x1000);
  stl::Assert(memory1.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory1.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory2 = allocator.Allocate(0x1000);
  stl::Assert(memory2.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory2.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory3 = allocator.Allocate(0x1000);
  stl::Assert(memory3.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory3.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory4 = allocator.Allocate(0x1000);
  stl::Assert(!memory4.data, TEST_FAILURE_MESSAGE());
  stl::Assert(!memory4.count, TEST_FAILURE_MESSAGE());
}
